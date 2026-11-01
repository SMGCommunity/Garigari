#pragma once

#include <revolution/types.h>

class J3DModel;
class J3DModelData;
class LiveActor;

namespace MR {
    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
    J3DModel* getJ3DModel(const LiveActor*);
    J3DModelData* getJ3DModelData(const char*);
    void hideMaterial(const LiveActor*, const char*);

    void calcModelBoundingRadius(f32*, const LiveActor*);
};  // namespace MR
