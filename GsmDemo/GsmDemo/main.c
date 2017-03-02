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
#include "speakerDriver.h"

int main(void)
{
	initializeUART(9600, 8);
	initializeSpeaker('B', 0b00000001);
	initLEDport();
	//char response[50];
	//char msg[50] = "This is a message for you ";
	//char num[8] = "61423402";
	char callback[20];
	setTextMode(callback);

	//sendSms(msg, num, callback);
	//getMessages(response);
	//sendSms(response, num);

	while (1)
	{
		toggleLED(7);
		_delay_ms(500);
	}
	
	playTone(500);
	
	
}

