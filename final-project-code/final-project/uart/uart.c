#define  F_CPU 3686400
#define  XTAL 3686400
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

volatile unsigned char value = 0;

ISR(USART_RXC_vect)
{
	value = UDR;
}

void uartInit()
{
	sei();
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}

unsigned char uartCharReady()
{
	if (value == 0)
	{
		return 0;
	}
	
	return 1;
}

unsigned char uartReadChar()
{
	return value;
}

void uartSendByte(unsigned char u8Data)
{
	// Wait until last byte has been transmitted
	while( (UCSRA & ( 1 << UDRE) ) == 0);

	// Transmit data
	UDR = u8Data;
}

void uartSendString(unsigned char* s)
{
	// Repeat until zero-termination
	while (*s != 0)
	{
		// Send the character pointed to by "s"
		uartSendByte(*s);
		// Advance the pointer one step
		s++;
	}
}

void uartSendInteger(int num)
{
	char array[7];
	// Convert the integer till an ASCII string (array), radix = 10
	itoa(num, array, 10);
	// - then send the string
	uartSendString(array);
}

/*************************************************************************
Flushed the RX buffer by toggling the receiver bit 4 in UCSRB
Parameters:
none
*************************************************************************/
void uartFlush()
{
	UCSRB ^= (-0^UCSRB) & (1 << 4);
	UCSRB ^= (-1^UCSRB) & (1 << 4);
}
