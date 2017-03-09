#include "usart.h"
#include <avr/io.h>

/* Interrupt Service Routine for Receive Complete
NOTE: vector name changes with different AVRs see AVRStudio -
Help - AVR-Libc reference - Library Reference - <avr/interrupt.h>: Interrupts
for vector names other than USART_RXC_vect for ATmega32 */

ISR(USART_RXC_vect)
{
	value = UDR;             //read UART register into value
	PORTB = ~value;          // output inverted value on LEDs (0=on)
}

void usartInit(void)
{
	// Set baud rate
	UBRRL = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8);
	/* Load upper 8-bits into the high byte of the UBRR register
	Default frame format is 8 data bits, no parity, 1 stop bit
	to change use UCSRC, see AVR datasheet*/

	// Enable receiver and transmitter and receive complete interrupt
	UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}

void usartSendByte(uint8_t u8Data)
{

	// Wait until last byte has been transmitted
	while((UCSRA &(1<<UDRE)) == 0);

	// Transmit data
	UDR = u8Data;
}

// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t usartReceiveByte()
{
	while((UCSRA &(1<<RXC)) == 0);
	{
		return UDR;
	}
}
