/*
* GsmDemo.c
* Created: 20-02-2017 12:59:12
* Author : Joachim
*/

#include <avr/io.h>
#define  F_CPU 3686400
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usartDriver.h"
#include "ledDriver.h"
#include "MC35Commands.h"

volatile unsigned int index = 0;
volatile unsigned char value;

void clearDataArray(unsigned char* dataArray)
{
	for (unsigned int i = 0; i< DATA_SIZE;i++)
	{
		dataArray[i] = 0;
	}
}

ISR(USART_RXC_vect)
{
	clearDataArray(data);
	value = UDR;
	data[index] = value;
	index++;
}

int main(void)
{
	usartInit();
	sei();
	
	while (1)
	{
		getAllMessages();
		_delay_ms(2000);
	}
}
