#pragma once

#include <WinSock2.h>
#include <string>

struct SocketAddress
{
	SocketAddress(std::string address, std::string port);

	sockaddr_storage Address = {};
};