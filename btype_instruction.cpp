#include "btype_instruction.h"
#include <bitset>
#include "utils.h"

BType_Instruction::BType_Instruction(const std::string& opcode, const int& imm,
                                     std::string const &funct3, const int &rs1, const int &rs2):
    opcode(opcode),imm(imm), funct3(funct3), rs1(rs1), rs2(rs2){}


std::string BType_Instruction::to_binary() const {
    std::string imm_bin = std::bitset<12>(this->imm).to_string();
    std::string imm12 = imm_bin.substr(0,1);
    std::string imm10 = imm_bin.substr(2,6);
    std::string imm4 = imm_bin.substr(8,4);
    std::string imm11 = imm_bin.substr(1,1);

    std::string rs1_str = std::bitset<5>(this->rs1).to_string();
    std::string rs2_str = std::bitset<5>(this->rs2).to_string();

    std::string res = imm12 + imm10 + rs2_str + rs1_str + this->funct3 + imm4 + imm11 + this->opcode;
    return res;
}

int BType_Instruction::execute(const std::string &rs1_value, const std::string &rs2_value, const std::string &rs3_value)const {
    std::string code = this->execution_code;
    code = code.replace(code.find("rs"),2, rs1_value);
    code = code.replace(code.find("rt"),2, rs2_value);

    std::cout<< "BType_Instruction. execute"<< code<< std::endl;
    // 在python中，这里将要进行的是eval(code)，但是目前，我还不知道code中的内容是什么，所以这里先空着
    return 4;
}

std::string BType_Instruction::toString(){
    std::string instr_name = Utils::getInstructionName(".\\opcode.json", this->opcode, this->funct3);
    return instr_name + Instruction::map_reg_name(this->rs2, this->rs2_type) + ", "
                      + Instruction::map_reg_name(this->rs1, this->rs1_type) + ", "
                      + std::to_string(this->imm);
}
