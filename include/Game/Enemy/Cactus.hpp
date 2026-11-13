#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class Cactus : public LiveActor {
public:
    Cactus(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void attackSensor(HitSensor*, HitSensor*);

    void exeWait();

    bool isNerveWait() const NO_INLINE;
};
