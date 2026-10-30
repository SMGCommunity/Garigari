#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "JSystem/JGeometry/TBox.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"
#include "JSystem/JGeometry/TVec.hpp"

class ActorCameraInfo;

class BlackHole : public LiveActor {
public:
    BlackHole(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void kill();
    virtual void calcAndSetBaseMtx();

    bool tryStartDemoCamera();
    void attackSensor(HitSensor*, HitSensor*);
    void initMapToolInfo(const JMapInfoIter&);
    void initModel();
    void initCubeBox();
    bool isInCubeBox(const TVec3f&) const;
    void updateModelScale(f32, f32);
    void exeWait();
    void exeDemo();
    void exeDisappear();

    /* 0x090 */ ModelObj* _90;
    /* 0x094 */ TVec3f _94;
    /* 0x0A0 */ f32 _A0;
    /* 0x0A4 */ f32 mHitSensorEyeRadius;
    /* 0x0A8 */ TBox3f* mCubeBox;
    /* 0x0AC */ TPos3f _AC;
    /* 0x0DC */ TPos3f mEffectHostMtx;
    /* 0x10C */ ActorCameraInfo* mActorCameraInfo;
};
