#pragma once

#include <string>
#include <vector>
#include <WinSock2.h>

class IrcClient
{
public:
	IrcClient()
		: mServerIp({}), mServerPort({}), mFd(0), mServerFd(0)
	{
		Init();
	};

	~IrcClient()
	{
		Release();
	};

	static IrcClient& GetInst();

	void Connect(const std::string _serverIp, const std::string _serverPort);

	std::vector<std::string>& GetMsgs() { return mMsgs; }
	void MsgsCleanup() { mMsgs.clear(); }

private:
	void Init();
	void Release();

	void Error(const std::string _curMethod, const std::string _position);
	void PrintError(const std::string _curMethod, const std::string _position);

private:
	std::string		mServerIp;
	std::string		mServerPort;
	SOCKET			mFd;
	SOCKET			mServerFd;

	std::vector<std::string>	mMsgs;
};
