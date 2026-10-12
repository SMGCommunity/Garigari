#pragma once

#include "Game/LiveActor/ActorStateKeeper.hpp"
#include "Game/System/NerveExecutor.hpp"

class ActorStateBaseInterface : public NerveExecutor {
public:
    inline ActorStateBaseInterface(const char* pName, bool isDead) : NerveExecutor(pName), mIsDead(isDead) {
    }

    virtual ~ActorStateBaseInterface();
    virtual void init();
    virtual void appear();
    virtual void kill();
    virtual bool update();
    virtual void control();

    bool mIsDead;  // 0x8
};
