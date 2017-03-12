#ifndef GSM_H_
#define GSM_H_
/************************************************************************/
/* Global command macros												*/
/************************************************************************/
#define ENTER "\r"

#define GET_ALL_MESSAGES "AT+CMGL=ALL"
#define DELETE_AT_INDEX "AT+CMGD="
#define DELETE_FIRST_INDEX "AT+CMGD=1"
#define ENABLE_ECHO "ATE1"
#define DISABLE_ECHO "ATE0"
#define SET_TEXT_MODE "AT+CMGF=1"
#define SEND_MESSAGE "AT+CMGS="
#define READ_FIRST_MESSAGE "AT+CMGR=1"
#define SEND_PIN "AT+CPIN="
#define GET_STATUS "AT+CIND?"

/************************************************************************/
/* Known SMS requests													*/
/************************************************************************/
const char REQ_TEMP_DATA;
const char REQ_CURRENT_GPS_COORD;
const char REQ_ALT_DATA;
const char REQ_PRES_DATA;

#define DATA_SIZE 100

extern const int SMS_FLAG_INDEX;
extern const char CR;
extern const char LF;
extern const char CTRL_Z;
extern const int RESPONSE_OFFSET;
extern const char TRUE;
extern const char FALSE;
extern char ackFlag;

struct gsmStatus
{
	char newMessage;
	char serviceAvailable;
	char callInProgress;
};

void gsmCommandDeleteArrayOfSms(unsigned int numberOfMessages);
void gsmInit();
void gsmCommandSendSms(unsigned char* phoneNumber, unsigned char* message);
void gsmCommandReadSms(char* header, char* data);
void gsmCommandDeleteSms();
void gsmCommandReadAllSms();
void gsmUtilWaitForResponse();
void gsmUtilWaitForSmsDelivery();
void gsmCommandSetTextMode();
void gsmCommandDisableEcho();
void gsmReadNewlines();
void gsmUtilCleanResponse();
void gsmUtilCheckForAck();
int gsmUtilDisassembleSms(char* meta, int offset);
void gsmCommandGetStatus(struct gsmStatus *stat);
void gsmUtilSetStatusFlags(struct gsmStatus *stat);
void gsmExecuteSmsRequest(char* data);

#endif /* GSM_H_ */
