#pragma once

#include "Game/Map/LightPointCtrl.hpp"

#include <revolution.h>

class LiveActor;
class ActorLightInfo;
class AreaLightInfo;

class ActorLightCtrl {
public:
    ActorLightCtrl(const LiveActor*);

    bool operator=(const ActorLightInfo&);

    void init(int, bool);
    void update(bool);
    void loadLight() const;
    void reset();
    void copy(const ActorLightCtrl*);
    void setLightType(s32);
    void isSameLight(const ActorLightCtrl*) const;
    void getActorLight() const;
    void tryFindNewAreaLight(bool);
    void updateLightBlend();
    void resetCurrentLightInfo();
    void getTargetActorLight(const AreaLightInfo*) const;

    /* 0x00 */ const LiveActor* mActor;
    /* 0x04 */ u32 _4;
    /* 0x08 */ u32 _8;
    /* 0x0C */ u32 _C;
    /* 0x10 */ u32 _10;
    /* 0x14 */ ZoneLightID mZoneLightID;
    /* 0x1C */ u32 _1C;
    /* 0x20 */ u32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 _28;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ u32 _30;
    /* 0x34 */ u32 _34;
    /* 0x38 */ u32 _38;
    /* 0x3C */ u32 _3C;
    /* 0x40 */ u32 _40;
    /* 0x44 */ u32 _44;
    /* 0x48 */ u32 _48;
    /* 0x4C */ u32 _4C;
    /* 0x50 */ u32 _50;
    /* 0x54 */ u32 _54;
};
