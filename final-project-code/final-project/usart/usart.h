#ifndef USART_H_
#define USART_H_

#define F_CPU 3686400
#include <avr/io.h>

// Define baud rate
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char value;
/* This variable is volatile so both main and RX interrupt can use it.
It could also be a uint8_t type */

void usartInit();
void usartSendByte(uint8_t u8Data);
uint8_t usartReceiveByte();

#endif /* USART_H_ */