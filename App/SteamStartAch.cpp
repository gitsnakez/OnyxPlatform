#include "SteamStartAch.h"
#include <Windows.h>

#define START_ACHIEVEMENT "ACH_FIRST_START"

namespace onyxengine
{
	void RequestForStat(ISteamUserStats* user)
	{
		if (!user->RequestCurrentStats()) MessageBox(NULL, L"l", L"SteamAPI", MB_OK);
	}

	bool CheckAchivement(ISteamUserStats* user)
	{
		bool isachieved = false;
		if (!user->GetAchievement(START_ACHIEVEMENT, &isachieved)) MessageBox(NULL, L"Achievement get info failed!", L"SteamAPI", MB_OK);

		return isachieved;
	}

	void SetFirstStartAchievement()
	{
		ISteamUserStats* userStats = SteamUserStats();

		RequestForStat(userStats);
		if (!CheckAchivement(userStats))
			if (!userStats->SetAchievement(START_ACHIEVEMENT)) MessageBox(NULL, L"Achievement set failed!", L"SteamAPI", MB_OK);
	}

	void AchievementReset()
	{
		ISteamUserStats* userStats = SteamUserStats();

		RequestForStat(userStats);
		if (CheckAchivement(userStats))
			if (!userStats->ClearAchievement(START_ACHIEVEMENT)) MessageBox(NULL, L"Achievement reset failed!", L"SteamAPI", MB_OK);
	}
}