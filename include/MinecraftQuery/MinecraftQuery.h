#pragma once

#include "../../src/Query/BasicStat.h"
#include "../../src/Query/FullStat.h"

class MinecraftQuery
{
public:
	static bool FillBasicStat(BasicStat& stat, std::string address, std::string port);
	static bool FillFullStat(FullStat& stat, std::string address, std::string port);

	static bool Initialize();
	static bool Cleanup();
};