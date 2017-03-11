#ifndef GSM_H_
#define GSM_H_

#define CTRL_Z 26
#define MAX_SIZE 100
#define ENTER "\r\n"
#define GET_ALL_MESSAGES "AT+CMGL=ALL"
#define DELETE_FIRST_INDEX "AT+CMGD=1"
#define ENABLE_ECHO "ATE1"
#define DISABLE_ECHO "ATE0"
#define SET_TEXT_MODE "AT+CMGF=1"
#define SEND_MESSAGE "AT+CMGS="
#define READ_MESSAGE "AT+CMGR="
#define SEND_PIN "AT+CPIN="

void gsmInit();
void gsmSendSms(unsigned char* phoneNumber, unsigned char* message);
void gsmReadSms(unsigned char index, unsigned char* message);
void gsmDeleteSms();
void gsmWaitForResponse();
void gsmSetTextMode();
void gsmDisableEcho();
void gsmReadNewlines();
void gsmCleanResponse();

#endif /* GSM_H_ */