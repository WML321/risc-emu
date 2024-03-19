#include "datamemory.h"

DataMemory::DataMemory(int size) {
    this->size = size;
}

// void store(int address, int value);
void DataMemory::store(int address, int value){
    if(address >= this->size){
        throw std::bad_alloc();
    }else{
        this->__memory[address] = value;
    }
}

int DataMemory::load(int address){
    if(address >= this->size){
        throw std::bad_alloc();
    }else{
        if(this->__memory.count(address)!=0){
            return this->__memory[address];
        }else{
            return 0x00;
        }
    }
}

void DataMemory::resize(int new_size){
    this->size = new_size;
}
