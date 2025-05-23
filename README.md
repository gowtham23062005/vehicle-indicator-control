# Vehicle Indicator Control System

This project implements a vehicle indicator control system using **MATLAB Simulink-generated C code** integrated into an **Arduino Uno** sketch. It handles left, right, and hazard light logic based on button inputs and LED outputs, using structured timing and state management.

---

## Project Files

- `Arduino drivers`- gpio_driver, pwm_driver, uart_driver, timer_driver
- `indicator_logic.c` - Core logic generated from Simulink
- `indicator_logic.h` – Header for logic functions and data structures
- `main.ino` – Arduino sketch that integrates the logic and handles hardware
- `README.md` – Project documentation

---

## Objective

Develop a real-time vehicle indicator system that supports:
- Left indicator
- Right indicator
- Hazard mode (both indicators blink)
- Blinking every 300ms during active mode
- Mode switching only after 1 second in the current state

---

## Hardware Requirements

- Arduino Uno
- 2 Push Buttons (for Left and Right)
- 2 LEDs (Left and Right indicators)
- 220Ω resistors
- Breadboard & Jumper wires
- USB cable

---

## Pin Configuration

| Component      | Arduino Pin |
|----------------|-------------|
| Left Button    | 2           |
| Right Button   | 3           |
| Left LED       | 8           |
| Right LED      | 9           |

---

## System Behavior

| Input Condition           | System Mode     | LED Behavior               |
|---------------------------|------------------|-----------------------------|
| No buttons pressed        | Idle             | All LEDs OFF               |
| Left button pressed       | Left Indicator   | Left LED blinks @ 300ms    |
| Right button pressed      | Right Indicator  | Right LED blinks @ 300ms   |
| Both buttons pressed      | Hazard Mode      | Both LEDs blink @ 300ms    |

> The system waits 1 second in the current state before accepting a new input state.

---

## How to Use

1. Clone this repository:
   ```bash
   git clone https://github.com/gowtham23062005/vehicle-indicator-control.git
   cd vehicle-indicator-control
2. Open main.ino in the Arduino IDE.
3. Connect the hardware as per the pin configuration.
4. Upload the sketch to your Arduino Uno.
5. Open Serial Monitor (baud rate: 9600) to view logs.
6. Press buttons to test each mode.

## Software Tools

1. MATLAB SIMULINK
2. ARDUINO IDE
