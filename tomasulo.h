#ifndef TOMASULO_H
#define TOMASULO_H

#include "reservationstation.h"
#include "register.h"
#include "registerstatus.h"
#include "instructionbuffer.h"
#include "datamemory.h"
#include "rtype_instruction.h"
#include "itype_instruction.h"
#include "stype_instruction.h"
#include "btype_instruction.h"
#include "utype_instruction.h"
#include "ujtype_instruction.h"

class Tomasulo
{
public:
    int __step=0, thread_id;
    bool stall=false;
   // InstructionBuffer IFQ;
   //RegisterFile Regs;
    //RegisterStatus RegisterStat;
    //ReservationStations RS;
    //DataMemory DM;

public:
    Tomasulo(int thread_id, int address_number, int multipliers_number, int dividers_number,
             int loaders_number, int fp_adders_number, int fp_multipliers_number, int fp_dividers_number,
             int fp_loaders_number);
    int step();
    void reset_steps();
    void issue();
    void execute();
    void write();
    void is_halted();
    int get_steps();
};

#endif // TOMASULO_H
