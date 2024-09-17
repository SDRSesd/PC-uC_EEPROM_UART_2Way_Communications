#ifndef _REAL_TIME_UART_DATA_H
#define _REAL_TIME_UART_DATA_H

#define F_CPU 16000000UL  // 16 MHz clock frequency of Arduino UNO
#define BAUD 2400
#define MYUBRR F_CPU/16/BAUD-1

void uart_init(unsigned int ubrr);
void init_timer0();

#endif
