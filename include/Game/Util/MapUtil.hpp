#pragma once

#include <JSystem/JGeometry/TVec.hpp>

namespace MR {};  // namespace MR
class CollisionPartsFilterBase;
class HitInfo;
class HitSensor;
class JMapInfoIter;
class LiveActor;
class Triangle;
class TriangleFilterBase;

namespace MR {
    bool isWallPolygon(const TVec3f&, const TVec3f&);
    bool isFloorPolygon(const TVec3f&, const TVec3f&);
    bool isFloorPolygonCos(const TVec3f&, const TVec3f&, f32);
    bool trySetMoveLimitCollision(LiveActor*);
    bool isExistMapCollision(const TVec3f&, const TVec3f&);
};  // namespace MR
