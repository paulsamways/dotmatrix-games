#include <Arduino.h>

#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>

#include <program.h>
#include "snake.h"
#include "clock.h"

const uint8_t *FONT = SystemFont5x7;

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
    game_millis = 0;
    next_program();
  }

  if (now - game_millis > p->tick()) {
    game_millis = now;
    p->step(btn_state);
  }
}