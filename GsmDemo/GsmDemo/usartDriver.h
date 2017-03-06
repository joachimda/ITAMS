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

void initializeUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char charReady();
char readChar();
void sendString(unsigned char* s);
void sendByte(unsigned char chr);
void SendInteger(int num);
void flushRxBuffer();
#endif /* UARTDRIVER_H_ */