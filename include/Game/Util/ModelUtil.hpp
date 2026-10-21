#pragma once

#include "JSystem/J3DGraphAnimator/J3DModel.hpp"
class LiveActor;

namespace MR {
    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
    J3DModel* getJ3DModel(const LiveActor*);
    J3DModelData* getJ3DModelData(const char*);
};  // namespace MR
