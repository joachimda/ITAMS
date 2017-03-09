#define F_CPU 3686400
#include <util/delay.h>
#include "gsm/gsm.h"

int main(void)
{
	gsmInit();
	
	unsigned char receivedChar = 0;
	unsigned char index = 0;
	unsigned char prefix[100] = {0};
	unsigned char message[100] = {0};

	gsmSendSms("24464105","ThIs Is A tEsT");

	unsigned char stopHere = 0;

}
