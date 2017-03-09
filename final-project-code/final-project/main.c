#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include "gsm/gsm.h"

#include "uart/uartwork.h"
volatile unsigned int index = 0;

int main(void)
{

	unsigned char receivedChar = 0;
	unsigned char index = 0;
	unsigned char prefix[100] = {0};
	unsigned char message[100] = {0};

	gsmSendSms("24464105","ThIs Is A tEsT");

	unsigned char stopHere = 0;

	while(1){}
}
