#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class MiniComet : public LiveActor {
public:
    MiniComet(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void appear();

    void exeDemo();

    /* 0x90 */ const char* mName;
};
