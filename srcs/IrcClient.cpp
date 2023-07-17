#include "IrcClient.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

IrcClient& IrcClient::GetInst()
{
	static IrcClient inst;
	return inst;
}

void IrcClient::Connect(const std::string _serverIp, const std::string _serverPort)
{
	mServerIp = _serverIp == "localhost" ? "127.0.0.1" : _serverIp;
	mServerPort = _serverPort;

	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(mServerIp.data());
	server.sin_family = AF_INET;
	server.sin_port = htons(stoi(mServerPort));

	if (mServerFd = connect(mFd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		return Error("Connect", "connect()");
	}
	mMsgs.push_back(std::string("[Connect] " + mServerIp + ":" + mServerPort));
}

void IrcClient::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return Error("Init", "WSAStartup()");
	}

	mFd = socket(AF_INET, SOCK_STREAM, 0);
	if (mFd == INVALID_SOCKET)
	{
		return Error("Init", "socket()");
	}
}

void IrcClient::Release()
{
	closesocket(mFd);
	closesocket(mServerFd);
	WSACleanup();
}

void IrcClient::Error(const std::string _curMethod, const std::string _position)
{
	Release();
	PrintError(_curMethod, _position);
	return;
}

void IrcClient::PrintError(const std::string _curMethod, const std::string _position)
{
	mMsgs.push_back(std::string("[Fail] IrcClient:: " + _curMethod + " => " + _position));
}

