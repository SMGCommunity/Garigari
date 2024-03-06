#pragma once

#include "Game/System/NerveExecutor.hpp"
#include "Game/System/GameSystemSceneController.hpp"

class GameSystem : public NerveExecutor {
public:
    u8 _8[0x24 - 0x8];
    GameSystemSceneController* mSceneController;        // _24
};