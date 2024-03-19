#include "instructionbuffer.h"

IFQEntry::IFQEntry(Instruction *inst, int iss, int ex, int wr): inst(inst), issue(iss), execute(ex), write_result(wr){
}

InstructionBuffer::InstructionBuffer(): last_instruction(), instructions() {}


IFQEntry InstructionBuffer::get(int pc){
    if(!this->instructions.count(pc)){
        return this->instructions[pc];
    }else{
        throw std::out_of_range("No instruction at PC " + std::to_string(pc));
    }
}

void InstructionBuffer::put(Instruction *inst, int iss, int ex, int wr){
    this->instructions[inst->program_counter] = IFQEntry(inst, iss, ex, wr);
    this->last_instruction = inst->program_counter;
}

void InstructionBuffer::set_instruction_issue(int pc, int steps){
    this->instructions[pc].issue = steps;
}

void InstructionBuffer::set_instruction_execute(int pc, int steps){
    this->instructions[pc].execute = steps;
}

void InstructionBuffer::set_instruction_write_result(int pc, int steps){
    this->instructions[pc].write_result = steps;
}

bool InstructionBuffer::empty(int pc){
    return pc>this->last_instruction;
}

void InstructionBuffer::clear(){
    this->instructions.clear();
}
