#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class CollisionParts;
class MapObjConnector;
class SpringValue;

class HipDropSwitch : public LiveActor {
public:
    HipDropSwitch(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void calcAnim();
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    bool trySwitchDown();
    bool tryOn();
    bool isPlayerOnTop();

    void exeOff();
    void exeSwitchDown();
    void exeOn();

    /* 0x90 */ u32 _90;  // useless
    /* 0x94 */ SpringValue* mSpringValue;
    /* 0x98 */ MapObjConnector* mConnector;
    /* 0x9C */ CollisionParts* mSpringModel;
    /* 0xA0 */ TPos3f _A0;
    /* 0xD0 */ bool _D0;
    /* 0xD1 */ bool _D1;
    /* 0xD2 */ bool _D2;
};
