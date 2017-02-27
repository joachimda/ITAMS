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
	
	char msg[50] = "This is a message ";
	char num[12] = "61423402";
	sendSms(msg, num);
		
	while (1)	{}
		
}

