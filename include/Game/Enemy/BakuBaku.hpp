#pragma once

#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "JSystem/JGeometry/TVec.hpp"

class AnimScaleController;
class ActorStateBaseInterface;

class BakuBaku : public LiveActor {
public:
    BakuBaku(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void control();
    virtual void calcAndSetBaseMtx();    
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);

    void exeWait();
    void exeTurn();
    void exeMove();
    void exeSuccess();

    void startEatSound();
    void updateRideOnRail();
    void updateRideFree();
    bool isAttackable() const;
    bool isMoving() const;
    bool isStarPointerBindable() const;

    /* 0x90 */ //class* _90;
    /* 0x94 */ AnimScaleController* mFront;
    /* 0x98 */ ActorStateBaseInterface* mMovementSpeed; 
    /* 0x9C */ TVec3f _9C; 
    /* 0xA8 */ s32 mRailSpeed;  
};
