#include "GsmDriver.h"

GsmDriver::GsmDriver()
{

}

GsmDriver::~GsmDriver()
{

}

bool GsmDriver::SendMessage(char* phonenumber, char* message)
{
	return false;
}

char* GsmDriver::GetMessage()
{
	return NULL;
}

bool GsmDriver::SetTextMode()
{
	return false;
}

bool GsmDriver::EnableEcho()
{
	return false;
}

bool GsmDriver::DisableEcho()
{
	return false;
}

bool GsmDriver::WaitForMessageReady()
{
	return false;
}
