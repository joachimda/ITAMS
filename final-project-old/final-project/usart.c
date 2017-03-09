/*
* uartDriver.c
* Created: 20-02-2017 13:04:32
*  Author: Joachim
*/

#include <avr/io.h>
#include "usart.h"
#include <stdlib.h>
#define  F_CPU 3686400
#include <util/delay.h>
#define  XTAL 3686400

void usartInit(unsigned char* data)
{
	for (int i = 0; i < DATA_SIZE;i++)
	{
		data[i] = 0;
	}
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}

void sendString(unsigned char* s)
{
	// Repeat until zero-termination
	while (*s != 0)
	{
		// Send the character pointed to by "s"
		sendByte(*s);
		// Advance the pointer one step
		s++;
	}
}


void sendByte(unsigned char u8Data)
{
	// Wait until last byte has been transmitted
	while((UCSRA &(1<<UDRE)) == 0);

	// Transmit data
	UDR = u8Data;
}

void sendInteger(int num)
{
	char array[7];
	// Convert the integer till an ASCII string (array), radix = 10
	itoa(num, array, 10);
	// - then send the string
	sendString(array);
}

/*************************************************************************
Flushed the RX buffer by toggling the receiver bit 4 in UCSRB
Parameters:
none
*************************************************************************/
void flushRxBuffer()
{
	UCSRB ^= (-0^UCSRB) & (1 << 4);
	UCSRB ^= (-1^UCSRB) & (1 << 4);
}

