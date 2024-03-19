#ifndef PROGRAM_H
#define PROGRAM_H

#include "datamemory.h"
#include "isa.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>>
#include <tuple>
class ELF;
class Program
{
public:
    DataMemory DM;
    ISA ISA_;
    std::vector<std::tuple<int, std::string, std::string>> syntax_errors;
    std::vector<int> unknown_instructions, IM; // 类型待定
    std::unordered_map<std::string, int> sections;
    std::unordered_map<std::string, std::string> directives;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> symbol_table; // 原型字典中，既有字符串，也有数字
    int alignment=4;



public:
    Program(DataMemory DM);

    std::string get_entry_point();
    void load_text(std::string text);

    int parse_directive(std::string line, int pc);
    void load_machine_code(std::string filename);
    std::string to_code();
};

#endif // PROGRAM_H
