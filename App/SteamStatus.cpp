#include "SteamStatus.h"

namespace onyxengine
{
    void SetSteamStatus(const char *pStatus, const char* pDisplay)
    {
        SteamFriends()->SetRichPresence("gamestatus", pStatus);
        SteamFriends()->SetRichPresence("steam_display", pDisplay);
    }
}