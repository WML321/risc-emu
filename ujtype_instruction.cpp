#include "ujtype_instruction.h"
#include "utils.h"
#include <bitset>

UJType_Instruction::UJType_Instruction(const std::string& opcode, const int& rd,const int& imm):opcode(opcode),rd(rd),imm(imm) {}

std::string UJType_Instruction::to_binary() const{
    std::string imm_bin = std::bitset<20>(this->imm).to_string();
    return imm_bin + std::bitset<5>(this->rd).to_string() + this->opcode;
}

int UJType_Instruction::execute(const std::string &rs1_value, const std::string &rs2_value, const std::string &rs3_value) const{
    std::string code = this->execution_code;
    code = code.replace(code.find("PC"), 2, rs1_value);

    // 缺少eval
    return 4;
}

std::string UJType_Instruction::toString (){
    std::string instr_name = Utils::getInstructionName(".\\opcode.json", this->opcode);

    return instr_name + Instruction::map_reg_name(this->rd, this->rd_type) + std::to_string(this->imm);
}
