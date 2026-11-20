#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class ActorCameraInfo;
class JUTTexture;
class SledRopePoint;
class SwingRopePoint;

// DOCUMENTME

/// @brief A hanging vine which the player can hold onto and swing around.
class SwingRope : public LiveActor {
public:
    /// @brief Creates a new `SwingRope`
    /// @param pName A pointer to the null-terminated name of the object.
    SwingRope(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void draw() const;
    virtual void updateHitSensor(HitSensor* pSensor);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeStop();
    void exeFree();
    void exeFreeInvalid();
    void exeBindSlideDownStart();
    void exeBindSlideDown();
    void exeBindStretch();
    void exeBindLoose();

    void initPoints();

    /// @brief Converts the given coordinate to a normalized value from [0.0f, mNumPoints - 1.0f)
    /// @param coord Coordinate along real length of `SwingRope`
    /// @return Normalized value, whole part corresponding to point index, fractional part corresponding to normalized distance between points
    f32 calcPointNo(f32 coord) const;

    /// @brief Calculates the friction to apply to the given point
    /// @param index Index of point to calculate friction for
    /// @return Friction of given point
    f32 calcFriction(s32 index) const;

    void addPointGravity();
    void restrictPointToTail(s32 index, const TVec3f* pAnchor, f32 length = 0.0f);
    void restrictPointToHead(s32 index, const TVec3f& rAnchor, f32 length = 0.0f);

    bool isAllPointsStop() const;
    bool isAllPointsSlow() const;
    bool isStretched() const;
    bool tryJump();
    void updateHangPoint();
    void updateRideMtx();
    void updateFootPos();
    bool updateStretch();
    bool updateLoose();
    void updateLooseUpperPoints();
    bool updateSlideDown();
    void updateStretchHangUpperPoints();
    void updateHangLowerPoints();
    void updateHangLowerPointPos(s32 index);

    void drawStop() const;
    void drawFree() const;
    void drawBind() const;

    const TVec3f& getBasePos() const {
        return mBasePos;
    }

    /* 0x090 */ TVec3f mBasePos;
    /* 0x09C */ f32 mRopeLength;
    /* 0x0A0 */ bool mIsStretched;
    /* 0x0A4 */ s32 mStretchTime;  ///< Time since start of stretch condition
    /* 0x0A8 */ s32 mAccelTime;    ///< Time since start of accel
    /* 0x0AC */ s32 mNumPoints;
    /* 0x0B0 */ SwingRopePoint** mPoints;
    /* 0x0B4 */ LiveActor* mRider;
    /* 0x0B8 */ TPos3f mRideMtx;
    /* 0x0E8 */ f32 mGrabCoord;
    /* 0x0EC */ f32 mGrabPointNum;
    /* 0x0F0 */ f32 mSlideSpeed;
    /* 0x0F4 */ SledRopePoint* mSledPoint;
    /* 0x0F8 */ ActorCameraInfo* mCameraInfo;
    /* 0x0FC */ f32 mFootCoord;
    /* 0x100 */ f32 mFootPointNum;
    /* 0x104 */ f32 mGrabToFootDist;
    /* 0x108 */ TVec3f mFootPos;
    /* 0x114 */ TVec3f mShadowDropPos;
    /* 0x120 */ f32 mShadowDropOffset;
    /* 0x124 */ s32 mPrevSoundLvl;
};

class SwingRopeGroup : public NameObj {
public:
    SwingRopeGroup(const char* pName);

    virtual void initDraw() const;

    /* 0x0C */ JUTTexture* mTexture;
};
