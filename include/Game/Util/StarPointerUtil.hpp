#pragma once

#include <JGeometry.hpp>

class LiveActor;

namespace MR {
    void initStarPointerTarget(LiveActor *, f32, const TVec3f &);
    
    void initStarPointerTargetAtJoint(LiveActor *, const char *, f32, const TVec3f &);
};
