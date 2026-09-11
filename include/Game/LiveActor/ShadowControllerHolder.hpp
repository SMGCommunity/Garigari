#pragma once
#include "LiveActor/ShadowControllerList.hpp"
#include "NameObj/NameObj.hpp"

// Native construction interface, recovered from the target NameObj vtable and
// field accesses. Existing holder routines retain their address-based ABI labels.
class ShadowControllerHolder : public NameObj {
public:
    ShadowControllerHolder();
    virtual ~ShadowControllerHolder();
    virtual void initAfterPlacement();
    virtual void movement();
    MR::Vector<MR::AssignableArray<ShadowController*> > registered;
    MR::Vector<MR::AssignableArray<ShadowController*> > pending;
    f32 distance, defaultDistance;
    u8 enabled, defaultEnabled;
};
