#define F_CPU 3686400
#include <util/delay.h>
#include <string.h>
#include "../uart/uart.h"
#include "gsm.h"
const char CR = 13;
const char LF = 10;
const char CTRL_Z = 26;
const int RESPONSE_OFFSET = 2;
const int SMS_FLAG_INDEX = 18;
const char TRUE = 1;
const char FALSE = 0;
char ackFlag;
char dataArray[DATA_SIZE];
const char REQ_TEMP_DATA = 'T';
const char REQ_CURRENT_GPS_COORD = 'G';
const char REQ_ALT_DATA = 'A';

void gsmInit()
{
	gsmCommandSetTextMode();
	gsmCommandDisableEcho();
}

void gsmCommandSetTextMode()
{
	clearDataArray();
	uartSendString((unsigned char*)SET_TEXT_MODE);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	gsmUtilCleanResponse();
	gsmUtilCheckForAck();
}

void gsmCommandDisableEcho()
{
	clearDataArray();
	uartSendString((unsigned char*)DISABLE_ECHO);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	gsmUtilCleanResponse();
	gsmUtilCheckForAck();
}

void gsmCommandReadAllSms()
{
	clearDataArray();
	gsmUtilWaitForResponse();
	uartSendString((unsigned char*)GET_ALL_MESSAGES);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	clearDataArray();
}

/************************************************************************/
/* Sends an SMS containing message to recipient specified by phoneNumber*/
/************************************************************************/
void gsmCommandSendSms(unsigned char* phoneNumber, unsigned char* message)
{
	gsmUtilWaitForResponse();
	clearDataArray();
	gsmUtilWaitForResponse();

	uartSendString((unsigned char*)SEND_MESSAGE);
	uartSendString((unsigned char*)phoneNumber);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	uartSendString((unsigned char*)message);
	gsmUtilWaitForResponse();

	uartSendByte(CTRL_Z);
	gsmUtilWaitForSmsDelivery();

}

/************************************************************************/
/* Reads the message located on the first index of the MC35 storage		*/
/************************************************************************/
void gsmCommandReadSms(char* meta, char* data)
{
	int offset = RESPONSE_OFFSET;
	clearDataArray();
	uartSendString((unsigned char*)READ_FIRST_MESSAGE);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	_delay_ms(300);
	offset = gsmUtilDisassembleSms(meta, offset);
	gsmUtilDisassembleSms(data, offset);
}

/************************************************************************/
/* Disassemble the SMS data and put into separate char arrays           */
/* Return current offset												*/
/************************************************************************/
int gsmUtilDisassembleSms(char* meta, int offset)
{
	char k = 0;
	if (dataArray[0] == CR && dataArray[1] == LF)
	{
		for (int i = offset; i < DATA_SIZE; i++)
		{
			meta[k] = dataArray[i];
			if (dataArray[i] == CR && dataArray[i+1] == LF)
			{
				return i+2;
			}
			k++;
		}
	}
}


/************************************************************************/
/* Deletes all messages stored on indexed up to the number given by		*/
/* the parameter numberOfMessages										*/
/************************************************************************/
void gsmCommandDeleteArrayOfSms(unsigned int numberOfMessages)
{
	for (volatile unsigned int k = 0; k < 10; k++)
	{
		uartSendString((unsigned char*)DELETE_AT_INDEX);
		uartSendInteger(k+1);
		uartSendString((unsigned char*)ENTER);
		gsmUtilWaitForResponse();
		gsmUtilCleanResponse();
		gsmUtilCheckForAck();
	}
}

/************************************************************************/
/* Deletes the SMS located on index 0							        */
/************************************************************************/
void gsmCommandDeleteSms()
{
	clearDataArray();
	uartSendString((unsigned char*)DELETE_FIRST_INDEX);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	gsmUtilCleanResponse();
	gsmUtilCheckForAck();
}

/************************************************************************/
/* Checks for an OK received and sets the ACK flag accordingly			*/
/************************************************************************/
void gsmUtilCheckForAck()
{
	if (dataArray[0] == 'O' && dataArray [1] == 'K')
	{
		ackFlag = 1;
	}
	else
	{
		ackFlag = 0;
	}
}

/************************************************************************/
/* Creates a delay to await SMS delivery								*/
/************************************************************************/
void gsmUtilWaitForSmsDelivery()
{
	_delay_ms(3000);
}

/************************************************************************/
/* Creates a delay await a reply from MC35								*/
/************************************************************************/
void gsmUtilWaitForResponse()
{
	_delay_ms(500);
}

/************************************************************************/
/* Removes any leading and traling LF/CR from a response				*/
/************************************************************************/
void gsmUtilCleanResponse()
{
	if (dataArray[0] != 0)
	{
		for (unsigned int i = 0; i < DATA_SIZE; i++)
		{
			if(dataArray[i] == LF || dataArray[i] == CR)
			{
				dataArray[i] = 0;
			}
		}

		int index = 0;
		for (unsigned int i = 0; i < DATA_SIZE; i++)
		{
			if (dataArray[i] != 0)
			{
				dataArray[index] = dataArray[i];
				dataArray[i] = 0;
				index++;
			}
		}
	}
}

/************************************************************************/
/* Requests the status parameters from MC35								*/
/************************************************************************/
void gsmCommandGetStatus(struct gsmStatus *stat)
{
	stat->callInProgress = 0;
	stat->newMessage = 0;
	stat->serviceAvailable = 0;
	clearDataArray();
	uartSendString((unsigned char*)GET_STATUS);
	uartSendString((unsigned char*)ENTER);
	gsmUtilWaitForResponse();
	gsmUtilSetStatusFlags(stat);
}

/************************************************************************/
/* Sets the flags in the GSM Status struct according to the CIND output */
/************************************************************************/
void gsmUtilSetStatusFlags(struct gsmStatus *stat)
{
	if (dataArray[18] == 49)	//if SMS flag (index 18) is set to 49 (1 ASCII)
	{
		stat->newMessage = 1;
	}
	
	else
	{
		stat->newMessage = 0;
	}
}

/************************************************************************/
/* Executes a received SMS command                                      */
/************************************************************************/
void gsmExecuteSmsRequest(char* data)
{
	if(data[0] == REQ_TEMP_DATA)
	{
		gsmCommandSendSms("50128894","TEMP: 23.2 deg.");
	}

	if(data[0] == REQ_ALT_DATA)
	{
		gsmCommandSendSms("50128894","Measured altitude: 52.8 meter above sea level.");
	}

	if(data[0] == REQ_CURRENT_GPS_COORD)
	{
		gsmCommandSendSms("50128894","Current location at: S1.0023deg SW13.20deg.");
	}
}

