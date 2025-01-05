#pragma once

#include "LiveActor/ActorStateKeeper.hpp"

class Spine {
public:
    Spine(void *, const Nerve *, s32);

    void update();
    void setNerve(const Nerve *);
    const Nerve* getCurrentNerve() const;
    void changeNerve();

    void* mExecutor;                        // 0x00
    const Nerve* mCurrentNerve;             // 0x04
    const Nerve* mNextNerve;                // 0x08
    s32 mCurrentStep;                       // 0x0C
    ActorStateKeeper* mStateKeeper;         // 0x10
};
