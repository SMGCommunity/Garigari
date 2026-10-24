#pragma once

#include "Game/Map/HitInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include <revolution.h>

class Binder {
public:
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

    /* 0x000 */ TriangleFilterBase* mTriangleFilter;
    /* 0x004 */ CollisionPartsFilterBase* mCollisionPartsFilter;
    /* 0x008 */ CollisionParts* mExCollisionParts;
    /* 0x00C */ MtxPtr _C;
    /* 0x010 */ const TVec3f* _10;
    /* 0x014 */ const TVec3f* _14;
    /* 0x018 */ f32 mRadius;
    /* 0x01C */ f32 mOffsetY;
    /* 0x020 */ const TVec3f* mOffsetVec;
    /* 0x024 */ u32 _24;
    /* 0x028 */ u32 mPlaneNum;
    /* 0x02C */ HitInfo* mPlane;
    /* 0x030 */ TVec3f mFixReactionVector;
    /* 0x03C */ HitInfo mGroundInfo;
    /* 0x0C8 */ f32 _C8;
    /* 0x0D4 */ HitInfo mWallInfo;
    /* 0x160 */ f32 _158;
    /* 0x164 */ HitInfo mRoofInfo;
    /* 0x1E8 */ f32 _1E8;
    /* 0x1EC */ struct {
        u8 _0 : 1;
        u8 _1 : 1;
        u8 _2 : 1;
        u8 _3 : 1;
        u8 _4 : 1;
        u8 _5 : 1;
    } _1EC;
};
