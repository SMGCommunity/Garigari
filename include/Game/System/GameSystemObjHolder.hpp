#pragma once
#include <revolution.h>

// Partial Galaxy 2 layout. The random state offset is verified in fn_8003B3F0.
class GameSystemObjHolder {
public:
    u8 _0[0x34];
    u32 mRandomSeed;
};
