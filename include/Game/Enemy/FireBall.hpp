#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class AnimScaleController;
class WalkerStateBindStarPointer;

class FireBall : public LiveActor {
public:
    FireBall(const char*);

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual void kill();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);

    void appearAndThrow(const TVec3f&, f32, f32);
    void fn_8017DA20(const TVec3f&, const TVec3f&);
    HitSensor* isBindedAny() const;
    bool tryToKill();
    void setVelocityToPlayer(f32);

    void exeThrow();
    void exeFreeze();
    void exeReflect();

    /* 0x90 */ LiveActor* mHost;
    /* 0x94 */ AnimScaleController* mScaleController;
    /* 0x98 */ WalkerStateBindStarPointer* mWalkerStateBindStarPointer;  // Rename?
    /* 0x9C */ TVec3f _9C;
    /* 0xA8 */ TVec3f _A8;
    /* 0xB4 */ f32 _B4;
};
