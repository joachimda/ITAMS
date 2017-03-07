#include "gsm.h"
#include "usart.h"

GsmDriver::GsmDriver()
{

}

GsmDriver::~GsmDriver()
{

}

bool GsmDriver::sendMessage(unsigned char* phonenumber, unsigned char* message)
{
	setTextMode();
	sendString((unsigned char*)SEND_MESSAGE);
	sendString(phonenumber);
	sendString((unsigned char*)ENTER);
	sendString(message);
	sendByte(CTRL_Z);
}

unsigned char* GsmDriver::getMessage()
{
	return NULL;
}

void GsmDriver::getAllMessages()
{
	sendString((unsigned char*)GET_ALL_MESSAGES);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::setTextMode()
{
	sendString((unsigned char*)SET_TEXT_MODE);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::enableEcho()
{
	return false;
}

void GsmDriver::disableEcho()
{
	return false;
}

void GsmDriver::waitForMessageReady()
{
	return false;
}
