#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;
class ClippingActorHolder;

class ClippingDirector : public NameObj {
public:
    ClippingDirector();

    void joinToGroupClipping(LiveActor*, const JMapInfoIter&, int);

    u8 _0[0x4];
    /* 0x04 */ ClippingActorHolder* mActorHolder;
};

namespace MR {
    ClippingDirector* getClippingDirector();
    void addToClippingTarget(LiveActor*);
    void removeFromClippingTarget(LiveActor*);
};  // namespace MR
