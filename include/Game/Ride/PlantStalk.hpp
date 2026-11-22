#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class PlantPoint;
class PlantRailInfo;
class JUTTexture;

class PlantStalk : public LiveActor {
public:
    /// @brief Creates a new `PlantStalk`
    PlantStalk();

    virtual void init(const JMapInfoIter& rIter);
    virtual void draw() const;
    virtual void drawGrowUp() const;

    bool updateGrowUp();
    void calcPosAndAxisY(TVec3f* pPos, TVec3f* pAxisY, f32 lengthAlongRail) const;

    void calcNearestPos(TVec3f* pRailPos, const TVec3f& rSrcPos) const;
    f32 calcPlayerCoord() const;

    /* 0x90 */ s32 mNumPlantPoints;
    /* 0x94 */ PlantPoint** mPlantPoints;
    /* 0x98 */ PlantRailInfo* mRailInfo;
    /* 0x9C */ f32 mStalkLength;
    /* 0xA0 */ f32 mGrowthPercent;
    /* 0xA4 */ f32 mGrowSpeed;
    /* 0xA8 */ s32 mGrowAccelTime;
    /* 0xAC */ s32 mGrownPlantPoints;
};

class PlantStalkDrawInit : public NameObj {
public:
    PlantStalkDrawInit(const char*);

    virtual void initDraw() const;

    /* 0x0C */ JUTTexture* mTexture;
};
