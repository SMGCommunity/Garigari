#pragma once

#include "Game/Gravity/PlanetGravity.hpp"

class BarrelGravity : public PlanetGravity {
    BarrelGravity();

    virtual void updateMtx(const TPos3f& rMtx);
    virtual bool calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPosition) const;

    void setLocalPosition(const TVec3f& rPosition);
    void setUpDirection(const TVec3f& rDirection);
    void setRadius(f32 radius);
    void setUnusedArg0(f32 arg0);
    void setInwardsThreshold(f32 threshold);

    /* 0x28 */ TVec3f mLocalPos;
    /* 0x34 */ TVec3f _34;
    /* 0x40 */ TVec3f mUpDir;
    /* 0x4C */ f32 _4C;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
    /* 0x58 */ f32 mRadius;
    /* 0x5C */ f32 _5C;
    /* 0x60 */ f32 _60;
    /* 0x64 */ f32 mThreshold;
};
