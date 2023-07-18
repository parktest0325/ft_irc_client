#include "IrcClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

IrcClient& IrcClient::GetInstance()
{
	static IrcClient inst;
	return inst;
}

void IrcClient::Connect(const std::string _serverIp, const std::string _serverPort)
{
	if (mFd) Disconnect();

	mServerIp = _serverIp == "localhost" ? "127.0.0.1" : _serverIp;
	mServerPort = _serverPort;

	mFd = socket(AF_INET, SOCK_STREAM, 0);
	if (mFd == INVALID_SOCKET)
		return Error("Connect", "socket()");

	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(stoi(mServerPort));

	if (inet_pton(AF_INET, mServerIp.data(), &(server.sin_addr)) <= 0)
		return Error("Connect", "inet_pton()");

	if (connect(mFd, (struct sockaddr*)&server, sizeof(server)) < 0)
		return Error("Connect", "connect()");

	mRecvThread = std::thread([this]() {
		ReceiveMsg();
	});
	PrintSystemMsg(mServerIp + ":" + mServerPort + " is Connected.");
}

void IrcClient::Disconnect()
{
	if (mFd)
	{
		closesocket(mFd);
		mFd = 0;
		mRecvThread.join();
		PrintSystemMsg(mServerIp + ":" + mServerPort + " is Disconnected.");
	}
	else
	{
		PrintSystemMsg("Not Connected!!");
	}
}

void IrcClient::SendMsg(const std::string _msg)
{
	std::cout << _msg << std::endl;
	send(mFd, _msg.data(), _msg.size(), NULL);
}

void IrcClient::SendMsgWithNl(std::string _msg)
{
	_msg += '\n';
	SendMsg(_msg);
}

void IrcClient::Init()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return Error("Init", "WSAStartup()");
	}
}

void IrcClient::Release()
{
	WSACleanup();
}

void IrcClient::ReceiveMsg()
{
	char recvBuffer[1024];
	int recvSize;
	while (mFd)
	{
		recvSize = recv(mFd, recvBuffer, 1024 - 1, NULL);
		if (recvSize > 0)
		{
			recvBuffer[recvSize] = '\0';
			mMsgs.push_back(recvBuffer);
		}
	}
}

void IrcClient::Error(const std::string _curMethod, const std::string _position)
{
	PrintError(_curMethod, _position);
	return;
}

void IrcClient::PrintError(const std::string _curMethod, const std::string _position)
{
	mMsgs.push_back(std::string("[Fail] IrcClient::" + _curMethod + " => " + _position));
}

void IrcClient::PrintSystemMsg(const std::string _msg)
{
	mMsgs.push_back(std::string("[System] " + _msg));
}
