#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class GliderCometMedalCage : public LiveActor {
public:
    GliderCometMedalCage(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeMove();

    /* 0x90 */ s32 _90;  // unused
};
