#ifndef ELF_H
#define ELF_H

#include "isa.h"
#include "rtype_instruction.h"
#include "itype_instruction.h"
#include "btype_instruction.h"
#include "r4type_instruction.h"
#include "stype_instruction.h"
#include "ujtype_instruction.h"
#include "utype_instruction.h"
#include "register.h"
#include "utils.h"
#include "program.h"
#include <vector>
#include <unordered_map>

class ELF
{
public:
    std::ifstream file;
    std::string filename;
    std::vector<std::string> symbols;
    std::unordered_map<std::string, std::string> eheader;
    std::unordered_map<std::string, std::string> pheader;
    std::vector<std::string> sections; // 这个里边都是啥类型阿，原型中太模糊了
    std::unordered_map<std::string, std::string> ordered_sections;
    std::vector<int> unknown_instructions;
public:
    ELF(std::string filename);

    void load_program(Program* prog);
    std::string read_byte(int n, bool to_int=true);
    std::unordered_map<int, std::string> parse_rs();
    void parse_eh();
    void parse_ph();
    void parse_sh();

    class Symbol{
        public:
            Symbol(ELF elf);
        public:
            std::ifstream file;
            std::unordered_map<std::string, std::string> eheader;
            std::string (*read_byte)(int n); // 函数指针
            int st_name, st_value, st_size, st_shndx;
            std::string st_info, st_other;
    };

    class Section{
        public:
            Section(ELF elf);
        public:
            std::ifstream file;
            std::unordered_map<std::string, std::string> eheader;
            std::string (*read_byte)(int n); // 函数指针
            std::string content;
            int sh_name, sh_type, sh_flag, sh_addr, sh_offset, sh_size, sh_addralign, sh_entsize;

    };

    class Relocation{
        public:
            Relocation(ELF elf);
            std::ifstream file;
            std::unordered_map<std::string, std::string> eheader;
            std::string (*read_byte)(int n); // 函数指针
            int r_offset, r_info_type, r_info_sym_num, r_addend;
    };
};

#endif // ELF_H
