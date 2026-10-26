#pragma once

#include "Game/Util/Array.hpp"
#include <revolution/types.h>

class ShadowController;
class LiveActor;

class ShadowControllerList {
public:
    ShadowControllerList(LiveActor*, u32);

    /* 0x00 */ MR::Vector< MR::AssignableArray< ShadowController* > > mShadowList;
    /* 0x0C */ LiveActor* mHost;
};

namespace MR {
    void addShadowController(ShadowController*);
    void requestCalcActorShadowAppear(LiveActor*);
    void requestCalcActorShadow(LiveActor*);
}
