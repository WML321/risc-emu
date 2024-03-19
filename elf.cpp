#include "elf.h"
#include <cstdint>

ELF::ELF(std::string filename):file(filename),filename(filename), symbols(), eheader(), pheader(), sections(), ordered_sections(), unknown_instructions() {}

void ELF::load_program(Program* prog){
    std::cout<< "\nLoading program into memory..." << std::endl;
    uintptr_t next_addr = 0;

}


std::string ELF::read_byte(int n, bool to_int){
    std::string data = Utils::read_bytes(n, &(this->file));
    if (!to_int) {
        return data;
    } else if (eheader.count("EI_DATA")) {
        std::string endian = eheader["EI_DATA"];
        return std::to_string(Utils::from_bytes(data, endian));
    } else {
        return std::to_string(Utils::from_bytes(data, "little"));
    }
}
