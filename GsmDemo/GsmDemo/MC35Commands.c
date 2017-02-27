/*
 * MC35Commands.c
 * Created: 20-02-2017 15:05:03
 *  Author: Joachim
 */ 

#define CTRL_Z 26
#include "MC35Commands.h"

void setTextMode()
{
	sendString("AT+CMGF=1");
	sendString("\r\n");
}

void sendSms(char* message, char* phoneNumber)
{
	//setTextMode();
	sendString("AT+CMGS=");
	sendString(phoneNumber);
	sendString("\r\n");
	sendString(message);
	sendChar(CTRL_Z);
}

char * getMessages()
{
	sendString("AT+CMGL=ALL");	
	
	char recieved[200];
	while(charReady())
	{
		readChar();	
	}
}