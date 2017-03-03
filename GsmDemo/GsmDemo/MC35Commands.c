/*
* MC35Commands.c
* Created: 20-02-2017 15:05:03
*  Author: Joachim
*/

#define CTRL_Z 26
#include <util/delay.h>
#include "MC35Commands.h"

void setTextMode(char * callback)
{
	unsigned int i = 0;

	sendString("AT+CMGF=1");
	sendString("\r\n");

	while(charReady())
	{
		_delay_ms(50);
		char test = readChar();
		callback[i] = test;
		i++;
	}
}

void enableEcho(char* callback)
{
	unsigned int i = 0;

	sendString("ATE1\r\n");
	while(charReady())
	{
		_delay_ms(50);
		char test = readChar();
		callback[i] = test;
		i++;
	}
}

void disableEcho(char* callback)
{
	unsigned int i = 0;

	sendString("ATE0\r\n");
	while(charReady())
	{
		callback[i] = readChar();
		i++;
	}
}

void sendSms(char* message, char* phoneNumber, char* callback)
{
	unsigned int i = 0;
	//setTextMode(TODO);
	sendString("AT+CMGS=");
	sendString(phoneNumber);
	sendString("\r\n");
	sendString(message);
	//flushRxBuffer();
	sendChar(CTRL_Z);
	
	while(charReady())
	{
		_delay_ms(50);
		callback[i] = readChar();
		i++;
	}
}

void getMessages(char* response)
{
	sendString("AT+CMGL=ALL\r\n");
	unsigned int i = 0;
	while(charReady())
	{
		_delay_ms(100);
		response[i] = readChar();
		i++;
	}
}