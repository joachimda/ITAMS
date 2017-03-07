#ifndef __GSMDRIVER_H__
#define __GSMDRIVER_H__

class GsmDriver
{
	public:
	// methods
	GsmDriver();
	~GsmDriver();
	bool sendMessage(unsigned char* phonenumber, unsigned char* message);
	unsigned char* getMessage();
	void saveReceivedChar(unsigned char receivedChar);

	private:
	// methods
	bool setTextMode();
	bool enableEcho();
	bool disableEcho();
	bool waitForMessageReady();
	// members
	unsigned char* receivedData[100];
	unsigned char index = 0;
};

#endif //__GSMDRIVER_H__
