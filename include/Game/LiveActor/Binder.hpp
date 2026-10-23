#pragma once

#include "Game/Map/HitInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include <revolution.h>

class Binder {
public:
    u8 _0[0x18];
    f32 mRadius;  // 0x18
    f32 mOffsetY;

    void setTriangleFilter(TriangleFilterBase*);
    void setCollisionPartsFilter(CollisionPartsFilterBase*);

    const HitInfo* getPlane(int) const;
    
    inline bool isBindedGround() const {
        return 0.0f <= _C8;
    }

    inline bool isBindedWall() const {
        return 0.0f <= _158;
    }

    inline bool isBindedRoof() const {
        return 0.0f <= _1E8;
    }

    TriangleFilterBase* mTriangleFilter;
    const TVec3f* mOffsetVec;
    u32 mPlaneNum;
    TVec3f mFixReactionVector;
    HitInfo mGroundInfo;
    f32 _C8;
    HitInfo mWallInfo;
    f32 _158;
    HitInfo mRoofInfo;
    f32 _1E8;
    struct {
        u8 _0 : 1;
        u8 _1 : 1;
        u8 _2 : 1;
        u8 _3 : 1;
        u8 _4 : 1;
        u8 _5 : 1;
    } _1EC;
};
