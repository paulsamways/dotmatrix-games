#include <program.h>
#include <DMD2.h>

class SnakeProgram : public Program {
private:
    SoftDMD &dmd;
    DMD_TextBox tb;
    const char *MESSAGE = "SNAKE";

public:
    SnakeProgram(SoftDMD &dmd)
        : dmd(dmd),tb(dmd, 1, 4) {}

    void init() {
        tb.print(MESSAGE);
    };
    void step() { 

    };
};


// uint8_t WIDTH = 16;
// uint8_t HEIGHT = 32;

// #define BTN_UP PIN2
// #define BTN_DOWN PIN3
// #define BTN_LEFT PIN4
// #define BTN_RIGHT PIN5

// #define DIR_UP (1 << 0)
// #define DIR_DOWN (1 << 1)
// #define DIR_LEFT (1 << 2)
// #define DIR_RIGHT (1 << 3)

// struct Coordinate {
//     uint8_t x, y;
// };
// struct Coordinate coordinate_up(struct Coordinate c) {
//     return Coordinate { c.x, uint8_t(c.y > 0 ? c.y-1 : HEIGHT-1)};
// }
// struct Coordinate coordinate_down(struct Coordinate c) {
//     return Coordinate { c.x, uint8_t(c.y < HEIGHT-1 ? c.y+1 : 0 )};
// }
// struct Coordinate coordinate_left(struct Coordinate c) {
//     return Coordinate { uint8_t(c.x > 0 ? c.x-1 : WIDTH-1), c.y};
// }
// struct Coordinate coordinate_right(struct Coordinate c) {
//     return Coordinate { uint8_t(c.x < WIDTH-1 ? c.x+1 : 0), c.y};
// }
// struct Coordinate coordinate_move(struct Coordinate c, uint8_t direction) {
//     if ((direction & DIR_UP) > 0) {
//         return coordinate_up(c);
//     } else if ((direction & DIR_DOWN) > 0) {
//         return coordinate_down(c);
//     } else if ((direction & DIR_LEFT) > 0) {
//         return coordinate_left(c);
//     } else if ((direction & DIR_RIGHT) > 0) {
//         return coordinate_right(c);
//     } else {
//         return c;
//     }
// }

// struct Snake {
//     uint8_t direction;
//     struct SnakeBit *head;
//     struct SnakeBit *tail;

//     struct SnakeBit* discard;
// };
// struct SnakeBit {
//     struct Coordinate position;

//     struct SnakeBit* previous;
//     struct SnakeBit* next;
// };

// struct Snake *snake_new(uint8_t direction) {
//     SnakeBit *h = (SnakeBit*)malloc(sizeof(SnakeBit));
//     SnakeBit *t = (SnakeBit*)malloc(sizeof(SnakeBit));

//     h->position = Coordinate { uint8_t(WIDTH / 2), uint8_t(HEIGHT / 2) };
//     h->previous = NULL;
//     h->next = t;

//     t->position = coordinate_move(h->position, direction);
//     t->previous = h;
//     t->next = NULL;

//     Snake *s = (Snake*)malloc(sizeof(Snake));
//     s->direction = direction;
//     s->head = h;
//     s->tail = t;
//     s->discard = NULL;

//     return s;
// }

// void snake_move(struct Snake* snake, uint8_t direction, bool grow) {
//     if (direction == 0) {
//         direction = snake->direction;
//     }

//     SnakeBit *h = (SnakeBit*)malloc(sizeof(SnakeBit));
    
//     if ((direction & DIR_UP) > 0 && snake->direction != DIR_DOWN) {
//         snake->direction = DIR_UP;
//     } else if ((direction & DIR_DOWN) > 0 && snake->direction != DIR_UP) {
//         snake->direction = DIR_DOWN;
//     } else if ((direction & DIR_LEFT) > 0 && snake->direction != DIR_RIGHT) {
//         snake->direction = DIR_LEFT;
//     } else if ((direction & DIR_RIGHT) > 0 && snake->direction != DIR_LEFT) {
//         snake->direction = DIR_RIGHT;
//     }
//     h->position = coordinate_move(snake->head->position, snake->direction);
//     h->next = snake->head;
//     h->previous = NULL;

