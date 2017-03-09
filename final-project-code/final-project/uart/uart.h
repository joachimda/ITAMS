/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 1/11 2011         *
***************************************/

#ifndef UART_H_
#define UART_H_

void uartInit();
unsigned char uartCharReady();
char uartReadChar();
char uartReadCharWithTimeout(int timeout);
void uartSendByte(unsigned char* Ch);
void uartSendString(char* String);
void uartSendInteger(int number);
void uartFlush();
/**************************************/

#endif /* UART_H_ */