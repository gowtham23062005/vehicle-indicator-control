#include <Arduino.h>
#include "gpio_driver.h"

// Define pin numbers
const int LEFT_BUTTON_PIN = 2;
const int RIGHT_BUTTON_PIN = 3;
const int LEFT_LED_PIN = 5;
const int RIGHT_LED_PIN = 6;

void gpio_init() {
  pinMode(LEFT_BUTTON_PIN, INPUT);
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
}

bool read_left_button() {
  return digitalRead(LEFT_BUTTON_PIN);
}

bool read_right_button() {
  return digitalRead(RIGHT_BUTTON_PIN);
}

void write_left_led(bool state) {
  digitalWrite(LEFT_LED_PIN, state ? HIGH : LOW);
}

void write_right_led(bool state) {
  digitalWrite(RIGHT_LED_PIN, state ? HIGH : LOW);
}
