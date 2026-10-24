#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class SpringValue;
class MapObjConnector;
class CollisionParts;

class HipDropTimerSwitch : public LiveActor {
public:
    HipDropTimerSwitch(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void calcAnim();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    void updateTimerSE();
    void exeOff();
    void exeSwitchDown();
    void exeOn();
    void exeSwitchUp();
    void exeSyncOn();
    void exeSyncOff();

    void listenSwitchOnA();
    void listenSwitchOffA();

    /* 0x90 */ u32 _8C;
    /* 0x94 */ SpringValue* mSpring;
    /* 0x98 */ MapObjConnector* mMapObjConnector;
    /* 0x9C */ CollisionParts* mCollisionParts;
    /* 0xCC */ TPos3f _9C;
    /* 0xD0 */ s32 mTimerMax;      // In frames
    /* 0xD4 */ s32 mTimerSFXType;  // 0: A ticking, 1: B ticking
    /* 0xD8 */ u8 _D4;
    /* 0xD9 */ bool mWasLightPressed;
    /* 0xDA */ bool mIsLightPressed;
    /* 0xDC */ s32 mScreenEffectType; // NEW to SMG2. 0 = NONE, 1 = createSwitchingScreenEffect (Missing ObjectData file), 2 = createTimeStopScreenEffect
};
