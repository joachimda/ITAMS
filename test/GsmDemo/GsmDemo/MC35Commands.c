/*
* MC35Commands.c
* Created: 20-02-2017 15:05:03
*  Author: Joachim
*/

#define F_CPU 3686400
#include <util/delay.h>
#include "MC35Commands.h"
#include "usartDriver.h"

<<<<<<< HEAD
void sendPin(unsigned char* pin)
{
	sendString((unsigned char*)SEND_PIN);
	sendString(pin);
	sendString((unsigned char*)ENTER);
=======
void initMC35()
{
	setTextMode();
>>>>>>> 2b63572f771842cb97e36b3b4b59c81017f20511
}

void setTextMode()
{
	sendString((unsigned char*)SET_TEXT_MODE);
	sendString((unsigned char*)ENTER);
}

void enableEcho()
{
	sendString((unsigned char*)ENABLE_ECHO);
	sendString((unsigned char*)ENTER);
}

void disableEcho()
{
	sendString((unsigned char*)DISABLE_ECHO);
	sendString((unsigned char*)ENTER);
}

void sendSms(unsigned char* message, unsigned char* phoneNumber)
{
	setTextMode();
	sendString((unsigned char*)SEND_MESSAGE);
	sendString(phoneNumber);
	sendString((unsigned char*)ENTER);
	sendString(message);
	sendByte(CTRL_Z);	
}

unsigned char waitForMessageReady()
{
	for (unsigned int i = 0; i < DATA_SIZE; i++)
	{
		if(data[i] == '>')
		return 1;
	}
	return 0;
}

void sendPin(unsigned char* pin)
{
	sendString(SEND_PIN);
	sendString(pin);
	sendString(ENTER);
}
void getAllMessages()
{
	sendString((unsigned char*)GET_ALL_MESSAGES);
	sendString((unsigned char*)ENTER);	
}