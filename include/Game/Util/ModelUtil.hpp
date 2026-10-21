#pragma once

class LiveActor;

namespace MR {
    void syncJointAnimation(LiveActor*, const LiveActor*);

    void syncMaterialAnimation(LiveActor*, const LiveActor*);
    void hideMaterial(const LiveActor*, const char*);
};  // namespace MR
