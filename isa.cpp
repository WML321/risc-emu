#include "isa.h"
#include "rapidjson/document.h"
#include <vector>
#include <regex>
#include <algorithm>
#include <bitset>
#include <sstream>

bool ISA::ISA_set = false;
InstructionMap ISA::ISA_singleton;

ISA::ISA() {
    if(!ISA::ISA_set){
        Document document_F = Utils::openJson(".\\RV32F.json");
        Document document_I = Utils::openJson(".\\RV32I.json");
        Document document_M = Utils::openJson(".\\RV32M.json");
        loadISA(document_F); // Document是不支持拷贝构造函数，因为他们不可复制，所以在loadISA中使用const和&
        loadISA(document_I);
        loadISA(document_M);

        ISA::ISA_singleton = this->ISA_;
    }else{
        this->ISA_ = ISA::ISA_singleton;
    }
}

void ISA::loadISA(const Document& document){
    std::vector<std::string> type = {"i-type", "r-type", "r4-type", "s-type", "b-type", "u-type", "uj-type"};

    for(int i_one=0; i_one<type.size(); i_one++){
        //first
        if(document.HasMember(type[i_one].c_str())){
            //second
            const Value& second = document[type[i_one].c_str()];
            // 查看过json文件后，可以知道此时的temp肯定还是一个map，所以就不进行判断了，直接用
            for(auto it_two = second.MemberBegin(); it_two!=second.MemberEnd(); it_two++){
                // third
                const Value& thrid = it_two->value;
                InstructionDetail detail;
                for(auto it_three = thrid.MemberBegin(); it_three!=thrid.MemberEnd(); it_three++){
                    std::string key = it_three->name.GetString();
                    if(key.compare("opcode")){
                        detail.opcode = it_three->value.GetString();
                    }else if(key.compare("funct3")){
                        detail.funct3 = it_three->value.GetString();
                    }else if(key.compare("funct7")){
                        detail.funct7 = it_three->value.GetString();
                    }else if(key.compare("exec")){
                        detail.exec = it_three->value.GetString();
                    }else if(key.compare("funcUnit")){
                        detail.funcUnit = it_three->value.GetString();
                    }else if(key.compare("clockNeeded")){
                        detail.clockNeeded = it_three->value.GetInt();
                    }else if(key.compare("rdType")){
                        detail.rdType = it_three->value.GetString();
                    }else if(key.compare("rsType")){
                        detail.rsType = it_three->value.GetString();
                    }else if(key.compare("rtType")){
                        detail.rtType = it_three->value.GetString();
                    }else if(key.compare("length")){
                        detail.length = it_three->value.GetInt();
                    }else if(key.compare("imm")){
                        detail.imm = it_three->value.GetString();
                    }else if(key.compare("rs1Type")){
                        detail.rs1Type = it_three->value.GetString();
                    }else if(key.compare("rs2Type")){
                        detail.rs2Type = it_three->value.GetString();
                    }else if(key.compare("rs3Type")){
                        detail.rs3Type = it_three->value.GetString();
                    }else if(key.compare("fmt")){
                        detail.fmt = it_three->value.GetString();
                    }

                }
                this->ISA_.maps[type[i_one]][it_two->name.GetString()] = detail;
            }
        }
    }
}

std::string ISA::map_register_name(std::string reg_name){
    RegisterFile rf = RegisterFile();
    std::vector<Register> ir = rf.IntRegisters;
    for(int i=0; i<ir.size(); i++){
        if(ir[i].symbolic_name.compare(reg_name)){
            return "x" + std::to_string(i);
        }
    }

    std::vector<Register> fr = rf.FPRegisters;
    for(int i=0; i<fr.size(); i++){
        if(fr[i].symbolic_name.compare(reg_name)){
            return "f" + std::to_string(i);
        }
    }

    return reg_name;
}

int ISA::map_symbols(const std::string& imm,
                     const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& symbol_table){
    try {
        return std::stoi(imm);
    } catch (std::invalid_argument& e) {
        std::smatch match;
        if (std::regex_match(imm, match, std::regex("%lo\\((.+)\\)"))){
            std::string label = match[1];
            auto sym = symbol_table.find(label);
            if(sym != symbol_table.end()){
                // 将symbol_table最后获取的数字，获取其8位二进制的ascii码然后连接起来
                const std::string& text = sym->second.at("text");
                std::string bins="";
                for(char c: text){
                    bins += std::bitset<8>(c).to_string();
                }
                return std::stoi(bins.substr(0, bins.size() - 12), nullptr, 2);

            }
        }else if(std::regex_match(imm, match, std::regex("%hi\\((.+)\\)"))){
            std::string label = match[1];
            auto sym = symbol_table.find(label);
            if(sym != symbol_table.end()){
                // 将symbol_table最后获取的数字，获取其8位二进制的ascii码然后连接起来
                const std::string& text = sym->second.at("text");
                std::string bins="";
                for(char c: text){
                    bins += std::bitset<8>(c).to_string();
                }
                return std::stoi(bins.substr(0, bins.size() - 12), nullptr, 2);

            }
        }
        return -1;
    }
}

