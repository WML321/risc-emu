#ifndef ITYPE_INSTRUCTION_H
#define ITYPE_INSTRUCTION_H
#include <iostream>
#include "Instruction.h"
class IType_Instruction: public Instruction
{
public:
    std::string opcode;
    std::string funct3;
    int rd;
    int rs;
    int imm;

    int length; // 这个变量，在python中没有定义
    std::string rd_type = "int";
    std::string rs_type = "int";
public:
    IType_Instruction(const std::string& opcode, const int& rd,
                      std::string const &funct3, const int &rs, const int &imm);

    static IType_Instruction* parse(const std::string & binary_code){
        int imm_ = Instruction::imm_bin_to_int(binary_code.substr(0,12));
        int rs = std::stoi(binary_code.substr(12,5), nullptr, 2);
        std::string funct3 = binary_code.substr(17,3);
        int rd = std::stoi(binary_code.substr(20,5), nullptr, 2);
        std::string opcode = binary_code.substr(25,7);
        return new IType_Instruction(opcode, rd, funct3, rs, imm_);
    }
    std::string to_binary() const override;
    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;
    std::string toString ();
    bool is_jarl();
    bool is_load();
};

#endif // ITYPE_INSTRUCTION_H
