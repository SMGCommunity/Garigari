#pragma once

#include "NameObj/NameObj.hpp"

class NameObjGroup;

class MovementOnOffGroupHolder : public NameObj {
public:
    MovementOnOffGroupHolder(const char *);
    
    virtual ~MovementOnOffGroupHolder();

    NameObjGroup* mGroups[0x20];    // 0x14
    s32 mCount;                     // 0x94
};
