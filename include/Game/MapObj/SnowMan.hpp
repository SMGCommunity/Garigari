#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class AnimScaleController;
class AnimScaleParam;
class DemoObj;

class SnowMan : public LiveActor {
public:
    SnowMan(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);

    void damageHead();
    void damageBody();
    void exeMeltHead();
    void exeMeltBody();
    void exeDownHead();
    void exeDownBody();
    void exeWait();
    void exeWaitBody();
    void exeWaitHead();

    /* 0x90 */ CollisionParts* mHeadCollisionParts;
    /* 0x94 */ CollisionParts* mBodyCollisionParts;
    /* 0x98 */ DemoObj* mDemoObj;
    /* 0x9C */ AnimScaleController* mAnimScaleCtrl;
    /* 0xA0 */ AnimScaleParam* mAnimScaleParam;
};
