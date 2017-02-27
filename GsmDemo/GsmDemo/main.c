/*
* GsmDemo.c
* Created: 20-02-2017 12:59:12
* Author : Joachim
*/

#include <avr/io.h>
#define  F_CPU 3686400
#include <util/delay.h>
#include "uartDriver.h"
#include "ledDriver.h"
#include "MC35Commands.h"

int main(void)
{
	initializeUART(9600, 8);
	initLEDport();
	char response[50];
	char msg[50] = "This is a message for you ";
	char num[12] = "24464105";
	sendSms(msg, num);
	getMessages(response);
	sendSms(response, num);

	while (1)
	{
		toggleLED(7);
		_delay_ms(500);
	}
}

