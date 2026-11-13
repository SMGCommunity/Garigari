#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;
class Nerve;
class Spine;

class MapPartsFunction : public NameObj {
public:
    MapPartsFunction(LiveActor* pHost, const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    virtual void movement();

    virtual bool isWorking() const;

    virtual void start();

    virtual void end() {
    }

    virtual bool receiveMsg(u32 msg) NO_INLINE {
        return false;
    }

    virtual void control() {
    }


    void resetHostSensorName();
    bool sendMsgToHost(u32 msg);
    void initNerve(const Nerve* pNerve);
    void setNerve(const Nerve* pNerve);
    s32 getStep() const;
    bool isStep(s32 step) const;
    bool isNerve(const Nerve* pNerve) const;
    bool isFirstStep() const;
    f32 getSpeed() const;

    /* 0x14 */ Spine* mSpine;
    /* 0x18 */ LiveActor* mHost;
    /* 0x1C */ bool mIsActive;
    /* 0x20 */ f32 mSpeed;
    /* 0x24 */ const char* mHostSensorName;
};
