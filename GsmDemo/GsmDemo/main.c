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

void clearDataArray(unsigned char* dataArray)
{
	for (unsigned int i = 0; i< DATA_SIZE;i++)
	{
		dataArray[i] = 0;
	}
}

ISR(USART_RXC_vect)
<<<<<<< HEAD
{	
	unsigned char value = UDR;
=======
{
	clearDataArray(data);
	value = UDR;
>>>>>>> 2b63572f771842cb97e36b3b4b59c81017f20511
	data[index] = value;
	index++;
}

int main(void)
{
	usartInit();
	sei();
	
	while(1)
	{
		//DO STUFF	
		_delay_ms(1000);	
	}
}