Instruction* ISA::instruction_from_str(const std::string& line,
                                 const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& symbol_table,
                                      const int& pc){
    std::vector<std::string> lines;
    std::regex regex("\\s+|,");
    std::sregex_token_iterator iter(line.begin(), line.end(), regex, -1);
    std::sregex_token_iterator end;
    for(; iter!=end; iter++){
        std::string word = *iter;
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(0, word.find_first_not_of(" \t")); //去除前导空格
        word.erase(word.find_last_not_of(" \t")+1);  // 起初尾随空格
        if(!word.empty()){
            lines.push_back(this->map_register_name(word));
        }
    }

    if(this->ISA_.maps["r-type"].count(lines[0]) > 0){
        InstructionDetail match = this->ISA_.maps["r-type"][lines[0]];
        int rd = std::stoi(lines[1].substr(1));
        int rs1 = std::stoi(lines[2].substr(1));
        int rs2 = std::stoi(lines[3].substr(1));
        std::string funct3="000";
        if(match.funct3!="nullptr"){
            funct3 = match.funct3;
        }

        RType_Instruction *inst = new RType_Instruction(match.opcode, rd, funct3, rs1, rs2, match.funct7);
        inst->program_counter = pc;
        inst->execution_code = match.exec;
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;
        if(match.rdType.compare("rdType")){
            inst->rd_type = match.rdType;
        }
        if(match.rsType.compare("rsType")){
            inst->rs1_type = match.rsType;
        }
        if(match.rtType.compare("rtType")){
            inst->rs2_type = match.rtType;
        }
        return inst;
    }else if(this->ISA_.maps["i-type"].count(lines[0]) > 0){
        InstructionDetail match = this->ISA_.maps["r-type"][lines[0]];
        int rd = std::stoi(lines[1].substr(1));
        int rs1 = std::stoi(lines[2].substr(1));
        int rs2 = std::stoi(lines[3].substr(1));
        int rs;
        std::string imm_str;
        if(match.opcode.compare("0000011") or match.opcode.compare("0000111") or match.opcode.compare("0100111")){
            std::smatch re;
            std::regex_search(lines[2], re, std::regex("(.+)\\((.+)\\)"));
            imm_str = re[1].str();
            rs = std::stoi(this->map_register_name(re[2].str()).substr(1));
        }else{
            rs = std::stoi(this->map_register_name(lines[2]).substr(1));
            imm_str= lines[3];
        }

        int imm = this->map_symbols(imm_str, symbol_table);

        IType_Instruction *inst = new IType_Instruction(match.opcode, rd, match.funct3, rs, imm);
        inst->program_counter = pc;
        inst->execution_code = match.exec;
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;
        if(match.rdType.compare("rdType")){
            inst->rd_type = match.rdType;
        }
        if(match.rsType.compare("rsType")){
            inst->rs_type = match.rsType;
        }

        if(inst->is_load()){
            inst->length = match.length;
        }
        return inst;

    }else if(this->ISA_.maps["s-type"].count(lines[0]) > 0){
        InstructionDetail match = this->ISA_.maps["s-type"][lines[0]];
        int rs2 = std::stoi(lines[1].substr(1));
        std::string rs1_parts_ = lines[2].substr(0, lines[2].size()-1);

        std::regex regex_1("\\(");
        std::vector<std::string> rs1_parts;
        Utils::split(rs1_parts_, regex_1, &rs1_parts);

        int rs1 = std::stoi(this->map_register_name(rs1_parts[1]).substr(1));
        int imm = this->map_symbols(rs1_parts[0], symbol_table);

        SType_Instruction *inst = new SType_Instruction(match.opcode, imm, match.funct3, rs1, rs2);
        inst->program_counter = pc;
        inst->execution_code = match.exec.replace(match.exec.find("imm"), 3, std::to_string(imm));
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;

        if(match.rsType.compare("rsType")){
            inst->rs1_type = match.rsType;
        }
        if(match.rtType.compare("rtType")){
            inst->rs2_type = match.rtType;
        }

        inst->length = match.length;
        return inst;
    }else if(this->ISA_.maps["b-type"].count(lines[0]) > 0){
        InstructionDetail match = this->ISA_.maps["b-type"][lines[0]];
        int rs2 = std::stoi(lines[1].substr(1));
        int rs1 = std::stoi(lines[2].substr(1));
        int imm;
        std::regex integer_pattern("[-+]?\\d+");
        if (std::regex_match(lines[3], integer_pattern)) {
            // 将匹配的整数字符串转换为整数
            imm = std::stoi(lines[3]);
            // 现在您可以使用imm进行其他操作
        }else{
            //imm = symbol_table[line[3]]['value'] - pc
            std::string tmp = symbol_table.at(lines[3]).at("value");
            imm = std::stoi(tmp) - pc;
        }

        BType_Instruction *inst = new BType_Instruction(match.opcode, imm, match.funct3, rs1, rs2);
        inst->program_counter = pc;
        inst->execution_code = match.exec;
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;

        if(match.rsType.compare("rsType")){
            inst->rs1_type = match.rsType;
        }
        if(match.rsType.compare("rtType")){
            inst->rs2_type = match.rtType;
        }
        return inst;
    }else if(this->ISA_.maps["u-type"].count(lines[0]) > 0){
        InstructionDetail match = this->ISA_.maps["b-type"][lines[0]];
        int rd = std::stoi(lines[1].substr(1));
        int imm = this->map_symbols(lines[2], symbol_table);

        UType_Instruction *inst = new UType_Instruction(match.opcode, rd, imm);
        inst->program_counter = pc;
        inst->execution_code = match.exec.replace(match.exec.find("imm"), 3, std::bitset<20>(imm).to_string());
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;

        if(match.rdType.compare("rdType")){
            inst->rd_type = match.rdType;
        }
        return inst;
    }else if(this->ISA_.maps["r4-type"].count(lines[0])){
        InstructionDetail match = this->ISA_.maps["r4-type"][lines[0]];
        int rd = std::stoi(lines[1].substr(1));
        int rs1 = std::stoi(lines[2].substr(1));
        int rs2 = std::stoi(lines[3].substr(1));
        int rs3 = std::stoi(lines[4].substr(1));

        std::string fmt = match.fmt;
        R4Type_Instruction *inst = new R4Type_Instruction(match.opcode, rd, match.funct3, rs1, rs2, rs3, fmt);
        inst->program_counter = pc;
        inst->execution_code = match.exec;
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;

        if(match.rdType.compare("rdType")){
            inst->rd_type = match.rdType;
        }
        if(match.rs1Type.compare("rs1Type")){
            inst->rs1_type = match.rs1Type;
        }
        if(match.rs2Type.compare("rs2Type")){
            inst->rs2_type = match.rs2Type;
        }
        if(match.rs3Type.compare("rs3Type")){
            inst->rs3_type = match.rs3Type;
        }
        return inst;
    }else if(this->ISA_.maps["uj-type"].count(lines[0])){
        InstructionDetail match = this->ISA_.maps["r4-type"][lines[0]];
        int rd = std::stoi(lines[1].substr(1));
        int imm = this->map_symbols(lines[2], symbol_table);

        UJType_Instruction *inst = new UJType_Instruction(match.opcode, rd, imm);
        inst->program_counter = pc;
        inst->execution_code = match.exec;
        inst->function_unit = match.funcUnit;
        inst->clock_needed = match.clockNeeded;
        if(match.rdType.compare("rdType")){
            inst->rd_type = match.rdType;
        }
        return inst;
    }else if(lines[0].compare("nop") or lines[0].compare("ecall")){
        throw std::logic_error("Not implemented");
    }else{
        throw std::logic_error("Syntax error");
    }
}

