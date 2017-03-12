#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU 3686400
#include <util/delay.h>
#include <math.h>

#include "bmp085.h"

int main(void) {
	long l = 0;
	double d = 0;
	double a = 0;
	char printbuff[10];

	sei();
	bmpInit();

	for (;;)
	{
		d = getTemperature();
		dtostrf(d, 10, 2, printbuff);

		l = getPressure();
		ltoa(l, printbuff, 10);

		a = getAltitude();
		dtostrf(d, 10, 2, printbuff);

		_delay_ms(1500);
	}
	
	return 0;
}


