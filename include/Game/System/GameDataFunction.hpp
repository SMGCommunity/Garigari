#pragma once

#include <revolution/os.h>

class GameDataHolder;
class GameDataSomeScenarioAccessor;
class JMapInfoIter;

namespace GameDataFunction {
    bool isOnGalaxyFlagTicoCoin(const char* pStageName);
    void onGameEventFlag(const char*);
    bool isOnGameEventFlag(const char*);
    s32 getPlayerGameOverNum();
    s32 getCurrentWorldId();
}
