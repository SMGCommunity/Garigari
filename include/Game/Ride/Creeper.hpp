#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class ActorCameraInfo;
class JUTTexture;
class PartsModel;

/// @brief A control point used by the `Creeper` to control the bending of the stalk
class CreeperPoint {
public:
    /// @brief Creates a new `CreeperPoint`
    /// @param rPos Position of the control point
    /// @param rUp Upwards direction of control point to the next point
    /// @param pPrevPoint Pointer to the previous point in the `Creeper` stalk
    CreeperPoint(const TVec3f& rPos, const TVec3f& rUp, const CreeperPoint* pPrevPoint);

    void updateFree();
    void updateBend(bool bend, const TVec3f& bendDirection, f32 t, f32 bendRate);
    void updateLocalAxis();

    const TVec3f& getPosition() const {
        return mPosition;
    }

    const TVec3f& getSide() const {
        return mSide;
    }

    const TVec3f& getUp() const {
        return mUp;
    }

    const TVec3f& getFront() const {
        return mFront;
    }

    /* 0x00 */ TVec3f mPosition;
    /* 0x0C */ TVec3f mNeutralPos;
    /* 0x18 */ TVec3f mVelocity;
    /* 0x24 */ TVec3f mSide;
    /* 0x30 */ TVec3f mUp;
    /* 0x3C */ TVec3f mFront;
    /* 0x48 */ TVec3f mProjection;
    /* 0x54 */ const CreeperPoint* mPrevPoint;
};

class Creeper : public LiveActor {
public:
    /// @brief Creates a new `Creeper`
    /// @param pName A pointer to the null-terminated name of the object.
    Creeper(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void control();
    virtual void draw() const;
    virtual void makeActorAppeared();
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeFree();
    void exeFreeInvalid();
    void exeHangStart();
    void exeHangUp();
    void exeHangDown();

    void initPoints();
    void updatePoints();
    void bendPoints();

    bool tryHangUp();
    bool tryJump();
    bool updateHangUp(f32 rotateSpeed);

    void calcAndGetCurrentInfo(TVec3f* pPosition, TVec3f* pUp) const;

    void loadMaterial() const;
    const CreeperPoint* getHeadPoint() const {
        return getPoint(mNumPoints - 1);
    }

    inline const CreeperPoint* getPoint(s32 idx) const {
        return mPoints[idx];
    }

    /* 0x90 */ s32 mNumPoints;
    /* 0x94 */ CreeperPoint** mPoints;
    /* 0x98 */ LiveActor* mRider;
    /* 0x9C */ TVec3f mFront;
    /* 0xA8 */ TVec3f mUp;
    /* 0xB4 */ f32 mHangSpeed;
    /* 0xB8 */ f32 mCoord;
    /* 0xBC */ f32 mBendRate;
    /* 0xC0 */ f32 mBendRateBee;
    /* 0xC4 */ TVec3f mBendDirection;
    /* 0xD0 */ f32 mJumpSpeedFront;
    /* 0xD4 */ f32 mJumpSpeedUp;
    /* 0xD8 */ ActorCameraInfo* mCameraInfo;
    /* 0xDC */ TVec3f mClippingCenter;
    /* 0xE8 */ JUTTexture* mTexture;
    /* 0xEC */ PartsModel* mFlowerModel;
    /* 0xF0 */ PartsModel* mLeafModel;
    /* 0xF4 */ TPos3f mTopMtx;
};
