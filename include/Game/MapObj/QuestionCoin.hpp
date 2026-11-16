#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class ActorCameraInfo;

class QuestionCoin : public LiveActor {
public:
    /// @brief Creates a new `QuestionCoin`.
    /// @param pName Pointer to a null-terminated string that will be used as a name for the Question Coin.
    QuestionCoin(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void makeActorAppeared();
    virtual void kill();
    virtual void startClipped();
    virtual void endClipped();
    virtual void calcAndSetBaseMtx();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void initFromJMapInfoArg(const JMapInfoIter& rIter);
    void initShadow();
    void updateActorMtx();

    void exeWait();
    void exeThrowActor();
    void exeCaught();
    void exeKilled();

    bool isThrowActor() const {
        return 0.0f < mLaunchSpeed;
    }

    /* 0x090 */ TPos3f mBaseMtx;

    /// @brief Pointer to the `LiveActor` that will be made to jump upon collecting the Coin. Basically, this points to the player.
    /* 0x0C0 */ LiveActor* mBindActor;

    /// @brief The base matrix of the `LiveActor` that will be made to jump upon collecting the Coin. Basically, the player's base matrix.
    /* 0x0C4 */ TPos3f mActorMtx;

    /* 0x0F4 */ TQuat4f mLaunchQuat;
    /* 0x104 */ ActorCameraInfo* mCameraInfo;

    /// @brief If set to a positive value, the player will jump after collecting the Coin. Default is 0.
    /* 0x108 */ f32 mLaunchSpeed;

    /// @brief Specifies how the player jumps when collecting the Coin. `false` means normal gravity jump; `true` means weak gravity jup.
    /* 0x10C */ bool mIsWeakGravity;

    /// @brief If `true`, the shadow will be calculated at all times.
    /* 0x10D */ bool mIsCalcShadow;

    /* 0x110 */ s32 mPoseType;

    /// @brief Sets the shadow drop length. Only a fixed set of length values are supported: `-1` for 1000, `1` for 1500, and `2` for 2000.
    /* 0x114 */ s32 mShadowLengthType;

    /* 0x118 */ TVec3f mShadowPos;
    /* 0x124 */ f32 mShadowDropLength;
};
