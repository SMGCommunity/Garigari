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
class ResourceHolder;
class RailRider;
class ShadowControllerList;
class Spine;
class StageSwitchCtrl;
class StarPointerTarget;
class HitSensor;
class Nerve;

class LiveActor : public NameObj {
public:

    virtual ~LiveActor();
    virtual void init(const JMapInfoIter &);
    virtual void movement();
    virtual void calcAnim();
    virtual void calcViewAndEntry();
    virtual void appear();
    virtual void makeActorAppeared();
    virtual void kill();
    virtual void makeActorDead();
    virtual bool receiveMessage(u32, HitSensor *, HitSensor *);
    virtual MtxPtr getBaseMtx() const;
    virtual MtxPtr getTakenMtx() const;
    virtual void startClipped();
    virtual void endClipped();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void updateHitSensor(HitSensor *);
    virtual void attackSensor(HitSensor *, HitSensor *);
    virtual bool receiveMsgPush(HitSensor *, HitSensor *);
    virtual bool receiveMsgPlayerAttack(HitSensor *, HitSensor *);
    virtual bool receiveMsgEnemyAttack(HitSensor *, HitSensor *);
    virtual bool receiveOtherMsg(HitSensor *, HitSensor *);

    HitSensor* getSensor(const char *) const;

    void initModelManagerWithAnm(const char *, const char *, const char *, bool);
    void initNerve(const Nerve *, s32);
    void initHitSensor(s32);
    void initBinder(f32, f32, u32);
    void initRailRider(const JMapInfoIter &);
    void initEffectKeeper(s32, const char *, bool);
    void initSound(s32, const char *, const TVec3f *, const TVec3f &);
    void initShadowControllerList(u32);
    void initActorCollisionParts(const char *, HitSensor *, ResourceHolder *, MtxPtr, bool, bool);

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
