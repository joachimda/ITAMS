#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "gsm/gsm.h"
#include <avr/interrupt.h>

#include "uart/uartwork.h"
volatile unsigned int index = 0;

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

unsigned char value;


ISR(USART_RXC_vect){
	
	value = UDR;             //read UART register into value
	//PORTB = ~value;          // output inverted value on LEDs (0=on)
	sendString("1");
}

int main(void)
{

	sei();
	//gsmInit();
	for (int i = 0; i < DATA_SIZE;i++)
	{
		data[i] = 0;
	}
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
	//initializeUART(9600,8);
	unsigned char receivedChar = 0;
	unsigned char index = 0;
	unsigned char prefix[100] = {0};
	unsigned char message[100] = {0};

	gsmSendSms("24464105","ThIs Is A tEsT");

	unsigned char stopHere = 0;

	while(1){}
}
