#include <Arduino.h>
#include "timer_driver.h"

unsigned long lastTick = 0;

bool is_100ms_elapsed() {
  if (millis() - lastTick >= 100) {
    lastTick = millis();
    return true;
  }
  return false;
}
