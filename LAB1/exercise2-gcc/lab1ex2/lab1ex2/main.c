/*
 * lab1ex2.c
 *
 * Created: 26-01-2017 09:49:08
 * Author : Joachim
 */ 

#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>


int main(void)
{
	unsigned char i = 0;
	DDRB = 0xFF;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = ~i;
		i++;
		_delay_ms(100);
    }
	return 0;
}

