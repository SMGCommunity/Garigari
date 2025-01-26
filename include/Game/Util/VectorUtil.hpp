#pragma once

#include <JGeometry.hpp>
#include <cmath>

namespace MR {
    inline void normalizeVec(TVec3f *pVector, f32 rotation) __attribute__((always_inline)) {
        pVector->x = rotation + (float)fmod((360.0f + (pVector->x - rotation)), 360.0);
        pVector->y = rotation + (float)fmod((360.0f + (pVector->y - rotation)), 360.0);
        pVector->z = rotation + (float)fmod((360.0f + (pVector->z - rotation)), 360.0);
    }
};
