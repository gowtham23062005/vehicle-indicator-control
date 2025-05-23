#include "gpio_driver.h"
#include "uart_driver.h"
#include "pwm_driver.h"
#include "timer_driver.h"

extern "C" {
  #include "indicator_logic.h"
}

void setup() {
  gpio_init();
  uart_init(9600);
  pwm_init();
  indicator_logic_initialize();

  uart_log("System Ready - Press buttons for 1 second");

  // Quick LED test
  write_left_led(true);
  write_right_led(true);
  delay(200);
  write_left_led(false);
  write_right_led(false);
}

void loop() {
  static unsigned long lastSchedulerTime = 0;
  unsigned long currentTime = millis();

  if (is_100ms_elapsed()) {
    bool left = read_left_button() == LOW;
    bool right = read_right_button() == LOW;
    bool blink = get_blink300_state();

    static bool leftPrev = false;
    static bool rightPrev = false;
    static unsigned long leftPressTime = 0;
    static unsigned long rightPressTime = 0;
    static bool leftTriggered = false;
    static bool rightTriggered = false;

    // Track press time for 1s detection
    if (left && !leftPrev) {
      leftPressTime = currentTime;
      uart_log("LEFT: Press detected");
    } else if (!left && leftPrev) {
      leftTriggered = false;
      uart_log("LEFT: Release detected");
    }

    if (right && !rightPrev) {
      rightPressTime = currentTime;
      uart_log("RIGHT: Press detected");
    } else if (!right && rightPrev) {
      rightTriggered = false;
      uart_log("RIGHT: Release detected");
    }

    // Check for hazard activation/deactivation
    if (left && right && !leftTriggered && !rightTriggered &&
        (currentTime - leftPressTime >= 1000) &&
        (currentTime - rightPressTime >= 1000)) {

      leftTriggered = true;
      rightTriggered = true;

      if (!(indicator_logic_Y.LED_Left && indicator_logic_Y.LED_Right)) {
        uart_log("HAZARD: Activated (1s press)");
      } else {
        uart_log("HAZARD: Deactivated (1s press)");
      }
    }

    // Simulink input
    indicator_logic_U.LeftBtn = (left && (currentTime - leftPressTime >= 1000) && !leftTriggered);
    indicator_logic_U.RightBtn = (right && (currentTime - rightPressTime >= 1000) && !rightTriggered);
    indicator_logic_U.Blink300 = blink;

    // Mark triggers to avoid repeated pulses
    if (indicator_logic_U.LeftBtn) leftTriggered = true;
    if (indicator_logic_U.RightBtn) rightTriggered = true;

    indicator_logic_step();

    // Output to LEDs
    write_left_led(indicator_logic_Y.LED_Left);
    write_right_led(indicator_logic_Y.LED_Right);

    // Logging same as your format
    if (indicator_logic_Y.LED_Left && indicator_logic_Y.LED_Right) {
      uart_log("BLINK: L_ON R_ON");
    } else if (indicator_logic_Y.LED_Left) {
      uart_log("BLINK: L_ON R_OFF");
    } else if (indicator_logic_Y.LED_Right) {
      uart_log("BLINK: L_OFF R_ON");
    } else {
      uart_log("BLINK: L_OFF R_OFF");
    }

    leftPrev = left;
    rightPrev = right;
  }
}
