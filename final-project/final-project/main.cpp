#define F_CPU 3668400
#include <avr/io.h>
#include <avr/interrupt.h>

#include "GsmDriver.h"

GsmDriver gsm = new GsmDriver();

int main(void)
{
    while (1) 
    {
    }
}

ISR(USART_RXC_vect)
{
	// something!
	gsm.EnableEcho();
}