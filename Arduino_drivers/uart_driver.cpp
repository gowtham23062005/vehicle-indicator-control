#include <Arduino.h>
#include "uart_driver.h"

void uart_init(unsigned long baudrate) {
  Serial.begin(baudrate);
}

void uart_log(const char* message) {
  Serial.println(message);
}
