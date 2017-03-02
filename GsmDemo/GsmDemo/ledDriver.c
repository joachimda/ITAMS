#include <avr/io.h>

#define MAX_LED_NR 7

void initLEDport(char key)
{
	switch (key)
	{
		case 'A':
		DDRA = 0b11111111;
		PORTA = 0xFF;
		break;
		case 'B':
		DDRB = 0b11111111;
		PORTB = 0xFF;
		break;
		case 'C':
		DDRC = 0b11111111;
		PORTC = 0xFF;
		break;
		case 'D':
		break;
		DDRD = 0b11111111;
		PORTD = 0xFF;
		break;
		default:
		DDRC = 0b11111111;
		PORTC = 0xFF;
		break;
	}
}

void writeAllLEDs(unsigned char pattern)
{
	// Fetch the parameter, invert all bits, and send to LEDs
	// The bits has to be inverted, because HW dictates
	// a 0 will turn ON a LED
	PORTC = ~pattern;
}

void turnOnLED(unsigned char led_nr)
{
	// Local variable
	unsigned char mask;
	// We only have to do anything, if led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Create mask based on the parameter (led_nr)
		mask = ~(0b00000001 << led_nr);
		// Turn ON the actual LED (the rest are unchanged)
		PORTC = PORTC & mask;
	}
}

void turnOffLED(unsigned char led_nr)
{
	// Local variable
	unsigned char mask;
	// We only have to do anything, if led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Create mask based on the parameter (led_nr)
		mask = 0b00000001 << led_nr;
		// Turn OFF the actual LED (the rest are unchanged)
		PORTC = PORTC | mask;
	}
}

void toggleLED(unsigned char led_nr)
{
	// Local variable
	unsigned char mask;
	// We only have to do anything, if led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Create mask based on the parameter (led_nr)
		mask = 0b00000001 << led_nr;
		// Toggle the actual LED (the rest are unchanged)
		PORTC = PORTC ^ mask;
	}
}
