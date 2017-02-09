/******************************************************
FreeRTOS Switch and LED program
*******************************************************/
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "semphr.h"
#include "switch.h"

//Create the semaphore handle
xSemaphoreHandle semaphoreHandle = NULL;

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

void vWaitForSwitch(void *pvParameters)
{
	while(1)
	{
		if(switchOn(7))
		{
			xSemaphoreGive(semaphoreHandle);
		}
		vTaskDelay(10);
	}
}

void vSemBlink(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(semaphoreHandle, portMAX_DELAY);
		turnOnLED(5);
		vTaskDelay(10);
		turnOffLED(5);
	}
}

int main(void)
{
	initLEDport();
	initSwitchPort();
	xTaskCreate(vLEDFlashTask1, (signed char *) "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vLEDFlashTask2, (signed char *) "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vWaitForSwitch, (signed char *) "SWITCH", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vSemBlink, (signed char *) "BLINK", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
	while(1)
	{}
}

