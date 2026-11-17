#pragma once

#include <revolution/types.h>

class GalaxyMoveArgument;
class UserFile;

namespace GameSequenceFunction {
    void collectTicoCoinInStage();
    void collectTicoCoinIfSaved();
    bool isCollectTicoCoinInStage();
    bool isCollectTicoCoinSaved();
    bool isPadMode2();
};  // namespace GameSequenceFunction
