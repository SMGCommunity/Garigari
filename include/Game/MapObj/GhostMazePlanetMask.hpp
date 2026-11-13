#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class GhostMazePlanetMask : public LiveActor {
public:
    GhostMazePlanetMask(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeAppear();
    void exeDisappear();
};
