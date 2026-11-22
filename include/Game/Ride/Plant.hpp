#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class ActorCameraInfo;
class J3DShapeDraw;
class PartsModel;
class PlantStalk;
class PlantLeaf;

class Plant : public LiveActor {
public:
    /// @brief Creates a new `Plant`
    /// @param pName A pointer to the null-terminated name of the object.
    Plant(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();
    virtual void draw() const;
    virtual void calcAnim();
    virtual void appear();
    virtual void startClipped();
    virtual void endClipped();
    virtual void updateHitSensor(HitSensor* pSensor);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void initLeaf();
    void updateTopMtx();
    bool updateGrowUp();
    bool updateHangUp(f32);
    void updateBindLeaf();

    void startGrowUp();

    bool tryHangUp();
    bool tryReachGoal();
    bool tryAccelHangUp();

    void exeWaitFar();
    void exeSeedWait();
    void exeWaitDemoWaitGrowUp();
    void exeDemoWaitGrowUp();
    void exeGrowUp();
    void exeHangWaitGrowUp();
    void exeHangUpGrowUp();
    void exeGrowthStop();
    void exeGrowthWait();
    void exeGrowthWaitInvalid();
    void exeHangStart();
    void exeHangUp();
    void exeHangDown();

    /* 0x090 */ PartsModel* mSeedPartsModel;
    /* 0x094 */ TPos3f mSeedMtx;
    /* 0x0C4 */ PlantStalk* mStalk;
    /* 0x0C8 */ PartsModel* mTopPartsModel;
    /* 0x0CC */ TPos3f mTopMtx;
    /* 0x0FC */ s32 mNumLeaves;
    /* 0x100 */ PlantLeaf** mLeaves;
    /* 0x104 */ J3DShapeDraw* mShapeDraw;
    /* 0x108 */ LiveActor* mRider;
    /* 0x10C */ f32 mRailCoord;
    /* 0x110 */ TVec3f mUp;
    /* 0x11C */ TVec3f mFront;
    /* 0x128 */ f32 mRideVelocity;
    /* 0x12C */ s32 mAccelTimer;
    /* 0x130 */ f32 mJumpSpeed;
    /* 0x134 */ f32 mJumpSpeedOffsetY;
    /* 0x138 */ TVec3f mClippingCenter;
    /* 0x144 */ ActorCameraInfo* mCameraInfo;
    /* 0x148 */ bool mPlayAppearDemo;
    /* 0x149 */ bool mGrabbedTop;
};
