#pragma once

#include "NameObj/NameObj.hpp"
#include "LiveActor/LiveActorFlag.hpp"
#include <JGeometry.hpp>

class ActorActionKeeper;
class ActorLightCtrl;
class ActorSoundHolder;
class Binder;
class CollisionParts;
class EffectKeeper;
class HitSensorKeeper;
class ModelManager;
class RailRider;
class ShadowControllerList;
class Spine;
class StageSwitchCtrl;
class StarPointerTarget;

class LiveActor : public NameObj {
public:

    TVec3f mPosition;                       // 0x14
    TVec3f mRotation;                       // 0x20
    TVec3f mScale;                          // 0x2C
    TVec3f mVelocity;                       // 0x38
    TVec3f mGravity;                        // 0x44
    ActorActionKeeper* mActionKeeper;       // 0x50
    ModelManager* mModelManager;            // 0x54
    Spine* mSpine;                          // 0x58
    HitSensorKeeper* mSensorKeeper;         // 0x5C
    Binder* mBinder;                        // 0x60
    RailRider* mRailRider;                  // 0x64
    EffectKeeper* mEffectKeeper;            // 0x68
    ActorSoundHolder* mSoundHolder;         // 0x6C
    LiveActorFlag mFlags;                   // 0x70
    ShadowControllerList* mShadowList;      // 0x7C
    CollisionParts* mCollisionParts;        // 0x80
    StageSwitchCtrl* mSwitchCtrl;           // 0x84
    StarPointerTarget* mPointerTarget;      // 0x88
    ActorLightCtrl* mLightCtrl;             // 0x8C
};