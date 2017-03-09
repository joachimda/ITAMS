#define F_CPU 3686400
#include <util/delay.h>
#include "gsm/gsm.h"

int main(void)
{
	while(1) // Repeat indefinitely
	{
		gsmInit();
	}
}