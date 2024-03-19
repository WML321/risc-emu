#ifndef UJTYPE_INSTRUCTION_H
#define UJTYPE_INSTRUCTION_H
#include "Instruction.h"
class UJType_Instruction: public Instruction
{
public:
    std::string rd_type = "int";
    std::string opcode;
    int rd, imm;

public:
    UJType_Instruction(const std::string& opcode, const int& rd,const int& imm);
    std::string to_binary() const override;
    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;
    std::string toString ();

    static UJType_Instruction* parse(const std::string & binary_code){
        int imm = Instruction::imm_bin_to_int(binary_code.substr(0,20));
        int rd = std::stoi(binary_code.substr(20,5), nullptr, 2);
        std::string opcode = binary_code.substr(25,7);

        return new UJType_Instruction(opcode, rd, imm);
    }
};

#endif // UJTYPE_INSTRUCTION_H
