#ifndef SNAKE_H
#define SNAKE_H

#include <program.h>
#include <DMD2.h>

#define DIR_UP BTN_UP
#define DIR_DOWN BTN_DOWN
#define DIR_LEFT BTN_LEFT
#define DIR_RIGHT BTN_RIGHT

const uint8_t WIDTH = 32;
const uint8_t HEIGHT = 16;

struct Coordinate {
    uint8_t x, y;
    Coordinate move(uint8_t direction);
};

struct SnakeBit {
    Coordinate position;

    SnakeBit* next;

    ~SnakeBit();
    bool at(Coordinate c);
};

class Snake {
private:
    uint8_t direction;

    SnakeBit* head;
    SnakeBit* discard;
public:
    Snake(uint8_t initial_direction);
    ~Snake();

    bool intersects(Coordinate c);
    bool intersects_self();
    void change_direction(uint8_t new_direction, bool grow);

    void draw(DMDFrame &dmd);
};


class SnakeProgram : public Program {
private:
    DMDFrame &dmd;

    Snake* snake = nullptr;
    Coordinate* apple = nullptr;
    bool grow = false;
    uint8_t speed = 120;

public:
    SnakeProgram(DMDFrame &dmd);
    ~SnakeProgram();

    unsigned long tick() override;
    void init();
    void step(uint8_t btn_state);
};


#endif