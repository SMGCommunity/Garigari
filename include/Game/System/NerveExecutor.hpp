#pragma once

#include <revolution.h>

class Spine;
class Nerve;

class NerveExecutor {
public:
    NerveExecutor(const char*);

    virtual ~NerveExecutor();

    void initNerve(const Nerve* pNerve, s32 numStates = 0);
    void updateNerve();
    void setNerve(const Nerve* pNerve);
    bool isNerve(const Nerve* pNerve) const;
    s32 getNerveStep() const;

    /* 0x04 */ Spine* mSpine;
};
