#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class MarioFacePlanet : public LiveActor {
public:
    MarioFacePlanet(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void listenDemoAction();

    void exeWait();
};
