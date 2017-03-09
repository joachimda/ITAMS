#include "gsm.h"

void gsmInit()
{
	gsmSetTextMode();
	gsmDisableEcho();
}

void gsmSetTextMode()
{}

void gsmDisableEcho()
{}

void gsmSendSms(unsigned char* phoneNumber, unsigned char* message)
{}