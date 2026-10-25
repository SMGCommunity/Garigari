#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class GrandGalaxyMap;

class MapDemoStateMove : public ActorStateBase< GrandGalaxyMap > {
public:
    MapDemoStateMove(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();
    virtual void kill();

    void exeNerve1();

    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1C */ TVec3f _1C;
    /* 0x28 */ TVec3f _28;
    /* 0x34 */ TVec3f _34;
    /* 0x40 */ f32 _40;
    /* 0x44 */ f32 _44;
    /* 0x48 */ f32 _48;
    /* 0x4C */ s32 _4C;
    /* 0x50 */ s32 _50;
    /* 0x54 */ u32 _54;
};
