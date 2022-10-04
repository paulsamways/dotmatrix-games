#ifndef PROGRAM_H
#define PROGRAM_H

#include <DMD2.h>

class Program {

public:

    virtual ~Program() { };

    void virtual init() { };

    void virtual step() { };

    unsigned long virtual tick() { 
        return 16;
    };
};

#endif