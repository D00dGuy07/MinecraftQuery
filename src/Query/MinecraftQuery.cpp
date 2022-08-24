/* 
MIT License

Copyright (c) 2022 D00dGuy07

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../../Include/MinecraftQuery/MinecraftQuery.h"

#include "../ByteUtil/Bytes.h"
#include "../ByteUtil/BufferUtil.h"
#include "../Networking/DatagramSocket.h"
#include "QueryHeader.h"

#include <WinSock2.h>
#include <unordered_map>

bool MinecraftQuery::Initialize()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	return (WSAStartup(wVersionRequested, &wsaData) == 0);
}

bool MinecraftQuery::Cleanup()
{
	return (WSACleanup() == 0);
}

int Handshake(DatagramSocket& socket, SocketAddress& address)
{
	QueryHeader header(QUERY_TYPE_HANDSHAKE, 0x0001);

	std::vector<char> packet = std::vector<char>();
	header.AppendBytes(packet);

	socket.Send(address, packet.data(), static_cast<int32_t>(packet.size()));
	std::vector<char> response = socket.Listen(address, 128);

	if (response[0] == 9)
		return std::stoi(response.data() + 5);

	return NULL;
}

bool MinecraftQuery::FillBasicStat(BasicStat& stat, std::string address, std::string port)
{
	DatagramSocket socket = DatagramSocket(2000);
	SocketAddress _address(address, port);

	int token = Handshake(socket, _address);

	// Build query packet
	QueryHeader header(QUERY_TYPE_STAT, 0x0001);

	std::vector<char> packet = std::vector<char>();
	header.AppendBytes(packet);
	SerializeBytes(packet, token);

	socket.Send(_address, packet.data(), static_cast<int32_t>(packet.size()));
	std::vector<char> response = socket.Listen(_address, 128);

	// Parse response
	if (response[4] == 1)
	{
		char* pointer = response.data() + 5;

		stat.MOTD = ReadString(pointer);
		stat.GameType = ReadString(pointer);
		stat.Map = ReadString(pointer);
		stat.NumPlayers = std::stoi(ReadString(pointer));
		stat.MaxPlayers = std::stoi(ReadString(pointer));
		stat.HostPort = *(short*)pointer;
		pointer += 2;
		stat.HostIP = ReadString(pointer);

		return false;
	}

	return true;
}

bool MinecraftQuery::FillFullStat(FullStat& stat, std::string address, std::string port)
{
	DatagramSocket socket = DatagramSocket(2000);
	SocketAddress _address(address, port);

	int token = Handshake(socket, _address);

	// Build query packet
	QueryHeader header(QUERY_TYPE_STAT, 0x0001);

	std::vector<char> packet = std::vector<char>();
	header.AppendBytes(packet);
	SerializeBytes(packet, token);
	SerializeBytes(packet, NULL);

	socket.Send(_address, packet.data(), static_cast<int32_t>(packet.size()));
	std::vector<char> response = socket.Listen(_address, 1024);

	// Parse response
	if (response[4] == 1)
	{
		char* pointer = response.data() + 16;

		// Parse k, v section
		std::unordered_map<std::string, std::string> dictionary = std::unordered_map<std::string, std::string>();
		while (*pointer != NULL)
		{
			std::string key = ReadString(pointer);
			std::string value = ReadString(pointer);
			dictionary[key] = value;
		}
		pointer++;

		stat.MOTD = dictionary["hostname"];
		stat.GameType = dictionary["gametype"];
		stat.GameID = dictionary["game_id"];
		stat.Version = dictionary["version"];
		stat.Plugins = dictionary["plugins"];
		stat.Map = dictionary["map"];
		stat.NumPlayers = std::stoi(dictionary["numplayers"]);
		stat.MaxPlayers = std::stoi(dictionary["maxplayers"]);
		stat.HostPort = std::stoi(dictionary["hostport"]);
		stat.HostIP = dictionary["hostip"];

		// Parse players section
		stat.Players = std::vector<std::string>();

		pointer += 10;

		while (*pointer != NULL)
		{
			stat.Players.push_back(ReadString(pointer));
		}

		return true;
	}

	return false;
}
