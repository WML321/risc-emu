#include "stype_instruction.h"
#include "utils.h"
#include <bitset>
SType_Instruction::SType_Instruction(const std::string& opcode, const int& imm,
                                     std::string const &funct3, const int &rs1,
                                     const int &rs2): opcode(opcode), imm(imm),
                                     funct3(funct3), rs1(rs1), rs2(rs2){}
std::string SType_Instruction::to_binary() const{
    std::string imm_bin = std::bitset<12>(this->imm).to_string();
    std::string imm11 = imm_bin.substr(0,7);
    std::string imm4 = imm_bin.substr(7,5);
    std::string rs1_ = std::bitset<5>(this->rs1).to_string();
    std::string rs2_ = std::bitset<5>(this->rs2).to_string();
    return imm11 + rs2_ + rs1_ + this->funct3 + imm4 + this->opcode;
}

int SType_Instruction::execute(const std::string &rs1_value, const std::string &rs2_value, const std::string &rs3_value) const{
    std::string code = this->execution_code;
    code = code.replace(code.find("rs"), 2, rs1_value);

    // 缺少eval
    return 4;
}

std::string SType_Instruction::toString (){
    std::string instr_name = Utils::getInstructionName(".\\opcode.json", this->opcode, this->funct3);

    return instr_name + Instruction::map_reg_name(this->rs2, this->rs2_type) +
           std::to_string(this->imm) + Instruction::map_reg_name(this->rs1, this->rs1_type);
}
