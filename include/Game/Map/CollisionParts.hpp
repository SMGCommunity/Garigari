#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <JSystem/JGeometry/TMatrix.hpp>
#include <revolution.h>

class HitSensor;

class CollisionParts : TRot3f {
public:
    CollisionParts();

    // Return types unkown for these functions; guessing for now
    void fn_8024A060(); // Parameter(s) unknown; leaving empty for now
    void init(const TPos3f&, HitSensor*, const void*, const void*, long, bool);
    void getScale(TVec3f&) override;
    void addToBelongZone();
    void removeFromBelongZone();
    void initWithAutoEqualScale(TPos3f&, HitSensor*, const void*, const void*, long, bool);
    void initWithNotUsingScale(TPos3f&, HitSensor*, const void*, const void*, long, bool);
    void resetAllMtx(TPos3f&);
    void resetAllMtx();
    void resetAllMtxPrivate(TPos3f&);
    void setMtx(const TPos3f&);
    void setMtx();
    void updateMtx();
    void makeEqualScale(MtxPtr);
    void updateBoundingSphereRange();
    void updateBoundingSphereRange(TVec3f);
    void updateBoundingSphereRangePrivate(float);
    char* getHostName() const;
    u32 getPlacementZoneID() const;
};
