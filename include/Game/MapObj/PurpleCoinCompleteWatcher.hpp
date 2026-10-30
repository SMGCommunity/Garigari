#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class PurpleCoinCompleteWatcher : public LiveActor {
public:
    PurpleCoinCompleteWatcher(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeComplete();
};
