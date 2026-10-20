#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>

class TriangleFilterBase;
class CollisionPartsFilterBase;
class HitInfo;


class Binder {
public:
    void setTriangleFilter(TriangleFilterBase*);
    void setCollisionPartsFilter(CollisionPartsFilterBase*);
    void clear();
    void getPlane(int) const;
    void compSensor(const HitInfo*, const HitInfo*);
    void bind(const TVec3f&);
    void moveAlongHittedPlanes(TVec3f*, TVec3f*, TVec3f*, const TVec3f&, const TVec3f&, HitInfo*, u32, bool*);
    void findBindedPos(TVec3f*, TVec3f*, bool*, HitInfo*, u32, bool, bool);
    void moveWithCollisionParts(TVec3f*, TVec3f*);
    void storeCurrentHintInfo(HitInfo*, u32, bool);
    void obtainMomentFixReaction(HitInfo*, u32, TVec3f*, u32);
    void storeContactPlane(HitInfo*, u32);

    u8 _0[0x18];
    f32 mRadius;  // 0x18
    f32 mOffsetY;
    /* todo */
};
