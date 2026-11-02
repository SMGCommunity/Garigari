#pragma once

#include "Game/AreaObj/AreaObj.hpp"

class BgmChangeArea : public AreaObj {
public:
    BgmChangeArea(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void movement();

    s32 getFadeTime() const;

    bool _48;
};