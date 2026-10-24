#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class LiveActor;

namespace MR {
    MtxPtr getJointMtx(const LiveActor*, const char*);
    void copyJointPos(const LiveActor*, const char*, TVec3f*);
};
