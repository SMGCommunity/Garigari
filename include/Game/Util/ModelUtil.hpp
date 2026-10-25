#pragma once

#include <revolution/types.h>

class J3DModel;
class LiveActor;

namespace MR {
    J3DModel* getJ3DModel(const LiveActor*);
    void calcJ3DModel(LiveActor *pActor);

    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
    void hideMaterial(const LiveActor*, const char*);
    
    void calcModelBoundingRadius(f32*, const LiveActor*);
};  // namespace MR
