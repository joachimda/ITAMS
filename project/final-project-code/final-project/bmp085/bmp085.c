/*This is a modified/refactored version of Davide Geroni's BMP085 driver:
copyright (c) Davide Gironi, 2012
Released under GPLv3.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>

#include "bmp085.h"
#include "../i2c/i2c.h"

void writeMemory(uint8_t reg, uint8_t value)
{
	i2c_start_wait(I2C_BMP_SLAVE_ADDR | I2C_WRITE);
	i2c_write(reg);
	i2c_write(value);
	i2c_stop();
}

void readMemory(uint8_t reg, uint8_t buff[], uint8_t bytes)
{
	uint8_t i =0;
	i2c_start_wait(I2C_BMP_SLAVE_ADDR | I2C_WRITE);
	i2c_write(reg);
	i2c_rep_start(I2C_BMP_SLAVE_ADDR | I2C_READ);
	for(i=0; i<bytes; i++)
	{
		if(i==bytes-1)
		buff[i] = i2c_readNak();
		else
		buff[i] = i2c_readAck();
	}
	i2c_stop();
}

#if FILTERPRESSURE == 1
#define AVERAGECOEF 21
static long k[AVERAGECOEF];

long averageFilter(long input)
{
	uint8_t i=0;
	long sum=0;
	for (i = 0; i < AVERAGECOEF; i++)
	{
		k[i] = k[i + 1];
	}

	k[AVERAGECOEF - 1] = input;
	for (i = 0; i < AVERAGECOEF; i++)
	{
		sum += k[i];
	}
	return (sum / AVERAGECOEF);
}
#endif

void getCalibration()
{
	uint8_t buffer[2];
	memset(buffer, 0, sizeof(buffer));

	readMemory(CAL_REG_AC1, buffer, 2);
	regAC1 = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_AC2, buffer, 2);
	regAC2 = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_AC3, buffer, 2);
	regAC3 = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_AC4, buffer, 2);
	regAC4 = ((unsigned int)buffer[0] <<8 | ((unsigned int)buffer[1]));
	readMemory(CAL_REG_AC5, buffer, 2);
	regAC5 = ((unsigned int)buffer[0] <<8 | ((unsigned int)buffer[1]));
	readMemory(CAL_REG_AC6, buffer, 2);
	regAC6 = ((unsigned int)buffer[0] <<8 | ((unsigned int)buffer[1]));
	readMemory(CAL_REG_B1, buffer, 2);
	regB1 = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_B2, buffer, 2);
	regB2 = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_MB, buffer, 2);
	regMB= ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_MC, buffer, 2);
	regMC = ((int)buffer[0] <<8 | ((int)buffer[1]));
	readMemory(CAL_REG_MD, buffer, 2);
	regMD = ((int)buffer[0] <<8 | ((int)buffer[1]));
}

void getRawTemperature()
{
	uint8_t buffer[2];
	memset(buffer, 0, sizeof(buffer));
	long ut, x1, x2;

	//read raw temperature
	writeMemory(CTRL_REG, CTRL_REG_TEMP);
	_delay_ms(5); // min. 4.5ms read Temp delay
	readMemory(CTRL_REG_OUTPUT, buffer, 2);
	ut = ((long)buffer[0] << 8 | ((long)buffer[1])); //uncompensated temperature value

	//calculate raw temperature
	x1 = ((long)ut - regAC6) * regAC5 >> 15;
	x2 = ((long)regMC << 11) / (x1 + regMD);
	rawTemperature = x1 + x2;
}

void getRawPressure()
{
	uint8_t buffer[3];
	memset(buffer, 0, sizeof(buffer));
	long uncompensatedPressure, x1, x2, x3, b3, b6, p;
	unsigned long b4,b7;

	#if AUTO_UPDATE_TEMP == 1
	getRawTemperature();
	#endif

	//read raw pressure
	writeMemory(CTRL_REG, CTRL_REG_PRES_OS+(MODE << 6));
	_delay_ms(2 + (3 << MODE));
	readMemory(CTRL_REG_OUTPUT, buffer, 3);
	uncompensatedPressure = ((((long)buffer[0] <<16) | ((long)buffer[1] <<8) | ((long)buffer[2])) >> (8-MODE));

	//calculate raw pressure
	b6 = rawTemperature - 4000;
	x1 = (regB2* (b6 * b6) >> 12) >> 11;
	x2 = (regAC2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((long)regAC1) * 4 + x3) << MODE) + 2) >> 2;
	x1 = (regAC3 * b6) >> 13;
	x2 = (regB1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (regAC4 * (uint32_t)(x3 + 32768)) >> 15;
	b7 = ((uint32_t)uncompensatedPressure - b3) * (50000 >> MODE);
	p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	rawPressure = p + ((x1 + x2 + 3791) >> 4);

	#if FILTERPRESSURE == 1
	rawPressure = averageFilter(rawPressure);
	#endif
}

double getTemperature()
{
	getRawTemperature();
	double temperature = ((rawTemperature + 8)>>4);
	temperature = temperature /10;
	return temperature;
}


int32_t getPressure()
{
	getRawPressure();
	return rawPressure + UNIT_PASCAL_OFFSET;
}

double getAltitude()
{
	getRawPressure();
	return ((1 - pow(rawPressure/(double)101325, 0.1903 )) / 0.0000225577) + UNIT_METER_OFFSET;
}

void bmpInit() {
	#if I2C_INIT == 1
	i2c_init();
	_delay_us(10);
	#endif

	getCalibration();
	getRawTemperature();

	#if FILTERPRESSURE == 1
	//initialize the average filter
	uint8_t i = 0;
	for (i = 0; i < AVERAGECOEF; i++)
	{
		getRawPressure();
	}
	#endif
}
