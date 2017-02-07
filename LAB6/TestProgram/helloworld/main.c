#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	unsigned char i = 0;
	
	DDRA = 0x00;	// PORTA pins are inputs (SWITCHES)
	DDRB = 0xFF;	// PORTB pins are outputs (LEDs)
	
	while (1)
	{
		PORTB = ~i; // Display "i" at the LEDs
		_delay_ms(500);
		i++;
		
		if ((PINA & 0b10000000) == 0)
		{
			__asm("JMP 0x3C00");
		}
	}
	
	return 0;
}
