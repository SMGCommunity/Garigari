#pragma once

class ShadowController;
class LiveActor;

namespace MR {
    void addShadowController(ShadowController*);
    void requestCalcActorShadowAppear(LiveActor*);
    void requestCalcActorShadow(LiveActor*);
}
