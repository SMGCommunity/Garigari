#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class AnimScaleController;
class WalkerStateBindStarPointer;
class FireBallSpreadLava;

class FireBallSpread : public LiveActor {
public:
    FireBallSpread(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void appear();
    virtual void kill();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveMsgEnemyAttack(u32, HitSensor*, HitSensor*);

    void appearAndThrow(const TVec3f&, f32, f32);
    void fn_8017E660(const TVec3f&, const TVec3f&);
    void fn_8017E6D0(const TVec3f&, const TVec3f&);
    bool fn_8017E750() const;
    bool fn_8017E7B0();
    HitSensor* isBindedAny() const;
    bool tryToKill();
    void setVelocityToPlayer(f32);
    void fn_8017EDF0();

    void exeThrow();
    void exeFreeze();
    void exeReflect();

    /* 0x90 */ LiveActor* mHost;
    /* 0x94 */ AnimScaleController* mScaleController;
    /* 0x98 */ WalkerStateBindStarPointer* mWalkerStateBindStarPointer;  // Rename?
    /* 0x9C */ TVec3f _9C;
    /* 0xA8 */ TVec3f _A8;
    /* 0xB4 */ f32 _B4;
    /* 0xB8 */ FireBallSpreadLava* mLava;
    /* 0xBC */ s32 mTimer;
    /* 0xC0 */ bool mIsFalling;
};
