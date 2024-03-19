#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <unordered_map>
#include "utils.h"
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
class Register
{

public:
    std::string value="", symbolic_name="";
    bool read_only=false;
public:
    Register(std::string symbolic_name, std::string value="", bool read_only=false);
    std::string getValue();
    void setValue(std::string value);
    static Register parse(std::unordered_map<std::string, std::string> int_reg){
        std::string value_="", symbolic_name_="";
        bool read_only_=false;

        auto exist_s = int_reg.find("symbolic_name");
        if(exist_s != int_reg.end()){
            symbolic_name_ = int_reg["symbolic_name"];
        }

        auto exist_v = int_reg.find("value");
        if(exist_v != int_reg.end()){
            value_ = int_reg["value"];
        }

        auto exist_r = int_reg.find("read_only");
        if(exist_r != int_reg.end()){
            read_only_ = Utils::str2bool(int_reg["read_only"]);
        }

        return Register(symbolic_name_, value_, read_only_);
    }

};

class RegisterFile
{
public:
    Register PC, IR, RA, SP;
    std::vector<Register> IntRegisters;
    std::vector<Register> FPRegisters;
public:
    RegisterFile();
    std::string readInt(int reg_name);
    std::string readFP(int reg_name);
    void writeInt(int reg_name, std::string value);
    void writeFP(int reg_name, std::string value);
    std::string read(int reg_name, std::string reg_type);
    void write(int reg_name, std::string value,std::string reg_type);


};

#endif // REGISTER_H
