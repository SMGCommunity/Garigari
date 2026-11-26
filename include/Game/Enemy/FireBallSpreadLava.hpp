#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class FireBallSpread;
class ClipAreaDrop;

class FireBallSpreadLava : public LiveActor {
public:
    FireBallSpreadLava(FireBallSpread*, const char*);

    virtual void init(const JMapInfoIter&);
    virtual void control();
    virtual void kill();
    virtual void attackSensor(HitSensor*, HitSensor*);

    void appearLava(const TVec3f&);

    void exeHidden();
    void exeAppear();
    void exeWait();
    void exeShrink();

    /* 0x90 */ FireBallSpread* mHost;
    /* 0x94 */ ClipAreaDrop* mClipAreaDrop;
    /* 0x98 */ f32 _98;
};
