#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class MiniRoutePoint : public LiveActor {
public:
    MiniRoutePoint();

    virtual void init(const JMapInfoIter& rIter);
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void control();

    bool fn_804E55D0();
    void setPosition(const TVec3f& rPosition);
    void setOpen(bool open);
    bool startSoundRoadExtend();
    bool startSoundPointOn();
    bool startSoundPointOff();

    bool isPointing() const;
    bool isOpen() const;

    /* 0x90 */ s32 _90;
    /* 0x94 */ LiveActor* mShadowActor;
    /* 0x98 */ bool _98;
    /* 0x99 */ bool _99;
};
