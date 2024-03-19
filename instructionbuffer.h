#ifndef INSTRUCTIONBUFFER_H
#define INSTRUCTIONBUFFER_H

#include "Instruction.h"
#include <unordered_map>
class IFQEntry{
public:
    Instruction *inst;
    int issue, execute, write_result;
public:
    IFQEntry(Instruction *inst, int iss, int ex, int wr);
    IFQEntry(){};
};

class InstructionBuffer
{
public:
    std::unordered_map<int, IFQEntry> instructions;
    int last_instruction = 0;
public:
    InstructionBuffer();
    IFQEntry get(int pc);
    void put(Instruction *inst, int iss=0, int ex=0, int wr=0);
    void set_instruction_issue(int pc, int steps);
    void set_instruction_execute(int pc, int steps);
    void set_instruction_write_result(int pc, int steps);
    bool empty(int pc);
// 原型中，是自定义了迭代器的，注意
    void clear();
};

#endif // INSTRUCTIONBUFFER_H
