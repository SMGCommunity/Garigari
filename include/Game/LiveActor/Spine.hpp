#pragma once

#include <revolution.h>

class Nerve;
class ActorStateKeeper;

class Spine {
public:
    Spine(void* pExecutor, const Nerve* pNerve, s32 numStates = 0);

    void update();
    void setNerve(const Nerve*);
    const Nerve* getCurrentNerve() const;
    void changeNerve();

    bool isCurrentNerve(const Nerve* pNerve) const {
        return getCurrentNerve() == pNerve;
    }

    /* 0x00 */ void* mExecutor;
    /* 0x04 */ const Nerve* mCurrNerve;
    /* 0x08 */ const Nerve* mNextNerve;
    /* 0x0C */ s32 mStep;
    /* 0x10 */ ActorStateKeeper* mStateKeeper;
};
