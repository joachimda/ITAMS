/*
 * MC35Commands.h
 * Created: 20-02-2017 14:57:50
 *  Author: Joachim
 */ 

#ifndef MC35COMMANDS_H_
#define MC35COMMANDS_H_
#define CTRL_Z 26
<<<<<<< HEAD
#define ENTER "\r\n"
=======
#define ENTER "\r"
#define SEND_PIN "AT+CPIN="
>>>>>>> 2b63572f771842cb97e36b3b4b59c81017f20511
#define GET_ALL_MESSAGES "AT+CMGL=ALL"
#define DELETE_FIRST_INDEX "AT+CMGD=1"
#define ENABLE_ECHO "ATE1"
#define DISABLE_ECHO "ATE0"
#define SET_TEXT_MODE "AT+CMGF=1"
#define SEND_MESSAGE "AT+CMGS="
#define SEND_PIN "AT+CPIN="
#define PIN "8195"


void sendSms(unsigned char* message, unsigned char* phoneNumber);
void getAllMessages();
void setTextMode();
void sendPin();
void disableEcho();
void enableEcho();
<<<<<<< HEAD

=======
void initMC35();
void sendPin(unsigned char* pin);
unsigned char waitForMessageReady()
>>>>>>> 2b63572f771842cb97e36b3b4b59c81017f20511
#endif /* MC35COMMANDS_H_ */