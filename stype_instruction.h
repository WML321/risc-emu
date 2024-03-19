#ifndef STYPE_INSTRUCTION_H
#define STYPE_INSTRUCTION_H

#include "Instruction.h"
class SType_Instruction: public Instruction
{
public:
    std::string rs1_type = "int";
    std::string rs2_type = "int";
    std::string opcode, funct3;
    int imm, rs1, rs2;

    int length;


public:
    SType_Instruction(const std::string& opcode, const int& imm,
                      std::string const &funct3, const int &rs1,
                      const int &rs2);
    std::string to_binary() const override;
    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;
    std::string toString ();
    static SType_Instruction* parse(const std::string & binary_code){
        std::string imm11 = binary_code.substr(0,7);
        int rs2 = std::stoi(binary_code.substr(7,5), nullptr, 2);
        int rs1 = std::stoi(binary_code.substr(12,5), nullptr, 2);
        std::string funct3 = binary_code.substr(17,3);
        std::string imm4 = binary_code.substr(20,5);
        std::string opcode = binary_code.substr(25,7);

        int imm = Instruction::imm_bin_to_int(imm11 + imm4);
        return new SType_Instruction(opcode, imm, funct3, rs1, rs2);
    }
};

#endif // STYPE_INSTRUCTION_H
