#include "itype_instruction.h"
#include <bitset>
#include "utils.h"

IType_Instruction::IType_Instruction(const std::string& opcode, const int& rd,
                                     std::string const &funct3, const int &rs, const int &imm):opcode(opcode),
    rd(rd), funct3(funct3), rs(rs), imm(imm){}

std::string IType_Instruction::to_binary() const{
    std::string imm_bin = std::bitset<5>(this->imm).to_string();
    std::string rs_ = std::bitset<5>(this->rs).to_string();
    std::string rd_ = std::bitset<5>(this->rd).to_string();
    return imm_bin + rs_ + this->funct3 + rd_ + this->opcode;
}

int IType_Instruction::execute(const std::string &rs1_value, const std::string &rs2_value, const std::string &rs3_value) const{
    std::string code = this->execution_code;
    code = code.replace(code.find("rs"),2, rs1_value);

    code = code.replace(code.find("PC"), 2, rs2_value);

    // eval
    return 4;
}

std::string IType_Instruction::toString (){
    std::string instr_name = Utils::getInstructionName(".\\opcode.json", this->opcode, this->funct3);
    if(is_load() || this->opcode.compare("0100111")){
        return instr_name + Instruction::map_reg_name(this->rd, this->rd_type) + ", " +
               std::to_string(this->imm) + "(" + Instruction::map_reg_name(this->rs, this->rs_type) + ")";
    }else{
        return instr_name + Instruction::map_reg_name(this->rd, this->rd_type) + ", " +
               Instruction::map_reg_name(this->rs, this->rs_type) + ", " + std::to_string(this->imm);
    }
}

bool IType_Instruction::is_jarl(){
    return this->opcode.compare("1100111");
}

bool IType_Instruction::is_load(){
    return this->opcode.compare("0000011") or this->opcode.compare("0000111");
}
