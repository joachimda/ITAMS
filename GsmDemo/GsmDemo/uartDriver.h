/*
* uartDriver.h
*
* Created: 20-02-2017 13:10:01
*  Author: Joachim
*/


#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_
void InitializeUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
#endif /* UARTDRIVER_H_ */