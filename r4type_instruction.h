#ifndef R4TYPE_INSTRUCTION_H
#define R4TYPE_INSTRUCTION_H
#include "Instruction.h"

class R4Type_Instruction: public Instruction
{

public:
    std::string rd_type = "int";
    std::string rs1_type = "int";
    std::string rs2_type = "int";
    std::string rs3_type = "int";

    std::string opcode, funct3, fmt;
    int rd, rs1, rs2, rs3;
public:
    R4Type_Instruction(const std::string& opcode, const int& rd,
                       std::string const &funct3, const int &rs1,
                       const int &rs2, const int &rs3, const std::string &fmt);

    std::string to_binary() const override;
    int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const override;
    std::string toString ();
    static R4Type_Instruction* parse(const std::string & binary_code){
        int rs3 = std::stoi(binary_code.substr(0,5), nullptr, 2);
        std::string fmt = binary_code.substr(5, 2);
        int rs2 = std::stoi(binary_code.substr(5,5), nullptr, 2);
        int rs1 = std::stoi(binary_code.substr(12,5), nullptr, 2);
        std::string funct3 = binary_code.substr(17,3);
        int rd = std::stoi(binary_code.substr(20,5), nullptr, 2);
        std::string opcode = binary_code.substr(25,7);
        return new R4Type_Instruction(opcode, rd, funct3, rs1, rs2, rs3, fmt);
    }

};

#endif // R4TYPE_INSTRUCTION_H
