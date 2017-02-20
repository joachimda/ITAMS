/*
 * IncFile1.h
 *
 * Created: 20-02-2017 13:19:24
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