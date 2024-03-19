#include "registerstatus.h"

RegisterStatus::RegisterStatus() {
    this->int_reg_status.resize(32);
    this->fp_reg_status.resize(32);
}

//void add_int_status(int register_, std::string operation);
void RegisterStatus::add_int_status(int register_, std::string operation){
    this->int_reg_status[register_] = operation;
}

void RegisterStatus::add_fp_status(int register_, std::string operation){
    this->fp_reg_status[register_] = operation;
}

void RegisterStatus::add_status(int register_, std::string operation, std::string reg_type){
    if(reg_type.compare("fp")){
        this->add_fp_status(register_, operation);
    }else{
        this->add_int_status(register_, operation);
    }
}

void RegisterStatus::remove_int_status(int register_){
    this->int_reg_status[register_] = "";
}

void RegisterStatus::remove_fp_status(int register_){
    this->fp_reg_status[register_] = "";
}

void RegisterStatus::remove_status(int register_, std::string reg_type){
    if(reg_type.compare("fp")){
        this->remove_fp_status(register_);
    }else{
        this->remove_int_status(register_);
    }
}

std::string RegisterStatus::get_int_status(int register_){
    return this->int_reg_status[register_];
}

std::string RegisterStatus::get_fp_status(int register_){
    return this->fp_reg_status[register_];
}


std::string RegisterStatus::get_status(int register_, std::string reg_type){
    if(reg_type.compare("fp")){
        this->get_fp_status(register_);
    }else{
        this->get_int_status(register_);
    }
    return ""; // 这里还有问题
}
