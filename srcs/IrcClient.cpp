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
	mServerIp = _serverIp == "localhost" ? "127.0.0.1" : _serverIp;
	mServerPort = _serverPort;

	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(stoi(mServerPort));

	if (inet_pton(AF_INET, mServerIp.data(), &(server.sin_addr)) <= 0) {
		return Error("Connect", "inet_pton()");
	}

	if (connect(mFd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		return Error("Connect", "connect()");
	}

	mMsgs.push_back(std::string("[Connect] " + mServerIp + ":" + mServerPort));
	mRecvThread = std::thread([this]() {
		ReceiveMsg();
	});
}

void IrcClient::Reset()
{
	Release();
	MsgsCleanup();
}

void IrcClient::SendMsg(const std::string _msg)
{
	send(mFd, _msg.data(), _msg.size(), NULL);
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
	mFd = 0;
	WSACleanup();
	mRecvThread.join();
}

void IrcClient::ReceiveMsg()
{
	char recvBuffer[1024];
	int recvSize;
	while (mFd)
	{
		recvSize = recv(mFd, recvBuffer, 1024 - 1, NULL);
		recvBuffer[recvSize] = '\0';
		mMsgs.push_back(recvBuffer);
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