Instruction* ISA::instruction_from_bin(std::string binary_code, int pc){
    std::string opcode = binary_code.substr(25, 7);
    for(auto it_1 = this->ISA_.maps.begin(); it_1!=this->ISA_.maps.end(); it_1++){
        for(auto it_2 = it_1->second.begin();it_2!=it_1->second.end(); it_2++){
            InstructionDetail match = it_2->second;
            if(match.opcode.compare(opcode)){
                if(it_1->first.compare("r-type")){
                    RType_Instruction* inst = RType_Instruction::parse(binary_code);
                    if(match.funct7.compare(inst->funct7)){
                        if(match.funct3.compare("nullptr") or match.funct3.compare(inst->funct3)){
                            inst->execution_code = match.exec;
                            inst->function_unit = match.funcUnit;
                            inst->clock_needed = match.clockNeeded;
                            inst->program_counter = pc;

                            if(match.rdType.compare("tdType")){
                                inst->rd_type = match.rdType;
                            }
                            if(match.rsType.compare("rsType")){
                                inst->rs1_type = match.rsType;
                            }
                            if(match.rtType.compare("rtType")){
                                inst->rs2_type = match.rtType;
                            }
                        }
                    }
                    return inst;
                }else if(it_1->first.compare("i-type")){
                    IType_Instruction* inst = IType_Instruction::parse(binary_code);
                    if(match.opcode.compare(inst->opcode) and match.funct3.compare(inst->funct3)){
                        std::string imm_bin = std::bitset<32>(inst->imm).to_string();
                        if((!match.imm.compare("nullptr") and match.imm.compare(imm_bin.substr(0, 6)))
                            or match.imm.compare("nullptr")){
                            inst->execution_code = match.exec.replace(match.exec.find("imm"), 3, std::to_string(inst->imm));
                            inst->function_unit = inst->function_unit;
                            inst->clock_needed = inst->clock_needed;
                            inst->program_counter = pc;

                            if(match.rdType.compare("rdType")){
                                inst->rd_type = match.rdType;
                            }
                            if(match.rsType.compare("rsType")){
                                inst->rs_type = match.rsType;
                            }

                            if(inst->is_load()){
                                inst->length = match.length;
                            }
                        }
                    }
                    return inst;

                }else if(it_1->first.compare("s-type")){
                    SType_Instruction *inst = SType_Instruction::parse(binary_code);
                    if(match.funct3.compare(inst->funct3)){
                        inst->execution_code = match.exec.replace(match.exec.find("imm"), 3, std::to_string(inst->imm));
                        inst->function_unit = match.funcUnit;
                        inst->clock_needed = match.clockNeeded;
                        inst->length = match.length;
                        inst->program_counter = pc;

                        if(match.rsType.compare("rsType")){
                            inst->rs1_type = match.rsType;
                        }
                        if(match.rsType.compare("rtType")){
                            inst->rs2_type = match.rtType;
                        }
                    }
                    return inst;
                }else if(it_1->first.compare("b-type")){
                    BType_Instruction *inst = BType_Instruction::parse(binary_code);
                    if(match.funct3.compare(inst->funct3)){
                        inst->execution_code = match.exec;
                        inst->function_unit = match.funcUnit;
                        inst->clock_needed = match.clockNeeded;
                        inst->program_counter = pc;

                        if(match.rsType.compare("rsType")){
                            inst->rs1_type = match.rsType;
                        }
                        if(match.rsType.compare("rtType")){
                            inst->rs2_type = match.rtType;
                        }
                    }
                    return inst;
                }else if(it_1->first.compare("u-type")){
                    UType_Instruction *inst = UType_Instruction::parse(binary_code);
                    if(match.opcode.compare(inst->opcode)){
                        std::string imm_bin = std::bitset<20>(inst->imm).to_string();
                        inst->execution_code = match.exec.replace(match.exec.find("imm"),3, imm_bin);
                        inst->function_unit = match.funcUnit;
                        inst->clock_needed = match.clockNeeded;
                        inst->program_counter = pc;

                        if(match.rdType.compare("rdType")){
                            inst->rd_type = match.rdType;
                        }

                    }
                    return inst;
                }else if(it_1->first.compare("uj-type")){
                    UJType_Instruction *inst = UJType_Instruction::parse(binary_code);
                    inst->execution_code = match.exec;
                    inst->function_unit = match.funcUnit;
                    inst->clock_needed = match.clockNeeded;
                    inst->program_counter = pc;

                    if(match.rdType.compare("rdType")){
                        inst->rd_type = match.rdType;
                    }
                    return inst;
                }else if(it_1->first.compare("r4-type")){
                    R4Type_Instruction *inst = R4Type_Instruction::parse(binary_code);
                    if(match.opcode.compare(inst->opcode) and match.fmt.compare(inst->fmt)){
                        inst->execution_code = match.exec;
                        inst->function_unit = match.funcUnit;
                        inst->clock_needed = match.clockNeeded;
                        inst->program_counter = pc;

                        if(match.rdType.compare("rdType")){
                            inst->rd_type = match.rdType;
                        }
                        if(match.rs1Type.compare("rs1Type")){
                            inst->rs1_type = match.rs1Type;
                        }
                        if(match.rs2Type.compare("rs2Type")){
                            inst->rs2_type = match.rs2Type;
                        }
                        if(match.rs3Type.compare("rs3Type")){
                            inst->rs3_type = match.rs3Type;
                        }

                    }
                    return inst;
                }else{
                    throw std::logic_error("Not implemented");
                }
            }
        }
    }
    throw std::logic_error("Unknown OPCODE");
}
