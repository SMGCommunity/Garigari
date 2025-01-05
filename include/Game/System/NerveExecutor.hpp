#pragma once

#include <revolution.h>

class Spine;
class Nerve;

class NerveExecutor {
public:
    NerveExecutor(const char *);

    virtual ~NerveExecutor();

    void initNerve(const Nerve *, s32);
    void updateNerve();
    void setNerve(const Nerve *);
    bool isNerve(const Nerve *) const;
    s32 getNerveStep() const;

    Spine* mSpine;          // 0x04
};
