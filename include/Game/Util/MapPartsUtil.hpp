#pragma once

#include <revolution/types.h>

class JMapInfoIter;
class LiveActor;

namespace MR {
    s32 getMapPartsArgShadowType(s32*, const JMapInfoIter&);
    bool getMapPartsArgRailGuideType(s32*, const LiveActor*);
    bool hasMapPartsShadow(s32);
};  // namespace MR
