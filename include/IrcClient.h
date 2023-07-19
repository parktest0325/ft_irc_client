#pragma once

#include <string>
#include <vector>
#include <thread>
#include <WinSock2.h>

class IrcClient
{
public:
	IrcClient()
		: mServerIp({}), mServerPort({}), mFd(0)
	{
		Init();
	};

	~IrcClient()
	{
		Release();
	};

	static IrcClient& GetInstance();

	void Connect(const std::string _serverIp, const std::string _serverPort);
	void Disconnect();

	std::vector<std::string>& GetMsgs() { return mMsgs; }
	void MsgsCleanup() { mMsgs.clear(); }

	void SendMsg(const std::string _msg);
	void SendMsgWithNl(std::string _msg);

private:
	void Init();
	void Release();
	void ReceiveMsg();

	void Error(const std::string _curMethod, const std::string _position);
	inline void PrintError(const std::string _curMethod, const std::string _position);
	inline void PrintSystemMsg(const std::string _msg);

	std::string ReplaceEscapeInString(std::string _str, std::string _delim);

private:
	std::string		mServerIp;
	std::string		mServerPort;
	SOCKET			mFd;

	std::thread		mRecvThread;
	std::vector<std::string>	mMsgs;
};
