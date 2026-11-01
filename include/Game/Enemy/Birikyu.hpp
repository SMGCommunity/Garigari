#pragma once

#include "Game/LiveActor/LiveActor.hpp"

/// @brief Faceless Amp
class Birikyu : public LiveActor {
public:
    Birikyu(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void control();
    virtual void movement();
    virtual void startClipped();
    virtual void endClipped();
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

    /* 0x8C */ char* _8C;
    /* 0x90 */ const char* mObjectName;
    /* 0x94 */ TVec3f mRailClipCenter;
    /* 0xA0 */ TVec3f mOrbitCenter;

    /// @brief JMapInfo arg 2.
    /* 0xAC */ bool mHasShadow;

    /* 0xAD */ bool mIsConnected;
    /* 0xB0 */ TVec3f mUpVec;
    /* 0xBC */ TVec3f mFrontVec;

    /// @brief In radians.
    /* 0xC8 */ f32 mOrbitAngle;

    /// @brief Used for both rail movement and orbit speed.
    /* 0xCC */ f32 mMoveSpeed;
};

/// @brief Amp
class BirikyuWithFace : public Birikyu {
public:
    BirikyuWithFace(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void calcAndSetBaseMtx();

    /// @brief JMapInfo arg 1.
    /* 0xD0 */ u32 _D0;
    /* 0xD4 */ bool _D4;
    /* 0xD5 */ u8 _D5;
    /* 0xD8 */ s32 _D8;
};
