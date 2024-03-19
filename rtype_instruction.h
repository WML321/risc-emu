#ifndef RTYPE_INSTRUCTION_H
#define RTYPE_INSTRUCTION_H

#include "Instruction.h"

class RType_Instruction: public Instruction
{
public:
    std::string rd_type = "int";
    std::string rs1_type = "int";
    std::string rs2_type = "int";

    std::string opcode;
    std::string funct3;
    std::string funct7;
    int rd, rs1, rs2;
public:
    RType_Instruction(const std::string& opcode, const int& rd,
                      std::string const &funct3, const int &rs1,
                      const int &rs2, const std::string &funct7);
    std::string to_binary() const override;
    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;
    std::string toString ();
    static RType_Instruction* parse(const std::string & binary_code){
        std::string funct7 = binary_code.substr(0,7);
        int rs2 = std::stoi(binary_code.substr(7,5), nullptr, 2);
        int rs1 = std::stoi(binary_code.substr(12,5), nullptr, 2);
        std::string funct3 = binary_code.substr(17,3);
        int rd = std::stoi(binary_code.substr(20,5), nullptr, 2);
        std::string opcode = binary_code.substr(25,7);
        return new RType_Instruction(opcode, rd, funct3, rs1, rs2, funct7);
    }
};

#endif // RTYPE_INSTRUCTION_H
