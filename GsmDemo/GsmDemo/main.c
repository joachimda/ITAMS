/*
* GsmDemo.c
*
* Created: 20-02-2017 12:59:12
* Author : Joachim
*/

#include <avr/io.h>
#define  F_CPU 3686400
#include <util/delay.h>
#include "uartDriver.h"
#include "ledDriver.h"

#define CTRL_Z 26

void SendMessage(char* message, char* phoneNumber);

int main(void)
{
	InitializeUART(9600, 8);
	initLEDport(); // PORTC
	
	char msg[50] = "HElloeee0";
	char num[11] = "+4561423402";
	
	while (1)
	{
	SendMessage(msg, num);
	_delay_ms(5000);
	}
}

void SendMessage(char* message, char* phoneNumber)
{
	SendString("AT+CMGS=");
	SendString(phoneNumber);
	SendString(message);
	SendChar(CTRL_Z);
}