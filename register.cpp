#include "register.h"

Register::Register(std::string symbolic_name, std::string value, bool read_only):
                    symbolic_name(symbolic_name), value(value), read_only(read_only) {}

std::string Register::getValue(){
    return this->value;
}

void Register::setValue(std::string value){
    this->value = value;
}


RegisterFile::RegisterFile():PC(Register("PC")), IR(Register("IR")), IntRegisters(), FPRegisters(),
                                RA(Register("RA")), SP(Register("SP")){
    this->PC.setValue("0");

    Document document = Utils::openJson(".\\rf_config.json");

    const Value& IntRegs = document["IntRegisters"];

    for(SizeType i=0; i<IntRegs.Size();i++){
        const Value& int_reg = IntRegs[i];
        std::string symbolic_name = std::to_string(int_reg["symbolic_name"].GetInt());
        std::string value = "";
        bool read_only = false;
        if(int_reg.HasMember("value")){
            value = int_reg["value"].GetString();
        }
        if(int_reg.HasMember("read_only")){
            read_only = int_reg["read_only"].GetBool();
        }

        this->IntRegisters.push_back(Register(symbolic_name, value, read_only));
    }

    const Value& FRegs = document["FPRegisters"];
    for(SizeType i=0; i<FRegs.Size(); i++){
        const Value& fr_reg = FRegs[i];
        std::string symbolic_name = std::to_string(FRegs["symbolic_name"].GetInt());
        std::string value = "";
        bool read_only = false;
        if(FRegs.HasMember("value")){
            value = FRegs["value"].GetString();
        }
        if(FRegs.HasMember("read_only")){
            read_only = FRegs["read_only"].GetBool();
        }

        this->FPRegisters.push_back(Register(symbolic_name, value, read_only));

    }

    this->RA = this->IntRegisters[1];
    this->SP = this->IntRegisters[2];
}

std::string RegisterFile::readInt(int reg_name){
    return this->IntRegisters[reg_name].getValue();
}

std::string RegisterFile::readFP(int reg_name){
    return this->FPRegisters[reg_name].getValue();
}

void RegisterFile::writeInt(int reg_name, std::string value){
    this->IntRegisters[reg_name].setValue(value);
}

void RegisterFile::writeFP(int reg_name, std::string value){
    this->FPRegisters[reg_name].setValue(value);
}


std::string RegisterFile::read(int reg_name, std::string reg_type){
    if(reg_type.compare("fp")){
        return this->readFP(reg_name);
    }else{
        return this->readInt(reg_name);
    }
}

void RegisterFile::write(int reg_name, std::string value,std::string reg_type){
    if(reg_type.compare("fp")){
        this->writeFP(reg_name, value);
    }else{
        this->writeInt(reg_name, value);
    }
}
