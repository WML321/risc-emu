#include "reservationstation.h"
#include <iostream>

std::unordered_map<std::string, std::vector<ReservationStation>> ReservationStations::RS_gingleton;

bool ReservationStations::flag = false;

ReservationStations::ReservationStations(int adders_number, int multipliers_number, int dividers_number, int loaders_number, int fp_adders_number, int fp_multipliers_number, int fp_dividers_number, int fp_loaders_number){
    if(!ReservationStations::flag){
        this->set_type_number(adders_number, "ADD");
        this->set_type_number(multipliers_number, "MULT");
        this->set_type_number(dividers_number, "DIV");
        this->set_type_number(loaders_number, "LD");
        this->set_type_number(fp_adders_number, "FADD");
        this->set_type_number(fp_multipliers_number, "FMULT");
        this->set_type_number(fp_dividers_number, "FDIV");
        this->set_type_number(fp_loaders_number, "FLD");

        ReservationStations::RS_gingleton["add"] = address;
        ReservationStations::RS_gingleton["mul"] = multipliers;
        ReservationStations::RS_gingleton["div"] = dividers;
        ReservationStations::RS_gingleton["ld"] = loaders;
        ReservationStations::RS_gingleton["fadd"] = fp_adders;
        ReservationStations::RS_gingleton["fmul"] = fp_multipliers;
        ReservationStations::RS_gingleton["fdiv"] = fp_dividers;
        ReservationStations::RS_gingleton["fld"] = fp_loaders;
    }else{
        ReservationStations::flag = true;
        address = ReservationStations::RS_gingleton["add"];
        multipliers = ReservationStations::RS_gingleton["mul"];
        dividers = ReservationStations::RS_gingleton["div"];
        loaders = ReservationStations::RS_gingleton["ld"];
        fp_adders = ReservationStations::RS_gingleton["fadd"];
        fp_multipliers = ReservationStations::RS_gingleton["fmul"];
        fp_dividers = ReservationStations::RS_gingleton["fdiv"];
        fp_loaders = ReservationStations::RS_gingleton["fld"];
    }

}

void ReservationStations::set_type_number(int n, std::string type){
    for(int i=0; i<n ; i++){
        std::string name_ = type + std::to_string(i);
        address.push_back(ReservationStation(name_));
    }

    if(type.compare("ADD")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            address.push_back(ReservationStation(name_));
        }
    }else if(type.compare("MULT")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            multipliers.push_back(ReservationStation(name_));
        }
    }else if(type.compare("DIV")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            dividers.push_back(ReservationStation(name_));
        }
    }else if(type.compare("LD")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            loaders.push_back(ReservationStation(name_));
        }
    }else if(type.compare("FADD")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            fp_adders.push_back(ReservationStation(name_));
        }
    }else if(type.compare("FMULT")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            fp_multipliers.push_back(ReservationStation(name_));
        }
    }else if(type.compare("FLD")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            fp_loaders.push_back(ReservationStation(name_));
        }
    }else if(type.compare("FDIV")){
        for(int i=0; i<n ; i++){
            std::string name_ = type + std::to_string(i);
            fp_dividers.push_back(ReservationStation(name_));
        }
    }
}

std::vector<ReservationStation> ReservationStations::get_function_units(std::string functional_unit){
    if(functional_unit.compare("add")){
        return this->address;
    }else if(functional_unit.compare("mult")){
        return this->multipliers;
    }else if(functional_unit.compare("div")){
        return this->dividers;
    }else if(functional_unit.compare("ld")){
        return this->loaders;
    }else if(functional_unit.compare("fadd")){
        return this->fp_adders;
    }else if(functional_unit.compare("fmult")){
        return this->fp_multipliers;
    }else if(functional_unit.compare("fdiv")){
        return this->fp_dividers;
    }else if(functional_unit.compare("fld")){
        return this->fp_loaders;
    }else{
        throw std::runtime_error("Unknown functional unit: " + functional_unit);
    }
}


ReservationStation ReservationStations::get_first_free(std::string functional_unit){
    auto fu_type = this->get_function_units(functional_unit);
    for(int i=0; i<fu_type.size(); i++){
        if(!fu_type[i].busy){
            return fu_type[i];
        }
    }
    return ReservationStation("nullptr");
}

std::vector<ReservationStation> ReservationStations::get_fus_of_thread(int thread_id){
    std::vector<ReservationStation> merged = ReservationStations::merge() ,res;

    for(int i=0; i<merged.size(); i++){
        if(merged[i].thread_id == thread_id){
            res.push_back(merged[i]);
        }
    }
    return res;
}

bool ReservationStations::all_empty(){
    std::vector<ReservationStation> merged = ReservationStations::merge();
    for(int i=0; i<merged.size(); i++){
        if(merged[i].busy){
            return false;
        }
    }
    return true;
}
