#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;

class MapDemoStateWait : public ActorStateBase< GrandGalaxyMap > {
public:
    MapDemoStateWait(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();
    virtual void kill();

    void exeNerve1();

    void fn_804E26F0(s32);  // Unknown
    void fn_804E2750();     // Unknown

    /* 0x10 */ s32 _10;  // Unknown
    /* 0x14 */ s32 _14;  // Unknown
    /* 0x18 */ s32 mWaitTime;
};
