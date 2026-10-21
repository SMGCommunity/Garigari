#pragma once

#include "Game/LiveActor/LiveActorFlag.hpp"
#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class ActorActionKeeper;
class ModelManager;
class Spine;
class HitSensorKeeper;
class Binder;
class RailRider;
class EffectKeeper;
class ActorSoundHolder;
class LiveActorFlag;
class ShadowControllerList;
class CollisionParts;
class StageSwitchCtrl;
class StarPointerTarget;
class ActorLightCtrl;
class ShadowControllerList;
class StarPointerTarget;
class HitSensor;
class Nerve;
class ResourceHolder;

class LiveActor : public NameObj {
public:
    /// @brief Creates a new `LiveActor`.
    /// @param pName A pointer to the null-terminated name of the actor.
    LiveActor(const char* pName);

    /* 0x0C */ virtual void init(const JMapInfoIter&);
    /* 0x14 */ virtual void movement();
    /* 0x1C */ virtual void calcAnim();
    /* 0x20 */ virtual void calcViewAndEntry();
    /* 0x2C */ virtual void appear();
    /* 0x30 */ virtual void makeActorAppeared();
    /* 0x34 */ virtual void kill();
    /* 0x38 */ virtual void makeActorDead();
    /* 0x3C */ virtual bool receiveMessage(u32, HitSensor*, HitSensor*);
    /* 0x40 */ virtual MtxPtr getBaseMtx() const;
    /* 0x44 */ virtual MtxPtr getTakingMtx() const;
    /* 0x48 */ virtual void startClipped();
    virtual void endClipped();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void updateHitSensor(HitSensor*);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPush(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    HitSensorKeeper* getSensorKeeper() const {
        return mSensorKeeper;
    }

    void calcAnmMtx();
    void setNerve(const Nerve*);
    bool isNerve(const Nerve*) const;
    s32 getNerveStep() const;

    HitSensor* getSensor(const char*) const;

    void initModelManagerWithAnm(const char*, const char*, const char*, bool);
    void initNerve(const Nerve*, s32 = 0);
    void initHitSensor(s32);
    void initBinder(f32, f32, u32);
    void initRailRider(const JMapInfoIter&);
    void initEffectKeeper(s32, const char*, bool);
    void initSound(s32, const char*, const TVec3f*, const TVec3f&);
    void initShadowControllerList(u32);
    void initActorCollisionParts(const char*, HitSensor*, ResourceHolder*, MtxPtr, bool, bool);
    void initStageSwitch(const JMapInfoIter&);
    void updateBinder();

    TVec3f mPosition;                   // 0x14
    TVec3f mRotation;                   // 0x20
    TVec3f mScale;                      // 0x2C
    TVec3f mVelocity;                   // 0x38
    TVec3f mGravity;                    // 0x44
    ActorActionKeeper* mActionKeeper;   // 0x50
    ModelManager* mModelManager;        // 0x54
    Spine* mSpine;                      // 0x58
    HitSensorKeeper* mSensorKeeper;     // 0x5C
    Binder* mBinder;                    // 0x60
    RailRider* mRailRider;              // 0x64
    EffectKeeper* mEffectKeeper;        // 0x68
    ActorSoundHolder* mSoundHolder;     // 0x6C
    LiveActorFlag mFlags;               // 0x70
    ShadowControllerList* mShadowList;  // 0x7C
    CollisionParts* mCollisionParts;    // 0x80
    StageSwitchCtrl* mSwitchCtrl;       // 0x84
    StarPointerTarget* mPointerTarget;  // 0x88
    ActorLightCtrl* mLightCtrl;         // 0x8C
};
