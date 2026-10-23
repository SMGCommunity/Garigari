#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class AnimScaleController;
template < typename T >
class JointControlDelegator;
class JointControllerInfo;
class WalkerStateBindStarPointer;

class BombTeresa : public LiveActor {
public:
    BombTeresa(const char*);

    virtual ~BombTeresa() {
    }
    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void makeActorAppeared();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPush(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveMsgEnemyAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    void initTongue();
    void initSensor();
    void initFromJMapParam(const JMapInfoIter&);
    void exeAppear();
    void exeShadowAppear();
    void exeBallAppear();
    void exeWait();
    void exeWander();
    void exeChase();
    void exeAttackTongueFailed();
    void exeDirectTackleSign();
    void exeDirectTackle();
    void exeDrift();
    void exeDriftRelease();
    void exeBindStarPointer();
    void endBindStarPointer();
    void exeExplosion();
    void exeShock();
    void exeDisperse();
    void exeReadyRestart();
    bool tryCheseEnd();
    bool tryDirectTackle();
    bool tryAbortDrift();
    bool tryDriftRelease();
    bool tryDriftReleaseEnd();
    bool tryExplosion();
    bool tryRevival();
    bool requestDrift();
    bool requestDisperse();
    bool appearNormal(const TVec3f&, const TVec3f&);
    bool appearShadow(const TVec3f&, const TVec3f&);
    bool rootTongueMtxCallBack(TPos3f*, const JointControllerInfo&);
    bool endTongueMtxCallBack(TPos3f*, const JointControllerInfo&);
    void updateNormalVelocity();
    void updateDriftReleaseVelocity();
    bool isTouchTongue() const NO_INLINE;
    bool isEnableDrift() const NO_INLINE;
    bool isEnablePointBind() const NO_INLINE;
    bool isEnableDisperse() const NO_INLINE;
    bool isEnableHitExplosionToPlayer() const NO_INLINE;
    bool isEnableHitExplosionToEnemy() const NO_INLINE;
    bool isEnableHitExplosion() const NO_INLINE;
    bool isEnableStarPieceAttack() const NO_INLINE;
    bool isEnableShockWave() const NO_INLINE;
    void addTeresaSpinPullVelocity(f32);

    inline bool isOutOfRange(f32 dist) {
        return !MR::isNearPlayer(this, dist);
    }

    /* 0x90 */ JointControlDelegator< BombTeresa >* mJointDelegator;
    /* 0x94 */ JointControlDelegator< BombTeresa >* mJointDelegator2;
    /* 0x98 */ AnimScaleController* mScaleController;
    /* 0x9C */ WalkerStateBindStarPointer* mBindStarPointer;
    /* 0xA0 */ TQuat4f _A0;
    /* 0xB0 */ TVec3f _B0;
    /* 0xBC */ TVec3f _BC;
    /* 0xC8 */ TVec3f _C8;
    /* 0xD4 */ TVec3f _D4;
    /* 0xE0 */ f32 _E0;
    /* 0xE4 */ f32 _E4;
    /* 0xE8 */ f32 _E8;
    /* 0xEC */ s32 _EC;
    /* 0xF0 */ bool _F0;
    /* 0xF1 */ bool mDisableRespawning;
    /* 0xF2 */ bool _F2;
    /* 0xF3 */ bool _F3;
};
