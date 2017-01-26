/*
* LAB2_JTAGDebugging.c
*
* Created: 26-01-2017 10:00:02
* Author : Joachim
*/

#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>

int main(void)
{
	unsigned char i = 0;
	
	DDRA = 0;		//PORTA pins are inputs
	DDRB = 0xFF;	//PORTB pins are outputs
	
	/* Replace with your application code */
	while (1)
	{
		PORTB = ~i;
		
		i++;
		_delay_ms(500);
		if ((PINA & 0b10000000)==0)
			i=0;
	}
	return 0;
}

