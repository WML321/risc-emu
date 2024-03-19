#ifndef REGISTERSTATUS_H
#define REGISTERSTATUS_H
#include<vector>
#include<string>
class RegisterStatus
{
public:
    std::vector<std::string> int_reg_status;
    std::vector<std::string> fp_reg_status;
public:
    RegisterStatus();
    void add_int_status(int register_, std::string operation);
    void add_fp_status(int register_, std::string operation);
    void add_status(int register_, std::string operation, std::string reg_type);
    void remove_int_status(int register_);
    void remove_fp_status(int register_);
    void remove_status(int register_, std::string reg_type);
    std::string get_int_status(int register_);
    std::string get_fp_status(int register_);
    std::string get_status(int register_, std::string reg_type);
};

#endif // REGISTERSTATUS_H
