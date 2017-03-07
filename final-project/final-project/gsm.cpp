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
	return false;
}

unsigned char* GsmDriver::getMessage()
{
	return NULL;
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
