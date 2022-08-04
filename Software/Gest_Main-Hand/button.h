/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
#include "sensors.h"
#include "timer.h"
#include "config.h"

void button_setup() {
  pinMode(BUTTON, INPUT_PULLUP);
}

int button_pressed() {
  int output = digitalRead(BUTTON);
  return output;
}
