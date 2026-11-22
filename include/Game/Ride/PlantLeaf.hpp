#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class J3DMaterial;
class J3DShape;
class J3DShapeDraw;

class PlantLeaf : public LiveActor {
public:
    /// @brief Creates a new `PlantLeaf`
    /// @param leafCoord Coordinate along the parent `Plant` rail
    /// @param rPosiiton Base position of the leaf
    /// @param rGrowDirection Direction leaf will grow
    /// @param leafSize Scale of this leaf
    PlantLeaf(f32 leafCoord, const TVec3f& rPosition, const TVec3f& rGrowDirection, f32 leafSize);

    virtual void init(const JMapInfoIter& rIter);
    virtual MtxPtr getBaseMtx() const {
        return (MtxPtr)&mBaseMtx;
    }

    void updateGrowUp(const TVec3f& rStalkPos, const TVec3f& rAxisY, f32 growthPercent, f32 offset);
    bool updateSpring(const TVec3f& rPos, f32 springPower, f32 growthPercent);
    bool updateSpring(f32 growthPercent);

    MtxPtr getPosMtx() const {
        return (MtxPtr)&mPosMtx;
    }

    /* 0x90 */ f32 mSpringCoord;
    /* 0x94 */ f32 mSpringSpeed;
    /* 0x98 */ f32 mLeafCoord;
    /* 0x9C */ f32 mLeafSize;
    /* 0xA0 */ TVec3f mSide;
    /* 0xAC */ TVec3f mUp;
    /* 0xB8 */ TVec3f mFront;
    /* 0xC4 */ TPos3f mBaseMtx;
    /* 0xF4 */ TPos3f mPosMtx;
};

class PlantLeafDrawInit : public LiveActor {
public:
    PlantLeafDrawInit(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void initDraw() const;

    /* 0x90 */ J3DMaterial* mMaterial;
    /* 0x94 */ J3DShape* mShape;
    /* 0x98 */ J3DShapeDraw* mShapeDraw;
};
