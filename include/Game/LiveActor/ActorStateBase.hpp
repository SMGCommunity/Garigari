#pragma once

#include "LiveActor/ActorStateKeeper.hpp"
#include "System/NerveExecutor.hpp"

class ActorStateBaseInterface : public NerveExecutor {
public:
    inline ActorStateBaseInterface(const char *pName) : NerveExecutor(pName) {

    }

    virtual ~ActorStateBaseInterface();
    virtual void init();
    virtual void appear();
    virtual void kill();
    virtual bool update();
    virtual void control();

    bool mIsDead; // 0x8
};
