#pragma once

#include <string>

struct BasicStat
{
	std::string MOTD;
	std::string GameType;
	std::string Map;
	int NumPlayers;
	int MaxPlayers;
	short HostPort;
	std::string HostIP;
};