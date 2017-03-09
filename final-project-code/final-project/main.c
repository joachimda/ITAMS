#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "gsm/gsm.h"
#include <avr/interrupt.h>

int main(void)
{
	//unsigned char receivedChar;
	//unsigned char prefix[100];
	unsigned char* message[100];

	sei();

	gsmInit();

	gsmSendSms("24464105","ThIs Is A tEsT");

	unsigned char stopHere = 0;

	while(1) { }
}
