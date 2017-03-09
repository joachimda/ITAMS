#define F_CPU 3686400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart/uart.h"

int main(void)
{
	uartInit(9600, 8);
	sei();        // enable all interrupts
	char value = 'B';  //0x41;
	
	while(1) // Repeat indefinitely
	{
		uartSendChar(value);  // send value
		_delay_ms(250);
		// delay just to stop Hyperterminal screen cluttering up
	}
}