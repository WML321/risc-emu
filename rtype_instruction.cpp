#include "rtype_instruction.h"
#include "utils.h"
#include <bitset>

RType_Instruction::RType_Instruction(const std::string& opcode, const int& rd,
                                     std::string const &funct3, const int &rs1,
                                     const int &rs2, const std::string &funct7): opcode(opcode),
    rd(rd), funct3(funct3), rs1(rs1), rs2(rs2), funct7(funct7){}


std::string RType_Instruction::to_binary() const{
    std::string rs1 = std::bitset<5>(this->rs1).to_string();
    std::string rs2 = std::bitset<5>(this->rs2).to_string();
    std::string rd  = std::bitset<5>(this->rd).to_string();

    return this->funct7 + rs2 + rs1 + this->funct3 + rd + this->opcode;
}

std::string RType_Instruction::toString (){
    std::string instr_name = Utils::getInstructionName(".\\opcode.json", this->opcode, this->funct3);
    return instr_name + Instruction::map_reg_name(this->rd, this->rd_type),
           Instruction::map_reg_name(this->rs1, this->rs1_type) + Instruction::map_reg_name(this->rs2, this->rs2_type);
}

int RType_Instruction::execute(const std::string &rs1_value, const std::string &rs2_value, const std::string &rs3_value) const{
    std::string code = this->execution_code;
    code = code.replace(code.find("rs"), 2, rs1_value);
    code = code.replace(code.find("rt"), 2, rs2_value);

    // 缺少eval
    return 4;
}
