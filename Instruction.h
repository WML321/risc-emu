#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <iostream>

class Instruction{
public:
    int program_counter = 0;
    std::string execution_code = "";
    std::string function_unit = "";
    int clock_needed = 0;
    std::string to_string = "";
public:

    static int imm_bin_to_int(const std::string& value){
        int bits = value.length();
        int dec = std::stoi(value, nullptr, 2);

        if(value[0] == '1'){
            dec = -1 * (2^bits - dec);
        }
        return dec;
    }
    std::string toString(){
        if(to_string.length() != 0){
            return to_string;
        }else{
            return execution_code;
        }
    }

    virtual std::string to_binary() const = 0;
    // 这个虚函数中， 三个rs的值，并不一定都会用上
    virtual int execute(const std::string &rs1_value, const std::string &rs2_value="", const std::string &rs3_value="") const = 0;

    static std::string map_reg_name(int reg, const std::string& reg_type){
        if(!reg_type.compare("fp")){
            return "f" + std::to_string(reg);
        }else{
            return "x" + std::to_string(reg);
        }
    }

};

#endif // INSTRUCTION_H
