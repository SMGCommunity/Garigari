#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class LiveActor;

namespace MR {
    void initStarPointerTarget(LiveActor*, f32, const TVec3f&);

    void initStarPointerTargetAtJoint(LiveActor*, const char*, f32, const TVec3f&);
    f32 calcPointRadius2D(const TVec3f&, f32);
};  // namespace MR
