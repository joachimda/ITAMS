#ifndef GSM_H_
#define GSM_H_

#define CTRL_Z 26
#define ENTER "\r"
#define GET_ALL_MESSAGES "AT+CMGL=ALL"
#define DELETE_FIRST_INDEX "AT+CMGD=1"
#define ENABLE_ECHO "ATE1"
#define DISABLE_ECHO "ATE0"
#define SET_TEXT_MODE "AT+CMGF=1"
#define SEND_MESSAGE "AT+CMGS="
#define SEND_PIN "AT+CPIN="

void gsmInit();
void gsmSendSms(unsigned char* phoneNumber, unsigned char* message);

void gsmSetTextMode();
void gsmDisableEcho();

#endif /* GSM_H_ */