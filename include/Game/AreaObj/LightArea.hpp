#pragma once

#include "Game/AreaObj/AreaObj.hpp"

class LightArea : public AreaObj {
public:
    LightArea(const char*);

    virtual void init(const JMapInfoIter&);

    virtual const char* getManagerName() const {
        return "LightArea";
    }

    /* 0x48 */ bool _48;
};
