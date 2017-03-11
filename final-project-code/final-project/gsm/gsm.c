#include "gsm.h"
#define F_CPU 3686400
#include <util/delay.h>
#include "../uart/uart.h"

char test[50];

void gsmInit()
{
	clear();
	gsmDisableEcho();
	gsmSetTextMode();
	gsmWaitForResponse();
}


void gsmCleanResponse()
{
	for (unsigned int i = 0; i < 50; i++)
	{
		if(test[i] == 10 || test[i] == 13)
			{
				test[i] = 0;
			}
	}

	int index = 0;
	for (unsigned int i = 0; i < 50; i++)
	{
		if (test[i] != 0)
		{
			test[index] = test[i];
			test[i] = 0;
			index++;
		}
	}
}

void gsmSendSms(unsigned char* phoneNumber, unsigned char* message)
{
	gsmWaitForResponse();
	uartSendString((unsigned char*)SEND_MESSAGE);
	uartSendString((unsigned char*)phoneNumber);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
	uartSendString((unsigned char*)message);
	gsmWaitForResponse();
	uartSendByte(26);
	gsmWaitForResponse();
}

void gsmReadSms(unsigned char index, unsigned char* message)
{
	uartSendString((unsigned char*)READ_MESSAGE);
	uartSendByte(index);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmDeleteSms()
{
	uartSendString((unsigned char*)DELETE_FIRST_INDEX);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmWaitForResponse()
{
	_delay_ms(200);
}

void gsmSetTextMode()
{
	uartSendString((unsigned char*)SET_TEXT_MODE);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmDisableEcho()
{
	uartSendString((unsigned char*)DISABLE_ECHO);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmReadNewlines()
{
	//uartReadChar();
	//uartReadChar();
}
