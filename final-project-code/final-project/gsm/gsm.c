#include "gsm.h"
#define F_CPU 3686400
#include <util/delay.h>
#include "../uart/uart.h"

void gsmInit()
{
	uartInit();
	clear();

	gsmDisableEcho();
	gsmSetTextMode();
	_delay_ms(200);

	//gsmSetTextMode();x
	_delay_ms(200);
}

void gsmSendSms(unsigned char* phoneNumber, unsigned char* message)
{
	_delay_ms(200);

	uartSendString((unsigned char*)SEND_MESSAGE);
	uartSendString((unsigned char*)phoneNumber);
	uartSendString((unsigned char*)ENTER);

	//while(uartReadChar() != '>') { }
	_delay_ms(200);
	_delay_ms(200);
	//uartReadChar();

	uartSendString((unsigned char*)message);
	_delay_ms(1000);
	uartSendByte(26);
	//uartSendString((unsigned char*)CTRL_Z);
	_delay_ms(1000);
	//gsmWaitForResponse();
}

void gsmReadSms(unsigned char index, unsigned char* prefix, unsigned char* message)
{
	uartSendString((unsigned char*)READ_MESSAGE);
	uartSendByte(index);
	uartSendString((unsigned char*)ENTER);

	gsmReadLine(prefix, MAX_SIZE);
	gsmReadLine(message, MAX_SIZE);

	gsmWaitForResponse();
}

//void gsmReadLine(unsigned char* output, unsigned char size)
//{
//unsigned char received = 0;
//unsigned char previous = 0;
//
//for (int i = 0; i < size; i++)
//{
//received = uartReadChar();
//
//if (received != CR && received != LF)
//{
//output[i] = received;
//}
//if (received == CR && received == LF)
//{
//break;
//}
//
//previous = received;
//}
//}

void gsmDeleteSms(unsigned char index)
{
	uartSendString((unsigned char*)DELETE_INDEX);
	uartSendInteger(index);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmWaitForResponse()
{
	while(1)
	{
		if(uartReadChar() == 'K')
		{
			break;
		}

		if(uartReadChar() == 'E')
		{
			if(uartReadChar() == 'R')
			{
				break;
			}
		}
	}
	_delay_ms(200);
}

void gsmSetTextMode()
{
	uartSendString((unsigned char*)SET_TEXT_MODE);
	uartSendString((unsigned char*)ENTER);
	//gsmWaitForResponse();
}

void gsmDisableEcho()
{
	uartSendString((unsigned char*)DISABLE_ECHO);
	uartSendString((unsigned char*)ENTER);
	//gsmWaitForResponse();
}

void gsmReadNewlines()
{
	//uartReadChar();
	//uartReadChar();
}
