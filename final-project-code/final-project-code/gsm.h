#ifndef GSM_H_
#define GSM_H_

void gsmInit();
void gsmSendSms(unsigned char* phoneNumber, unsigned char* message);

void gsmSetTextMode();
void gsmDisableEcho();

#endif /* GSM_H_ */