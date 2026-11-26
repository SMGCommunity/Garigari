#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class AnimScaleController;
class WalkerStateBindStarPointer;
class YoshiLockOnTarget;

class Buzz : public LiveActor {
public:
    Buzz(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    bool isSupportFreezable() const;
    bool fn_80176300() const NO_INLINE;
    bool fn_80176310() const;
    bool fn_80176390() const;
    bool isYoshiEatable() const;

    void exeWait();
    void exeYoshiEaten();
    void exeSupportFreeze();
    void exeStarPieceHit();
    void exeAttackSuccess();
    void exeBlowDown();
    void exeStepDown();

    /* 0x90 */ TVec3f mClippingCenter;
    /* 0x9C */ TVec3f mFrontVec;
    /* 0xA8 */ f32 mRailSpeed;
    /* 0xAC */ AnimScaleController* mScaleController;
    /* 0xB0 */ WalkerStateBindStarPointer* mWalkerStateBindStarPointer; // Rename?
    /* 0xB4 */ YoshiLockOnTarget* mYoshiLockOnTarget;
};