//     snake->head->previous = h;
//     snake->head = h;


//     if (!grow && snake->tail != NULL && snake->tail->previous != snake->head) {
//         snake->discard = snake->tail;

//         snake->tail = snake->tail->previous;
//         snake->tail->next = NULL;

//         snake->discard->previous = NULL;
//     }
// }

// bool snake_intersects(struct Snake* snake, struct Coordinate c) {
//     struct SnakeBit* sb;
//     sb = snake->head;
//     while (sb != NULL) {
//         if (sb->position.x == c.x && sb->position.y == c.y) {
//             return true;
//         }
//         sb = sb->next;
//     }
//     return false;
// }
// bool snake_intersects_self(struct Snake* snake) {
//     uint16_t x = 0;
//     uint32_t y = 0;

//     struct SnakeBit* sb = snake->head;
//     while (sb != NULL) {
//         uint16_t sb_x = 1U << sb->position.x;
//         uint32_t sb_y = 1UL << sb->position.y;

//         if ((x & sb_x) > 0 && (y & sb_y) > 0) {
//             struct SnakeBit* sbp = sb;
//             while (sbp != NULL) {
//                 Serial.print(sbp->position.x);
//                 Serial.print(",");
//                 Serial.print(sbp->position.y);
//                 Serial.print(" | ");

//                 sbp = sbp->previous;
//             }

//             Serial.print("\b\b = ");
//             Serial.print(x);
//             Serial.print(',');
//             Serial.print(y);
//             Serial.print(" & ");
//             Serial.print(sb_x);
//             Serial.print(',');
//             Serial.println(sb_y);
//             return true;
//         }
//         x |= sb_x;
//         y |= sb_y;
//         sb = sb->next;
//     }
//     return false;
// }

// void setupInput() {
//     pinMode(BTN_UP, INPUT_PULLUP);
//     pinMode(BTN_DOWN, INPUT_PULLUP);
//     pinMode(BTN_LEFT, INPUT_PULLUP);
//     pinMode(BTN_RIGHT, INPUT_PULLUP);
// }

// struct Snake *snake = snake_new(DIR_RIGHT);
// struct Coordinate *apple = NULL;
// uint8_t input_direction = 0;
// uint8_t growth = 0;

// void processInput() {
//     input_direction = 
//         (digitalRead(BTN_UP) ? 0 : DIR_UP) 
//         | (digitalRead(BTN_DOWN) ? 0 : DIR_DOWN)
//         | (digitalRead(BTN_LEFT) ? 0 : DIR_LEFT)
//         | (digitalRead(BTN_RIGHT) ? 0 : DIR_RIGHT);
// }

// void update() {
//     snake_move(snake, input_direction, growth);

//     if (snake_intersects_self(snake)) {
//         dmd.fillScreen(1);
//         delay(500);
//         dmd.fillScreen(0);
//     }

//     if (growth > 0) {
//         growth--;
//     }

//     if (apple != NULL) {
//         if (snake_intersects(snake, *apple)) {
//             growth += 1;
//             free(apple);
//             apple = NULL;
//         }
//     } else {
//         apple = (Coordinate*)malloc(sizeof(Coordinate));
//         apple->x = random(0, WIDTH-1);
//         apple->y = random(0, HEIGHT-1);
//     }
// }


// void setupRender() {
//     dmd.setBrightness(10);
//     dmd.begin();
// }

// void render() {
    
//     SnakeBit *h = snake->head;
//     while (h != NULL) {
//         dmd.setPixel(h->position.y, (WIDTH-1) - h->position.x);
//         h = h->next;
//     }

//     h = snake->discard;
//     while (h != NULL) {
//         dmd.setPixel(h->position.y, (WIDTH-1) - h->position.x, GRAPHICS_OFF);
//         struct SnakeBit *b = h;
//         h = h->next;
//         free(b);
//     }
//     snake->discard = NULL;

//     if (apple != NULL) {
//         dmd.setPixel(apple->y, (WIDTH-1) - apple->x);
//     }
// }