#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/types.h>

class LiveActor;

namespace SpinDriverUtil {
    void setShadowAndClipping(LiveActor*, TVec3f*, f32, f32, f32*);
};  // namespace SpinDriverUtil
