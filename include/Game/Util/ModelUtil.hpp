#pragma once

class J3DModel;
class LiveActor;

namespace MR {
    J3DModel* getJ3DModel(const LiveActor*);

    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
};  // namespace MR
