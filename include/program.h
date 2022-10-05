#ifndef PROGRAM_H
#define PROGRAM_H

#include <DMD2.h>

#define PIN_DISPLAY_NOE 9
#define PIN_DISPLAY_A 10
#define PIN_DISPLAY_B 12
#define PIN_DISPLAY_SCK 8
#define PIN_DISPLAY_CLK 13
#define PIN_DISPLAY_DATA 11

#define PIN_BTN_UP 2
#define PIN_BTN_DOWN 3
#define PIN_BTN_LEFT 4
#define PIN_BTN_RIGHT 5
#define PIN_BTN_A 6
#define PIN_BTN_B 7

#define BTN_UP (1 << 2)
#define BTN_DOWN (1 << 3)
#define BTN_LEFT (1 << 4)
#define BTN_RIGHT (1 << 5)
#define BTN_A (1 << 6)
#define BTN_B (1 << 7)

#define SETBIT(x,y)   (x |= (y))  //Set bit y in byte x
#define CLEARBIT(x,y) (x &= (~y)) //Clear bit Y in byte x
#define CHECKBIT(x,y) (x & (y))   //True if bit y of byte x=1.

class Program {

public:

    virtual ~Program() { };

    void virtual init() { };

    void virtual step(uint8_t btn_state) { };

    unsigned long virtual tick() { 
        return 16;
    };
};

#endif