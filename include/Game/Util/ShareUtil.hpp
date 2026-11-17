#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <revolution/types.h>

class ResourceShare : public NameObj {
public:
    ResourceShare();

    /* 0x14 */ u8* _14;
    /* 0x18 */ u8* _18;
    /* 0x1C */ u32 _1C;
};
