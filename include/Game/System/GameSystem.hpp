#pragma once
#include "System/NerveExecutor.hpp"

class GameSystemObjHolder;

// Partial layout; the object-holder offset is confirmed by Galaxy 2 code.
// Field identification is aided by Petari's CC0 GameSystem declarations.
class GameSystem : public NerveExecutor {
public:
    u8 _8[0x18];
    GameSystemObjHolder* mObjHolder; // 0x20
};
