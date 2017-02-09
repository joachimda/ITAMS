/******************************************************
FreeRTOS demo program.
Implementing 2 tasks, each blinking a LED.

STK500 setup:
* PORTC connected to LEDS.

Henning Hargaard 13.2.2016
*******************************************************/
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void vLEDFlashTask1( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	while(1)
	{
		toggleLED(0);
		vTaskDelayUntil(&xLastWakeTime,800);
	}
}

void vLEDFlashTask2( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	while(1)
	{
		toggleLED(1);
		vTaskDelayUntil(&xLastWakeTime,500);
	}
}

void vLEDFlashTask3(void *pvParameters )
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		toggleLED(2);
		vTaskDelayUntil(&xLastWakeTime,200);
	}
}

int main(void)
{
	initLEDport();
	xTaskCreate( vLEDFlashTask1, (signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate( vLEDFlashTask2, (signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate( vLEDFlashTask3, (signed char * ) "LED3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
	while(1)
	{}
}

