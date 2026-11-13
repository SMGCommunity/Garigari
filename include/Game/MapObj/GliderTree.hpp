#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class GliderTree : public LiveActor {
public:
    GliderTree(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeWait();
    void exeSwing();
};
