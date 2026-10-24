#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;

class MapDemoStateWarp : public ActorStateBase<GrandGalaxyMap> {
public:
    MapDemoStateWarp(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();

    void exeWait();

    /* 0x10 */ s32 mWarpWorldId;
    /* 0x14 */ u32 _14; // Unknown
    /* 0x18 */ f32 mZoom; // Unknown
};
