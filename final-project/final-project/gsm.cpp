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

bool GsmDriver::setTextMode()
{
	return false;
}

bool GsmDriver::enableEcho()
{
	return false;
}

bool GsmDriver::disableEcho()
{
	return false;
}

bool GsmDriver::waitForMessageReady()
{
	return false;
}
