#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

void gpio_init();
bool read_left_button();
bool read_right_button();
void write_left_led(bool state);
void write_right_led(bool state);

#endif
