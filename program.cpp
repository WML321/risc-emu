#include "program.h"
#include "utils.h"
#include "elf.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip>

Program::Program(DataMemory DM):DM(DM) {
    this->ISA_ = ISA();
    this->sections[".text"] = 0;
    this->directives[".byte"] = 1;
    this->directives[".2byte"] = 2;
    this->directives[".4byte"] = 4;
    this->directives[".8byte"] = 8;
    this->directives[".half"] = 2;
    this->directives[".word"] = 4;
    this->directives[".dword"] = 8;
}

std::string Program::get_entry_point(){ // 这个函数，很明显就是为了获取程序入口的
    if(this->symbol_table.count("_start")>0){
        return ""; // 这个返回类型我也不知道，我去调试其他时，这里时空的，我也不知道对应value是什么类型，源码中，既可以是字典，也可以是数字
    }
}

void Program::load_text(std::string text){
    int pc=0;
    std::vector<std::string> lines;
    Utils::split(text, std::regex("\n"), &lines);
    std::string line;
    for(int i=0; i<lines.size(); i++){
        line = Utils::split(lines[i], std::regex(";"))[0];
        line = Utils::strip(line);
        line.replace(line.find("\t"), 1, " ");

        if(line.compare("")){
            std::vector<std::string> temp = Utils::split(line, std::regex(".+"));
            if(temp.size()!=0){
                std::string label = temp[0];
                label = label.substr(0, label.size()-1);
                std::transform(label.begin(), label.end(), label.begin(), ::tolower);

            }
        }
    }
}


int Program::parse_directive(std::string line, int pc){
    std::vector<std::string> lines = Utils::split(line, std::regex(" "));
    std::vector<std::string> sections_ = {".text", ".data", ".rodata", ".bss"};

    for(int i=0; i<4; i++){
        if( !lines[0].compare(sections_[i])){
            this->sections[lines[0]] = pc;
        }else if(!lines[0].compare(".section") and !lines[1].compare(sections_[i])){
            this->sections[lines[1]] = pc;
        }
    }

    if(!lines[0].compare(".align")){
        this->alignment = 2^(std::stoi(lines[1]));
    }else if(!lines[0].compare("balign")){
        this->alignment = std::stoi(lines[1]);
    }

    for(int i=0; i<this->directives.size();i++){

        if(this->directives.count(lines[0])>0){
            std::string val = lines[1];
            for(int i=0; i<this->alignment; i++){
                this->DM.store(pc, std::stoi(val)); // 暂时不知道这里的类型是什么
            }
        }

    }

    if(!lines[0].compare(".zero")){
        int addr = pc;
        while(addr < std::stoi(lines[1])){
            this->DM.store(addr, 0);
            addr++;
        }
        pc+=addr;
    }
    if(!lines[0].compare(".string") or !lines[0].compare(".asciz")){
        std::string s = lines[1].substr(1, lines[1].size()-2);
        int addr = pc;
        for(int i=0; i<s.size(); i++, addr++){
            this->DM.store(addr, static_cast<int>(s[i]));
        }
        pc+=addr;
    }

    return pc;
}

void Program::load_machine_code(std::string filename){
    ELF file(filename);
    file.load_program(this);
    this->unknown_instructions = file.unknown_instructions;
}

std::string Program::to_code(){
    std::vector<std::string> lines, done_sections;
    for(int i=0; i<this->IM.size(); i++){
        for(auto iter=this->sections.begin(); iter!=this->sections.end(); iter++){
            if(iter->second == i*4){
                if(iter->first.compare(".text")){
                    lines.push_back("");
                }
                lines.push_back(iter->first);
                done_sections.push_back(iter->first);
            }
        }
        for(auto iter=this->symbol_table.begin(); iter!=this->symbol_table.end(); iter++){
            if(std::stoi(iter->second["value"]) == i*4 and !iter->second["section"].compare(done_sections[done_sections.size()-1])){
                lines.push_back("");
                lines.push_back(iter->first + ":");
            }
        }
        lines.push_back("    " + std::to_string(this->IM[i]));

        if(std::find(this->unknown_instructions.begin(), this->unknown_instructions.end(), i) != this->unknown_instructions.end()){
            //this->syntax_errors.push_back(std::make_tuple(lines.size()-1, std::to_string(this->IM[i]), "Umknown Instruction"));
        }
    }


    for(auto iter=this->sections.begin(); iter!=this->sections.end(); iter++){
        if(std::find(done_sections.begin(), done_sections.end(), iter->first) == done_sections.end()){
            lines.push_back("");
            lines.push_back(iter->first);
            for(auto sym = this->symbol_table.begin(); sym!=this->symbol_table.end(); sym++){
                if(!sym->second["section"].compare(iter->first)){
                    lines.push_back(sym->second["name"] + ":");
                    std::string dim;
                    if(!sym->second["size"].compare("1")){
                        dim = ".byte";
                    }else if(!sym->second["size"].compare("2")){
                        dim = ".2byte";
                    }else if(!sym->second["size"].compare("4")){
                        dim = ".4byte";
                    }else if(!sym->second["size"].compare("8")){
                        dim = ".8byte";
                    }else{
                        lines.push_back("    <no_info>");
                        continue;
                    }

                    std::vector<std::string> data;
                    for(int i=0; i<std::stoi(sym->second["size"]); i++){
                        uintptr_t addr = this->sections[sym->second["section"]] + std::stoi(sym->second["value"]);
                        std::stringstream ss;
                        ss<<std::hex<<this->DM.load(addr);
                        data.push_back(ss.str());
                    }
                    std::ostringstream oss;
                    oss<<"    "<<dim<<"0x";
                    for(auto value:data){
                        oss<<value;
                    }
                    lines.push_back(oss.str());
                }
            }
        }
    }
    std::ostringstream ossd;
    for(auto str:lines){
        ossd<<str<<"\n";
    }
    return ossd.str();
}
