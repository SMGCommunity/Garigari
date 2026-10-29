#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;
class ClippingActorHolder;

class ClippingDirector : public NameObj {
public:
    ClippingDirector();

    void joinToGroupClipping(LiveActor*, const JMapInfoIter&, int);

    /* 0x14 */ u8 _14[0x4];
    /* 0x18 */ ClippingActorHolder* mActorHolder;
};

namespace MR {
    ClippingDirector* getClippingDirector();
    void addToClippingTarget(LiveActor*);
    void removeFromClippingTarget(LiveActor*);
};  // namespace MR
