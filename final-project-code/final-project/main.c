#define F_CPU 3686400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart/usart.h"
#include "gsm/gsm.h"

void ledInit(void){
	//outputs, all off
	DDRB = 0xFF;
	PORTB = 0xFF;
}

int main(void)
{
	usartInit();  // Initialise USART
	sei();        // enable all interrupts
	ledInit();    // init LEDs for testing
	value = 'A';  //0x41;
	PORTB = ~value; // 0 = LED on
	
	while(1) // Repeat indefinitely
	{
		usartSendByte(value);  // send value
		_delay_ms(250);
		// delay just to stop Hyperterminal screen cluttering up
	}
}