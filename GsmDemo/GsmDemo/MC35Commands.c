/*
 * MC35Commands.c
 *
 * Created: 20-02-2017 15:05:03
 *  Author: Joachim
 */ 

#define CTRL_Z 26

#include "MC35Commands.h"

void sendMessage(char* message, char* phoneNumber)
{
	sendString("AT+CMGS=");
	sendString(phoneNumber);
	sendString(message);
	SendChar(CTRL_Z);
}