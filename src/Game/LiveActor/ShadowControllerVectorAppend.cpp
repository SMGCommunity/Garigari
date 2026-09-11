#include "LiveActor/ShadowControllerList.hpp"

void MR::Vector<MR::AssignableArray<ShadowController*> >::push_back(ShadowController* const& controller) {
    const s32 index = count++;
    array[index] = controller;
}
