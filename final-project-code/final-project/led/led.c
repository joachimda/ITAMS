#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "led.h"

const unsigned char OUTPUT = 0b11111111;
const unsigned char DEFAULT_OFF = 0xFF;
const char LED_PORT = 'B';

void ledInit()
{
	switch (LED_PORT)
	{
		case 'A':
		DDRA = OUTPUT;
		PORTA = DEFAULT_OFF;
		break;
		case 'B':
		DDRB = OUTPUT;
		PORTB = DEFAULT_OFF;
		break;
		case 'C':
		DDRC = OUTPUT;
		PORTC = DEFAULT_OFF;
		break;
		case 'D':
		break;
		DDRD = OUTPUT;
		PORTD = DEFAULT_OFF;
		break;
		default:
		DDRC = OUTPUT;
		PORTC = DEFAULT_OFF;
		break;
	}
}

void ledToggleAll()
{
	switch(LED_PORT)
	{
		case 'A':
		PORTA = ~PORTA;
		break;
		case 'B':
		PORTB = ~PORTB;
		break;
		case 'C':
		PORTC = ~PORTC;
		break;
		case 'D':
		PORTD = ~PORTD;
		break;
	}
}

void ledReadyForRequest()
{
	for (int i = 0; i < 4; i++)
	{
		ledToggleAll();
		_delay_ms(50);
	}
}

void ledMessageReceived()
{
	unsigned char mask;
	for(int i = 0; i < 8; i++)
	{
		mask = ~(0b00000001 << i);
		switch (LED_PORT)
		{
			case 'A':
			PORTA = PORTA & mask;
			break;
			case 'B':
			PORTB = PORTB & mask;
			break;
			case 'C':
			PORTC = PORTC & mask;
			break;
			case 'D':
			PORTD = PORTD & mask;
			break;
		}
		_delay_ms(50);
	}
	ledToggleAll();
}

void ledMessageSent()
{
	unsigned char mask;
	for(int i = 7; i >= 0; i--)
	{
		mask = ~(0b00000001 << i);
		switch (LED_PORT)
		{
			case 'A':
			PORTA = PORTA & mask;
			break;
			case 'B':
			PORTB = PORTB & mask;
			break;
			case 'C':
			PORTC = PORTC & mask;
			break;
			case 'D':
			PORTD = PORTD & mask;
			break;
		}
		_delay_ms(50);
	}
	ledToggleAll();
}