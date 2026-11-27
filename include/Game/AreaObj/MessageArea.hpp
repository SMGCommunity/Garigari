#pragma once

#include "Game/AreaObj/AreaObj.hpp"

class MessageArea : public AreaObj {
public:
    MessageArea(const char*);

    virtual void init(const JMapInfoIter&);

    /* 0x48 */ s32 mZoneID;
};
