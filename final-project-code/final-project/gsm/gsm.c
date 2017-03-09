#include "gsm.h"
#define F_CPU 3686400
#include <util/delay.h>
#include "../uart/uart.h"

void gsmInit()
{
	uartInit();

	gsmDisableEcho();
	gsmSetTextMode();
}

void gsmSendSms(unsigned char* phoneNumber, unsigned char* message)
{
	uartSendString((unsigned char*)SEND_MESSAGE);
	uartSendString((unsigned char*)phoneNumber);
	uartSendString((unsigned char*)CR);

	while(uartReadChar() != '>') { }
	_delay_ms(200);
	uartReadChar();

	uartSendString((unsigned char*)message);
	uartSendString((unsigned char*)CTRL_Z);
	gsmWaitForResponse();
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

void gsmReadLine(unsigned char* output, unsigned char size)
{
	unsigned char received = 0;
	unsigned char previous = 0;

	for (int i = 0; i < size; i++)
	{
		received = uartReadChar();

		if (received != CR && received != LF)
		{
			output[i] = received;
		}
		if (received == CR && received == LF)
		{
			break;
		}

		previous = received;
	}
}

void gsmDeleteSms(unsigned char index)
{
	uartSendString((unsigned char*)DELETE_INDEX);
	uartSendInteger(index);
	uartSendString((unsigned char*)ENTER);
	gsmWaitForResponse();
}

void gsmWaitForResponse()
{
	unsigned char* error = "ERROR";
	unsigned char pointer = 0;
	unsigned char received = 0;
	unsigned char previous = 0;

	while((received = uartReadChar()) != 0)
	{
		// Success
		if (previous == 'O' && received == 'K')
		{
			gsmReadNewlines();
			break;
		}
		else
		{
			previous = received;
		}

		// Error
		if (received == error[pointer])
		{
			pointer++;
		}
		else
		{
			pointer = 0;
		}

		// Going over possible error length
		if (pointer >= 5)
		{
			gsmReadNewlines();
			break;
		}
	}

	_delay_ms(200);
}

void gsmSetTextMode()
{
	uartSendString((unsigned char*)SET_TEXT_MODE);
	uartSendString((unsigned char*)CR);
	gsmWaitForResponse();
}

void gsmDisableEcho()
{
	uartSendString((unsigned char*)DISABLE_ECHO);
	uartSendString((unsigned char*)CR);
	gsmWaitForResponse();
}

void gsmReadNewlines()
{
	uartReadChar();
	uartReadChar();
}
