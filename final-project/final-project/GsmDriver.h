#ifndef __GSMDRIVER_H__
#define __GSMDRIVER_H__

class GsmDriver
{
	public:
	GsmDriver();
	~GsmDriver();
	bool SendMessage(char* phonenumber, char* message);
	char* GetMessage();
	void SaveReceivedChar(char receivedChar);

	private:
	bool SetTextMode();
	bool EnableEcho();
	bool DisableEcho();
	bool WaitForMessageReady();
};

#endif //__GSMDRIVER_H__
