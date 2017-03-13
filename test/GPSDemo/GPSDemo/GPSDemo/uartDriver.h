#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

void initializeUART(unsigned long BaudRate, unsigned char DataBit);

unsigned char charReady();

char readChar();

void sendChar(char chr);

void sendString(char* str);

void SendInteger(int num);

#endif /* UARTDRIVER_H_ */