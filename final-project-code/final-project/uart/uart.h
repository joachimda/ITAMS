/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 1/11 2011         *
***************************************/

#ifndef UART_H_
#define UART_H_

void uartInit(unsigned long BaudRate, unsigned char DataBit);
unsigned char uartCharReady();
char uartReadChar();
char uartReadCharWithTimeout(int timeout);
void uartSendChar(char Ch);
void uartSendString(char* String);
void uartSendInteger(int Number);
void uartFlush();
/**************************************/

#endif /* UART_H_ */