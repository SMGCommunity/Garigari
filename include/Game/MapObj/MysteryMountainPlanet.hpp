#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class MysteryMountainPlanet : public LiveActor {
public:
    MysteryMountainPlanet(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeBoxVanish();
    void exeCakeVanish();
    void exeWaitVanished();
};
