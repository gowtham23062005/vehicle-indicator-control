#include <Arduino.h>
#include "pwm_driver.h"

unsigned long lastBlinkTime = 0;
bool blinkState = false;

void pwm_init() {
  lastBlinkTime = millis();
}

bool get_blink300_state() {
  if (millis() - lastBlinkTime >= 300) {
    blinkState = !blinkState;
    lastBlinkTime = millis();
  }
  return blinkState;
}
