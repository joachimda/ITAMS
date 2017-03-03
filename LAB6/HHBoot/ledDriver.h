/*
 * ledDriver.h
 *
 * Created: 03-03-2017 00:59:35
 *  Author: Joachim
 */ 


#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_
void initLEDport();
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);
#endif /* LEDDRIVER_H_ */