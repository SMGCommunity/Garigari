#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class SupportTicoStop;

class Foomin : public LiveActor {
public:
    Foomin(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void makeActorAppeared();
    virtual void control();
    virtual void calcAndSetBaseMtx();

    void exeWait();
    void exeWaitDelay();
    void exeAttackSign();
    void exeAttack();

    /* 0x90 */ SupportTicoStop* mSupportTicoStop;
    /* 0x94 */ TVec3f _94;
    /* 0xA0 */ u32 mMovementSpeed; ///< Default is 250.
    /* 0xA4 */ s32 mFirstFlipDelay; ///< The delay for the first flip which can be edited via Obj Arg 0.
};
