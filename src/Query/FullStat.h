#pragma once

#include <string>
#include <vector>

struct FullStat
{
	std::string MOTD;
	std::string GameType;
	std::string GameID;
	std::string Version;
	std::string Plugins;
	std::string Map;
	int NumPlayers;
	int MaxPlayers;
	short HostPort;
	std::string HostIP;
	std::vector<std::string> Players;
};