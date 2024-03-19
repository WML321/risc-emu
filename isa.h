#ifndef ISA_H
#define ISA_H

#include "rtype_instruction.h"
#include "itype_instruction.h"
#include "btype_instruction.h"
#include "r4type_instruction.h"
#include "stype_instruction.h"
#include "ujtype_instruction.h"
#include "utype_instruction.h"
#include "register.h"
#include "utils.h"
#include <vector>
#include <unordered_map>


struct InstructionDetail {
    std::string opcode = "nullptr";
    std::string funct3 = "nullptr";
    std::string funct7 = "nullptr";
    std::string exec = "nullptr";
    std::string funcUnit = "nullptr";
    int clockNeeded = -1;
    std::string rdType = "nullptr";
    std::string rsType = "nullptr";
    std::string rtType = "nullptr";
    int length = -1;  // 仅用于某些类型的指令
    std::string imm = "nullptr";  // 仅用于某些类型的指令
    std::string rs1Type = "nullptr";  // 仅用于某些类型的指令
    std::string rs2Type = "nullptr";  // 仅用于某些类型的指令
    std::string rs3Type = "nullptr";  // 仅用于某些类型的指令
    std::string fmt = "nullptr";  // 仅用于某些类型的指令
};

// // 定义一个结构体表示不同类型的指令集合
// struct InstructionSet {
//     std::unordered_map<std::string, InstructionDetail> rType;
//     std::unordered_map<std::string, InstructionDetail> iType;
//     std::unordered_map<std::string, InstructionDetail> sType;
//     std::unordered_map<std::string, InstructionDetail> bType;
//     std::unordered_map<std::string, InstructionDetail> uType;
//     std::unordered_map<std::string, InstructionDetail> ujType;
//     std::unordered_map<std::string, InstructionDetail> r4Type;

//     // std::unordered_map<std::string, InstructionDetail> getType(std::string type){
//     //     // "i-type", "r-type", "r4-type", "s-type", "b-type", "u-type", "uj-type"
//     //     if(type.compare("i-type")){
//     //         return iType;
//     //     }else if(type.compare("r-type")){
//     //         return rType;
//     //     }else if(type.compare("r4_type")){
//     //         return r4Type;
//     //     }else if(type.compare("s-type")){
//     //         return sType;
//     //     }else if(type.compare("b-type")){
//     //         return bType;
//     //     }else if(type.compare("u-type")){
//     //         return uType;
//     //     }else{
//     //         return ujType; // 这里不是指针，所以外界如果修改，只能修改副本
//     //     }
//     // }
// };

struct InstructionMap{
    std::unordered_map<std::string, std::unordered_map<std::string, InstructionDetail>> maps;
    InstructionMap(){
        maps.insert({"i-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"r-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"r4-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"s-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"b-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"u-type", std::unordered_map<std::string, InstructionDetail>()});
        maps.insert({"uj-type", std::unordered_map<std::string, InstructionDetail>()});
    }
};


class ISA
{
public:
    static InstructionMap ISA_singleton;
    static bool ISA_set;
    InstructionMap ISA_;
public:
    ISA();
public:
    std::string map_register_name(std::string reg_name);
    int map_symbols(const std::string& imm, const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& symbol_table); // 第二个参数，类型未知
    Instruction* instruction_from_str(const std::string& line,
                                     const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& symbol_table,
                                     const int& pc); // 参数类型未知, pc类型未知
    Instruction *instruction_from_bin(std::string binary_code, int pc);
    void loadISA(const Document& document);
};

#endif // ISA_H
