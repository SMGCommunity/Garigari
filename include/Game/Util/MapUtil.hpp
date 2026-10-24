#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class CollisionPartsFilterBase;
class HitInfo;
class HitSensor;
class JMapInfoIter;
class LiveActor;
class Triangle;
class TriangleFilterBase;

namespace MR {
    bool trySetMoveLimitCollision(LiveActor*);
    bool isExistMapCollision(const TVec3f&, const TVec3f&);
}; // namespace MR
