#pragma once

#include <WinSock2.h>
#include <vector>

#include "SocketAddress.h"

class DatagramSocket
{
public:
	DatagramSocket(uint32_t timeout);
	~DatagramSocket();

	void Send(SocketAddress& address, void* data, int len);
	std::vector<char> Listen(SocketAddress& address, int bufferSize);

private:
	SOCKET m_Socket;
	sockaddr_in m_ListenAddress = {};
};