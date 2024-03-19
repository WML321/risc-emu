#ifndef BTYPE_INSTRUCTION_H
#define BTYPE_INSTRUCTION_H

#include "Instruction.h"
class BType_Instruction: public Instruction
{ // B-Type imm[12] imm[10:5] rs2 rs1 funct3 imm[4:1] imm[11] opcode B-type   (31<-0)
public:
    std::string rs1_type = "int";
    std::string rs2_type = "int";
    std::string opcode;
    std::string funct3;
    int rs1;
    int rs2;
    int imm;

public:
    BType_Instruction(const std::string& opcode, const int& imm,
                      std::string const &funct3, const int &rs1, const int &rs2);

    std::string to_binary() const override;

    static BType_Instruction* parse(const std::string & binary_code){
        std::string imm12 = binary_code.substr(0,1);
        std::string imm10 = binary_code.substr(1,6);
        int rs2 = std::stoi(binary_code.substr(7, 5), nullptr, 2);
        int rs1 = std::stoi(binary_code.substr(12, 5), nullptr, 2);
        std::string funct3_ = binary_code.substr(17, 3);
        std::string imm4 = binary_code.substr(20, 4);
        std::string imm11 = binary_code.substr(24,1);
        std::string opcode = binary_code.substr(25,7);
        std::string imm_bin = imm12 + imm11 + imm10 + imm4 + "0";

        int imm_val = Instruction::imm_bin_to_int(imm_bin);
        return new BType_Instruction(opcode, imm_val, funct3_, rs1, rs2);
    }

    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;

    std::string toString ();
};

#endif // BTYPE_INSTRUCTION_H
