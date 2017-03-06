/*
* MC35Commands.c
* Created: 20-02-2017 15:05:03
*  Author: Joachim
*/

#define CTRL_Z 26
#include <util/delay.h>
#include "MC35Commands.h"

void setTextMode()
{
	sendString("AT+CMGF=1");
	sendString("\r\n");
}

void enableEcho()
{
	sendString("ATE1\r\n");
}

void disableEcho()
{
	sendString("ATE0\r\n");
}

void sendSms(char* message, char* phoneNumber)
{
	//setTextMode(TODO);
	sendString("AT+CMGS=");
	sendString(phoneNumber);
	sendString("\r\n");
	sendString(message);
	sendByte(CTRL_Z);	
}

void getAllMessages()
{
	sendString("AT+CMGL=ALL\r\n");
}