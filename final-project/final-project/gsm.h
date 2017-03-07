#ifndef __GSMDRIVER_H__
#define __GSMDRIVER_H__

class GsmDriver
{
	public:
	GsmDriver();
	~GsmDriver();
	void sendMessage(unsigned char* phonenumber, unsigned char* message);
	void getMessage();
	void saveReceivedChar(unsigned char receivedChar);
	void getAllMessages();

	private:
	void setTextMode();
	void enableEcho();
	void disableEcho();
	unsigned char waitForMessageReady();

	unsigned char* receivedData_[100];
	int index_;
};

#endif //__GSMDRIVER_H__
