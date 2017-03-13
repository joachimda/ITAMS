#ifndef LED_H_
#define LED_H_

const unsigned char OUTPUT;
const char LED_PORT;
const unsigned char DEFAULT_OFF;

void ledInit();
void ledToggleAll();
void ledMessageReceived();
void ledReadyForRequest();
void ledMessageSent();

#endif /* LED_H_ */