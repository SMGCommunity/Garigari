#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class ClippingActorInfo;
class LiveActor;

class ClippingActorHolder : public NameObj {
public:
    /// @brief Creates a new `ClippingActorHolder`.
    ClippingActorHolder();

    void invalidateClipping(LiveActor*);
    void validateClipping(LiveActor*);
    void setTypeToSphere(LiveActor*, f32, const JGeometry::TVec3<float>*);
    void setFarClipLevel(LiveActor*, s32);
    ClippingActorInfo* find(const LiveActor*) const;
};
