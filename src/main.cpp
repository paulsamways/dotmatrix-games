#include <Arduino.h>

#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>

#include <program.h>
#include "snake.cpp"
#include "clock.cpp"

const uint8_t *FONT = SystemFont5x7;

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

SoftDMD dmd(1, 1, PIN_DISPLAY_NOE, PIN_DISPLAY_A, PIN_DISPLAY_B, PIN_DISPLAY_SCK, PIN_DISPLAY_CLK, PIN_DISPLAY_DATA);

DMD_TextBox box(dmd);
uint8_t pIndex = 0;
const uint8_t P_MAX = 1;
Program *p;

void next_program() {
  if (p != NULL) {
      delete p;
      p = NULL;
      dmd.clearScreen();
    }

  pIndex = (pIndex >= P_MAX) ? 0 : pIndex + 1;
  switch (pIndex) {
    default:
    case 0:
      p = new ClockProgram(dmd);
      break;
    case 1:
      p = new SnakeProgram(dmd);
      break;
  }

  p ->init();
}


volatile uint8_t btn_state = 0;

ISR (PCINT2_vect) {
  btn_state = ~(PIND & ~3);
}

void setup()
{
  Serial.begin(115200);

  for (uint8_t p = PIN_BTN_UP; p <= PIN_BTN_B; p++) {
    pinMode(p, INPUT_PULLUP);
  }

  PCICR |= 0b00000100;  // Enable PinChangeInterrupt on Port D
  PCMSK2 |= 0b11111100; // Interrupt only on Pins 2-7
  
  dmd.setBrightness(10);
  dmd.selectFont(FONT);
  dmd.begin();

  next_program();
}

unsigned long game_delay = 16;
unsigned long game_millis = 0;
unsigned long reset_millis = 0;

void loop()
{
  unsigned long now = millis();

  if (CHECKBIT(btn_state, BTN_A) && now-reset_millis > 1000) {
    reset_millis = now;
    next_program();
  }

  if (now - game_millis > p->tick()) {
    game_millis = now;
    p->step();
  }
}