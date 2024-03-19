#ifndef RESERVATIONSTATION_H
#define RESERVATIONSTATION_H
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

class ReservationStation
{
public:
    std::string Vj, Vk, Qj, Qk, A;
    std::string name, time_remaning, result;
    bool busy = false;
    std::string instruction; // 类型待定
    int thread_id;



public:
    ReservationStation(std::string name){
        this->name = name;
    }
    void clear(){
        this->A = this->Qj = this->Qk = this->Vj = this->Vk = "nullptr";
        this->time_remaning = this->result = "nullptr";
        this->busy = false;
        this->instruction = "nullptr";
    }
};

class ReservationStations{
public:
    //std::list<std::unordered_map<std::string, std::string>> addres, multipliers, dividers, loaders, fp_addres, fp_multipliers, fp_dividers, fp_loaders;
    //int adders_number, multipliers_number, dividers_number, loaders_number, fp_adders_number, fp_multipliers_number, fp_dividers_number, fp_loaders_number;
    std::vector<ReservationStation> address, multipliers, dividers, loaders, fp_adders, fp_multipliers, fp_dividers, fp_loaders;
public:
    static std::unordered_map<std::string, std::vector<ReservationStation>> RS_gingleton;
    static bool flag;
    ReservationStations(int adders_number, int multipliers_number, int dividers_number, int loaders_number, int fp_adders_number, int fp_multipliers_number, int fp_dividers_number, int fp_loaders_number);
    std::vector<ReservationStation> get_function_units(std::string functional_unit);
    ReservationStation get_first_free(std::string functional_unit);
    std::vector<ReservationStation> get_fus_of_thread(int thread_id);
    bool all_empty();
    void set_type_number(int n, std::string type);

    std::vector<ReservationStation> merge(){
        std::vector<ReservationStation> merged;

        // 将 address 合并到 merged
        merged.insert(merged.end(), address.begin(), address.end());

        // 将 multipliers 合并到 merged
        merged.insert(merged.end(), multipliers.begin(), multipliers.end());

        // 将 dividers 合并到 merged
        merged.insert(merged.end(), dividers.begin(), dividers.end());

        // 将 loaders 合并到 merged
        merged.insert(merged.end(), loaders.begin(), loaders.end());

        // 将 fp_adders 合并到 merged
        merged.insert(merged.end(), fp_adders.begin(), fp_adders.end());

        // 将 fp_multipliers 合并到 merged
        merged.insert(merged.end(), fp_multipliers.begin(), fp_multipliers.end());

        // 将 fp_dividers 合并到 merged
        merged.insert(merged.end(), fp_dividers.begin(), fp_dividers.end());

        // 将 fp_loaders 合并到 merged
        merged.insert(merged.end(), fp_loaders.begin(), fp_loaders.end());
        return merged;
    }
    int size(){
        return this->address.size() + this->dividers.size()+ this->multipliers.size() +
               this->fp_adders.size() + this->fp_dividers.size() + this->fp_loaders.size() +
               this->loaders.size() + this->fp_multipliers.size();

    }
};

#endif // RESERVATIONSTATION_H
