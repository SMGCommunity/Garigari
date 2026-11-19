#pragma once

#include "Game/LiveActor/LiveActor.hpp"

/// @brief Faceless Amp
class Birikyu : public LiveActor {
public:
    Birikyu(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void movement();
    virtual void startClipped();
    virtual void endClipped();
    virtual void control();
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void initFromJmpArgs(const JMapInfoIter&);
    void initRail(const JMapInfoIter&);
    bool tryStopPointing() NO_INLINE;
    void goMove();
    void endStopPointing();
    bool isMoving() const;

    void exeMove();
    void exeMoveCircle();
    void exeWaitAtEdge();
    void exeAttack();
    void exeAttackWait();
    void exeStopPointing();
    void exeKill();

    /* 0x8C */ char* _90;
    /* 0x94 */ const char* mObjectName;
    /* 0x98 */ TVec3f mRailClipCenter;
    /* 0xA4 */ TVec3f mOrbitCenter;

    /// @brief JMapInfo arg 2.
    /* 0xB0 */ bool mHasShadow;

    /* 0xB1 */ bool mIsConnected;
    /* 0xB4 */ TVec3f mUp;
    /* 0xC0 */ TVec3f mFront;

    /// @brief In radians.
    /* 0xCC */ f32 mOrbitAngle;

    /// @brief Used for both rail movement and orbit speed.
    /* 0xD0 */ f32 mMoveSpeed;
};

/// @brief Amp
class BirikyuWithFace : public Birikyu {
public:
    BirikyuWithFace(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void calcAndSetBaseMtx();

    /* 0xD4 */ bool mSideType;
    /* 0xD8 */ s32 mGravityType;
};
