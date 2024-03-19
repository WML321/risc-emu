#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <regex>

using namespace rapidjson;
class Utils
{
public:
    Utils();
    static std::string getInstructionName(const std::string& path, const std::string& opcode, const std::string& funct3 = ""){
        FILE* fp = fopen(path.c_str(), "r");
        if(!fp){
            std::cerr<< "Fail to open JSON file" << path << std::endl;
            return "";
        }
        char buffer[4096];
        FileReadStream is(fp, buffer, sizeof(buffer));

        Document document;
        document.ParseStream(is);

        fclose(fp);

        if(document.HasParseError()){
            std::cerr << "JSON parse error: " << GetParseErrorFunc(document.GetParseError()) << std::endl;
            return "";
        }

        if(document.HasMember(opcode.c_str())){
            const Value& opcodeValue = document[opcode.c_str()];
            if(opcodeValue.IsString()){
                return opcodeValue.GetString();
            }else if(opcodeValue.IsObject() && !funct3.empty()){
                if(opcodeValue.HasMember(funct3.c_str())){
                    const Value& funct_value = opcodeValue[funct3.c_str()];
                    if (funct_value.IsString()) {
                        return funct_value.GetString();
                    }
                }
            }
        }

        std::cerr << "Instruction not found for opcode: " << opcode << " and funct3: " << funct3 << std::endl;
        return "xx";
    }

    static std::string bool2str(const bool& va){
        if(va){
            return "true";
        }else{
            return "false";
        }
    }
    static bool str2bool(std::string str){
        if(str.compare("true")){
            return true;
        }else{
            return false;
        }
    }

    static Document openJson(std::string path){
        FILE* fp = fopen(path.c_str(), "r");
        try {
            if(!fp){
                std::cerr<< "Fail to open JSON file" << path << std::endl;
                throw std::runtime_error("Failed to open file: " + path);
            }
        } catch (const std::runtime_error& e){
            std::cerr << "Error: " << e.what() << std::endl;
            std::terminate(); // 结束进程
            return nullptr;
        }
        char buffer[4096];
        FileReadStream is(fp, buffer, sizeof(buffer));

        Document document;
        document.ParseStream(is);

        fclose(fp);
        try {
            if(document.HasParseError()){
                std::cerr << "JSON parse error: " << GetParseErrorFunc(document.GetParseError()) << std::endl;
                throw std::runtime_error("JSON parse error: " + std::to_string(document.GetParseError()));

                return nullptr;
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return nullptr; // 结束进程
        }

        return document;
    }

    static void split(std::string line, std::regex regex, std::vector<std::string> *res){
        std::sregex_token_iterator iter(line.begin(), line.end(), regex, -1);
        std::sregex_token_iterator end;
        for(; iter != end; iter++){
            std::string word = *iter;
            res->push_back(word);
        }
        return;
    }

    static std::vector<std::string> split(std::string line, std::regex regex){
        std::vector<std::string> res;
        std::sregex_token_iterator iter(line.begin(), line.end(), regex, -1);
        std::sregex_token_iterator end;
        for(; iter != end; iter++){
            std::string word = *iter;
            res.push_back(word);
        }
        return res;
    }

    static std::string strip(const std::string& str){
        std::string result = str;

        // 去除字符串开头的空格
        size_t start = result.find_first_not_of(" \t");
        if (start != std::string::npos) {
            result = result.substr(start);
        }

        // 去除字符串末尾的空格
        size_t end = result.find_last_not_of(" \t");
        if (end != std::string::npos) {
            result = result.substr(0, end + 1);
        }

        return result;
    }

    static uint64_t from_bytes(const std::string& data, const std::string& endian) {
        if (endian == "big") {
            // 大端字节序处理
            // 此处需要根据实际情况实现
        } else if (endian == "little") {
            // 小端字节序处理
            // 此处需要根据实际情况实现
        } else {
            throw std::invalid_argument("Invalid endian argument");
        }
    }
    static std::string read_bytes(size_t n, std::ifstream *file) {
        char* buffer = new char[n];
        file->read(buffer, n);
        std::string data(buffer, n);
        delete[] buffer;
        return data;
    }
};

#endif // UTILS_H
