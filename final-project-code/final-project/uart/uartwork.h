/*
* uartDriver.h
* Created: 20-02-2017 13:10:01
*  Author: Joachim
*/


#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define DATA_SIZE 50
volatile char data[DATA_SIZE];

void uartInit(unsigned long BaudRate, unsigned char DataBit);
char readChar();
void uartSendString(unsigned char* s);
void uartSendByte(unsigned char chr);
void SendInteger(int num);
void uartFlush();


#endif /* UARTDRIVER_H_ */