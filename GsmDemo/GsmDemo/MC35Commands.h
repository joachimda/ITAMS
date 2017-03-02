/*
 * MC35Commands.h
 * Created: 20-02-2017 14:57:50
 *  Author: Joachim
 */ 

#ifndef MC35COMMANDS_H_
#define MC35COMMANDS_H_

void sendSms(char* message, char* phoneNumber, char* callback);
void getMessages(char* response);
void setTextMode(char * callback);
void disableEcho();
void enableEcho();

#endif /* MC35COMMANDS_H_ */