#pragma once
#include "LiveActor/ShadowControllerList.hpp"

// Retail holder storage; only accessed fields are exposed.
struct ShadowHolderView {
    const void* _0;
    u8 _4[0x10];
    MR::Vector<MR::AssignableArray<ShadowController*> > registered;
    MR::Vector<MR::AssignableArray<ShadowController*> > pending;
    f32 distance;
    f32 defaultDistance;
    u8 enabled;
    u8 defaultEnabled;
};
