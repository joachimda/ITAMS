#define SMS_META_SIZE 75
#define SMS_DATA_SIZE 50
#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "gsm/gsm.h"
#include "uart/uart.h"
#include <avr/interrupt.h>

void clearSmsData(char* meta, char* data);

int main(void)
{
	sei();
	uartInit();
	gsmInit();
	gsmCommandDeleteArrayOfSms(10);

	struct gsmStatus stats;
	char meta[75] = {0};
	char data[50] = {0};

	gsmCommandGetStatus(&stats);
	clearSmsData(meta, data);
	volatile unsigned char stopHere = 0;
	while(1)
	{
		gsmCommandGetStatus(&stats);

		if (stats.newMessage == 1)
		{
			gsmCommandReadSms(meta, data);
			gsmExecuteSmsRequest(data);
			gsmCommandDeleteSms();
			clearSmsData(meta, data);			
		}
		
		_delay_ms(1000);
	}
}

void clearSmsData(char* meta, char* data)
{
	for(int i = 0; i < SMS_META_SIZE; i++)
	{
		meta[i] = 0;
	}

	for(int i = 0; i < SMS_DATA_SIZE; i++)
	{
		data[i] = 0;
	}
}
