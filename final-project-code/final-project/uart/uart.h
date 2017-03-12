
#ifndef UART_H_
#define UART_H_

#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

extern char dataArray[];
void clearDataArray();
void uartInit();
unsigned char uartCharReady();
unsigned char uartReadChar();
unsigned char uartReadCharWithTimeout(int timeout);
void uartSendByte(unsigned char charToSend);
void uartSendString(unsigned char* string);
void uartSendInteger(int number);
void uartFlush();

#endif /* UART_H_ */