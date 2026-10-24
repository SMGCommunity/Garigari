#pragma once

#include <revolution/types.h>

class LiveActor;

namespace MR {
    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
    void hideMaterial(const LiveActor*, const char*);
    
    void calcModelBoundingRadius(f32*, const LiveActor*);
};  // namespace MR
