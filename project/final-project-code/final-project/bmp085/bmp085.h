/*This is a modified version of Davide Geroni's BMP085 driver:
copyright (c) Davide Gironi, 2012
Released under GPLv3.
References:
- this library is a porting of the bmp085driver 0.4 arduino library
http://code.google.com/p/bmp085driver/
*/

#ifndef BMP085_H_
#define BMP085_H_

#include <stdio.h>
#include <avr/io.h>

#define I2C_BMP_SLAVE_ADDR	 (0x77<<1)
#define I2C_INIT			 1 //initialize i2c

/*EEPROM registers from BMP085 datasheet p. 13*/
/************************************************************************/
/*				   	 Calibration registers 16-bit                       */
/************************************************************************/
#define CAL_REG_AC1 0xAA
#define CAL_REG_AC2 0xAC
#define CAL_REG_AC3 0xAE
#define CAL_REG_AC4 0xB0
#define CAL_REG_AC5 0xB2
#define CAL_REG_AC6 0xB4
#define CAL_REG_B1 0xB6
#define CAL_REG_B2 0xB8
#define CAL_REG_MB 0xBA
#define CAL_REG_MC 0xBC
#define CAL_REG_MD 0xBE

/*Control register values for different oversampling_setting (OSRS) p.17*/
/************************************************************************/
/*					    Control register 0xF4                           */
/************************************************************************/
#define CTRL_REG 0xF4
#define CTRL_REG_OUTPUT 0xF6		 //output 0xF6=MSB, 0xF7=LSB, optional 0xF8=XLSB
#define CTRL_REG_TEMP 0x2E			 //max conversion time 4.5ms - read temp
#define CTRL_REG_PRES_OS 0x34		 //max conversion time: see modes
/************************************************************************/

/************************************************************************/
/*						  Measurement modes                             */
/************************************************************************/
#define MODE_ULTRALOWPOWER 0						//oversampling=0, internalsamples=1, maxconvtimepressure=4.5ms, avgcurrent=3uA, RMSnoise_hPA=0.06, RMSnoise_m=0.5
#define MODE_STANDARD	   1						//oversampling=1, internalsamples=2, maxconvtimepressure=7.5ms, avgcurrent=5uA, RMSnoise_hPA=0.05, RMSnoise_m=0.4
#define MODE_HIGH_RES      2						//oversampling=2, internalsamples=4, maxconvtimepressure=13.5ms, avgcurrent=7uA, RMSnoise_hPA=0.04, RMSnoise_m=0.3
#define MODE_ULTRAHIGH_RES 3						//oversampling=3, internalsamples=8, maxconvtimepressure=25.5ms, avgcurrent=12uA, RMSnoise_hPA=0.03, RMSnoise_m=0.25
#define MODE			   MODE_ULTRAHIGH_RES		//Mode definition

//auto-update temperature enabled
#define AUTO_UPDATE_TEMP 1 //auto-update temperature every read
/************************************************************************/

/************************************************************************/
/*							HW initiation								*/
/************************************************************************/
#define UNIT_PASCAL_OFFSET	0					//define a unit offset (pa)
#define UNIT_METER_OFFSET	0					//define a unit offset (m)
#define FILTERPRESSURE  1						//average filter for pressure
extern void bmpInit();							//non static at link-time

/************************************************************************/

/************************************************************************/
/*							Data receive								*/
/************************************************************************/
extern int32_t getPressure();
extern double getAltitude();
extern double getTemperature();
/************************************************************************/

int regAC1, regAC2, regAC3, regB1, regB2, regMB, regMC, regMD;
unsigned int regAC4, regAC5, regAC6;
long rawTemperature, rawPressure;

#endif /* BMP085_H_ */
