/*
 * GPSDemo.cpp
 *
 * Created: 27-02-2017 20:29:21
 * Author : Joachim
 */ 

#include <avr/io.h>
#define BAUD
#define F_CPU 3686400
#include <util/delay.h>
#include "uartDriver.h"
#include "ledDriver.h"

int main(void)
{
    while (1)
    {
		initializeUART(BAUD, 8)
		initLEDport('C');
    }
}

