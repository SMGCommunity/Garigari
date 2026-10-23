#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;
class ClippingActorHolder;

class ClippingDirector : public NameObj {
public:
    ClippingDirector();

    void joinToGroupClipping(LiveActor*, const JMapInfoIter&, int);

    ClippingActorHolder* mActorHolder;
};

namespace MR {
    ClippingDirector* getClippingDirector();
    void addToClippingTarget(LiveActor*);
    void removeFromClippingTarget(LiveActor*);
};  // namespace MR
