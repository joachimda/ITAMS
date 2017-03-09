#include "gsm.h"
#include "../uart/uart.h"

void gsmInit()
{
	uartInit(9600, 8);
	uartSendString("UART connection is working");	
}