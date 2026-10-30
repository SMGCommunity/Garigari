#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class VsOtaRockTankIcePlanetFence : public LiveActor {
    VsOtaRockTankIcePlanetFence(const char*);

    virtual void init(const JMapInfoIter& rIter);
};
