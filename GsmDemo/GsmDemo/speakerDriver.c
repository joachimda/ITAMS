/*
* speakerDriver.c
*
* Created: 27-02-2017 22:26:55
*  Author: Joachim
*/
#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
#include "speakerDriver.h"

void initializeSpeaker(char port, unsigned char pattern)
{
	switch (port)
	{
		case 'A':
		DDRA = pattern;
		break;
		case 'B':
		DDRB = pattern;
		break;
		case 'C':
		DDRC = pattern;
		break;
		case 'D':
		break;
		DDRD = pattern;
		break;
		default:
		DDRB = pattern;
		break;
	}
}

void playTone(unsigned int freq)
{

	unsigned int milisec = 1000/freq;

	unsigned int outer = 100;
	unsigned int inner = 2;
	for (unsigned int i = 0;i<outer; i++)
	{
		for (unsigned int n = 0; n< inner;n++)
		{
			PORTB = ~PORTB;
			_delay_ms(milisec);
		}
	}
}