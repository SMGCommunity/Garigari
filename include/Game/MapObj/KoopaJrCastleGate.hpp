#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class KoopaJrCastleGate : public LiveActor {
public:
    KoopaJrCastleGate(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeMove();
    void exeMoveFast();
    void exeWaitEnd();
};
