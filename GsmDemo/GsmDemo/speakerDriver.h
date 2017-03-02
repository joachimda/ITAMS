/*
 * speakerDriver.h
 *
 * Created: 27-02-2017 22:38:34
 *  Author: Joachim
 */ 


#ifndef SPEAKERDRIVER_H_
#define SPEAKERDRIVER_H_

 void initializeSpeaker(char port, unsigned char pattern);

 void playTone(unsigned int freq);
 
#endif /* SPEAKERDRIVER_H_ */