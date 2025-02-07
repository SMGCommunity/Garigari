#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

static Vec gZeroVec;

namespace MR {
    void sortSmall(s32, u32 *, s32 *);

    void initAcosTable();

    bool isNearZero(f32, f32);
    bool isNearZero(const TVec3f &, f32);
};
