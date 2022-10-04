#include <program.h>
#include <DMD2.h>
#include <GravityRtc.h>

class ClockProgram : public Program {
private:
    SoftDMD &dmd;
    GravityRtc rtc;
    
    bool tock = false;

public:
    ClockProgram(SoftDMD &dmd)
        : dmd(dmd) {}

    unsigned long tick() override {
        return 1000;
    } 

    void init() {
        rtc.setup();
        // rtc.adjustRtc(F(__DATE__), F(__TIME__)); 
    };

    void step() {
        rtc.read();

        dmd.drawString(3, 4,  rtc.hour < 10 ? "0" + String(rtc.hour) : rtc.hour);
        dmd.drawString(18, 4, rtc.minute < 10 ? "0" + String(rtc.minute) : rtc.minute);

        for (uint8_t i = 15; i <= 16; i++) {
            dmd.setPixel(i, 5, tock ? GRAPHICS_ON : GRAPHICS_OFF);
            dmd.setPixel(i, 6, tock ? GRAPHICS_ON : GRAPHICS_OFF);
            dmd.setPixel(i, 8, tock ? GRAPHICS_ON : GRAPHICS_OFF);
            dmd.setPixel(i, 9, tock ? GRAPHICS_ON : GRAPHICS_OFF);
        }

        if (rtc.second < 2) {
            dmd.drawLine(0,15,31,15, GRAPHICS_OFF);
        } else {
            dmd.drawLine(1, 15, rtc.second / 2, 15);
        }
        
        tock = !tock;
    };
};