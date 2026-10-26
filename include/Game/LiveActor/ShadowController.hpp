#pragma once

#include <revolution/types.h>

class ShadowController;
class LiveActor;

class ShadowControllerList {
public:
    ShadowControllerList(LiveActor*, u32);
};

namespace MR {
    void addShadowController(ShadowController*);
    void requestCalcActorShadowAppear(LiveActor*);
    void requestCalcActorShadow(LiveActor*);
}
