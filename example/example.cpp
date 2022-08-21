#include <iostream>

#include "MinecraftQuery/MinecraftQuery.h"

int main()
{
	MinecraftQuery::Initialize();

	BasicStat basicStat = BasicStat();
	std::cout << MinecraftQuery::FillBasicStat(basicStat, "address", "25565") << '\n';

	std::cout << "Basic Stat:\n"
		<< "\tMOTD: " << basicStat.MOTD << '\n'
		<< "\tGame Type: " << basicStat.GameType << '\n'
		<< "\tMap: " << basicStat.Map << '\n'
		<< "\tPlayers Online: " << basicStat.NumPlayers << '\n'
		<< "\tMax Players: " << basicStat.MaxPlayers << '\n'
		<< "\tHost Port: " << basicStat.HostPort << '\n'
		<< "\tHost IP: " << basicStat.HostIP << '\n';

	FullStat fullStat = FullStat();
	MinecraftQuery::FillFullStat(fullStat, "address", "25565");

	std::cout << "Full Stat:\n"
		<< "\tMOTD: " << fullStat.MOTD << '\n'
		<< "\tGame Type: " << fullStat.GameType << '\n'
		<< "\tGame ID: " << fullStat.GameID << '\n'
		<< "\tVersion: " << fullStat.Version << '\n'
		<< "\tPlugins: " << fullStat.Plugins << '\n'
		<< "\tMap: " << fullStat.Map << '\n'
		<< "\tPlayers Online: " << fullStat.NumPlayers << '\n'
		<< "\tMax Players: " << fullStat.MaxPlayers << '\n'
		<< "\tHost Port: " << fullStat.HostPort << '\n'
		<< "\tHost IP: " << fullStat.HostIP << '\n'
		<< "\tPlayers:\n";

	for (std::string player : fullStat.Players)
		std::cout << "\t\t" << player << "\n";

	MinecraftQuery::Cleanup();
}