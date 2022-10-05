#ifndef CLOCK_H
#define CLOCK_H

#include <GravityRtc.h>
#include "program.h"

class ClockProgram : public Program {
private:
    SoftDMD &dmd;
    GravityRtc rtc;
    
    bool tock = false;

public:
    ClockProgram(SoftDMD &dmd);
    unsigned long tick() override;

    void init();
    void step(uint8_t btn_state);
};

#endif