#pragma once

#include "Game/System/NerveExecutor.hpp"
#include <revolution/types.h>

class GameSystemDataHolder;
class GameSystemObjHolder;

class GameSystem : public NerveExecutor {
public:
    /* 0x08 */ u32 _8;  // unknown type
    /* 0x0C */ u32 _C;  // unknown type
    /* 0x10 */ u32 _10; // unknown type
    /* 0x14 */ u32 _14; // unknown type
    /* 0x18 */ u32 _18; // unknown type
    /* 0x1C */ u32 _1C; // unknown type
    /* 0x20 */ GameSystemObjHolder* mObjHolder;
    /* 0x24 */ u32 _24; // unknown type
    /* 0x28 */ u32 _28; // unknown type
    /* 0x2C */ u32 _2C; // unknown type
    /* 0x30 */ u32 _30; // unknown type
    /* 0x34 */ GameSystemDataHolder* mDataHolder;
    /* 0x38 */ u8 _38;  // unknown type
};
