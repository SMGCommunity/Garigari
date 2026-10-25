#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class MiniGreenComet : public LiveActor {
public:
    MiniGreenComet();

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual void control();
};

class MiniGreenCometShower : public LiveActor {
public:
    MiniGreenCometShower();

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
};
