#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "gsm/gsm.h"
#include "uart/uart.h"
#include <avr/interrupt.h>

int main(void)
{
	sei();
	gsmInit();
	uartInit();

	gsmDeleteSms();

	gsmCleanResponse();

	gsmSendSms("50128894","More test");
	volatile unsigned char stopHere = 0;
	//while(1) { }
}
