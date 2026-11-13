#pragma once

#include "Game/AreaObj/AreaObj.hpp"

class CancelBeeMorphArea : public AreaObj {
public:
    CancelBeeMorphArea(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void movement();
};