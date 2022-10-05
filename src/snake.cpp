#include <program.h>
#include <DMD2.h>
#include "snake.h"

Coordinate Coordinate::move(uint8_t direction) {
    if ((direction & DIR_UP) > 0) {
        return Coordinate { x, uint8_t(y > 0 ? y-1 : HEIGHT-1)};
    } else if ((direction & DIR_DOWN) > 0) {
        return Coordinate { x, uint8_t(y < HEIGHT-1 ? y+1 : 0 )};
    } else if ((direction & DIR_LEFT) > 0) {
        return Coordinate { uint8_t(x > 0 ? x-1 : WIDTH-1), y};
    } else if ((direction & DIR_RIGHT) > 0) {
        return Coordinate { uint8_t(x < WIDTH-1 ? x+1 : 0), y};
    } else {
        return Coordinate { x, y };
    }
}

SnakeBit::~SnakeBit() {
    if (next) {
        delete next;
    }
}
bool SnakeBit::at(Coordinate c) {
    auto sb = this;
    while (sb) {
        if (sb->position.x == c.x && sb->position.y == c.y) {
            return true;
        }
        sb = sb->next;
    }
    return false;
}

Snake::Snake(uint8_t initial_direction)
    : direction(initial_direction)
    , discard(nullptr) {

    head = new SnakeBit();

    head->position = Coordinate { uint8_t(WIDTH / 2), uint8_t(HEIGHT / 2) };
    head->next = new SnakeBit();
    head->next->position = head->position.move(direction);
}
Snake::~Snake() {
    delete head;
    if (discard) {
        delete discard;
    }
}

bool Snake::intersects(Coordinate c) {
    return head->at(c);
}

bool Snake::intersects_self() {
    auto sb = head;
    while (sb) {      
        if (sb->next && sb->next->at(sb->position)) {
            return true;
        }
        sb = sb->next;
    }
    return false;
}

void Snake::change_direction(uint8_t new_direction, bool growing) {
    if (new_direction == 0) {
        new_direction = direction;
    }
    
    if ((new_direction & DIR_UP) > 0 && direction != DIR_DOWN) {
        direction = DIR_UP;
    } else if ((new_direction & DIR_DOWN) > 0 && direction != DIR_UP) {
        direction = DIR_DOWN;
    } else if ((new_direction & DIR_LEFT) > 0 && direction != DIR_RIGHT) {
        direction = DIR_LEFT;
    } else if ((new_direction & DIR_RIGHT) > 0 && direction != DIR_LEFT) {
        direction = DIR_RIGHT;
    }

    auto h = new SnakeBit();
    h->position = head->position.move(direction);
    h->next = head;
    head = h;

    if (!growing) {
        auto new_end = head;
        while (new_end->next && new_end->next->next) {
            new_end = new_end->next;
        }
        discard = new_end->next;
        new_end->next = nullptr;
    }
}

void Snake::draw(DMDFrame &dmd) {
    auto h = head;
    while (h) {
        dmd.setPixel(h->position.x, h->position.y);
        h = h->next;
    }

    h = discard;
    while (h) {
        dmd.setPixel(h->position.x, h->position.y, GRAPHICS_OFF);
        h = h->next;
    }

    delete discard;
    discard = nullptr;
}

SnakeProgram::SnakeProgram(DMDFrame &dmd)
    : dmd(dmd) {}

SnakeProgram::~SnakeProgram() {
    delete snake;
}

unsigned long SnakeProgram::tick() {
    return speed;
} 

void SnakeProgram::init() {
    snake = new Snake(DIR_RIGHT);
}

void SnakeProgram::step(uint8_t btn_state) { 
    snake->change_direction(btn_state, grow);
    grow = false;

    if (snake->intersects_self()) {
        delete snake;
        if (apple) {
            delete apple;
            apple = nullptr;
        }
        grow = false;
        speed = 120;
        snake = new Snake(DIR_RIGHT);

        dmd.clearScreen();
        return;
    }

    if (apple) {
        if (snake->intersects(*apple)) {
            grow = true;
            speed = speed > 33 ? speed - 1 : 33;

            delete apple;
            apple = nullptr;
        }
    } else {
        apple = new Coordinate();
        apple->x = random(0, WIDTH-1);
        apple->y = random(0, HEIGHT-1);
    }

    snake->draw(dmd);
    if (apple) {
        dmd.setPixel(apple->x, apple->y);
    }
};