/*
* USARTInterruptsDemo.c
*
* Created: 06-03-2017 13:54:18
* Author : Joachim
*/

#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
#include <avr/interrupt.h>
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char value;

ISR(USART_RXC_vect){
	
	value = UDR;             //read UART register into value
	PORTB = ~value;          // output inverted value on LEDs (0=on)
}

void USART_Init(void)
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

void Led_init(void){
	//outputs, all off
	DDRB =0xFF;
	PORTB = 0xFF;
}

void USART_SendByte(uint8_t u8Data){

	// Wait until last byte has been transmitted
	while((UCSRA &(1<<UDRE)) == 0);

	// Transmit data
	UDR = u8Data;
}

// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t USART_ReceiveByte(){
	while((UCSRA &(1<<RXC)) == 0);
	return UDR;
}

int main(void)
{
	USART_Init();
	sei();
	Led_init();
	
	value = 'A';
	PORTB = ~value;
	
	/* Replace with your application code */
	while (1)
	{
		USART_SendByte(value);
		_delay_ms(250);
	}
}

