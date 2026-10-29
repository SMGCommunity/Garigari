#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class RockReflector : public LiveActor {
public:
    RockReflector(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    bool canReflect() const NO_INLINE;

    void exeWait();
    void exeReflect();
};
