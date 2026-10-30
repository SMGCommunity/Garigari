#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class WhiteSnowTree : public LiveActor {
    WhiteSnowTree(const char*);

    virtual void init(const JMapInfoIter& rIter);
};
