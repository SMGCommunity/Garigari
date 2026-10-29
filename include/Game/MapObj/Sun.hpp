#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class Sun : LiveActor {
public:
    Sun(const char*);

    ~Sun();

    void init(const JMapInfoIter&);
};
