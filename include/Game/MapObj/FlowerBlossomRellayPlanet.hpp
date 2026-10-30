#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class FlowerBlossomRellayPlanet : public LiveActor {
public:
    FlowerBlossomRellayPlanet(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeBloomStart();
    void exeBloomEnd();
};
