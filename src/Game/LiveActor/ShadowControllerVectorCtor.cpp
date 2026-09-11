#include "LiveActor/ShadowControllerList.hpp"

MR::Vector<MR::AssignableArray<ShadowController*> >::Vector()
    : array(nullptr), capacity(0), count(0) {}
