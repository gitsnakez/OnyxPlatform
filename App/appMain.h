#pragma once

#include "steam_api.h"

int PreQuit(int PriorityCode)
{
	SteamAPI_Shutdown();
	return PriorityCode;
}

#define EngineShutdown(code) return PreQuit(code)