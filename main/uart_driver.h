#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void uart_init(unsigned long baudrate);
void uart_log(const char* message);

#endif
