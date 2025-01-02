#pragma once

#include "NameObj/NameObj.hpp"

class StageSwitchCtrl;

class SwitchSynchronizer : public NameObj {
public:
    SwitchSynchronizer(const char *);

    virtual ~SwitchSynchronizer();
    virtual void init(const JMapInfoIter &);
    virtual void movement();

    StageSwitchCtrl* mSwitchCtrl;           // 0x14
    bool _18;
};
