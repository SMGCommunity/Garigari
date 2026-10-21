#pragma once

#include <JSystem/JGeometry/TVec.hpp>

namespace MR {
    bool isFloorPolygon(const TVec3f&, const TVec3f&);
    bool isFloorPolygonCos(const TVec3f&, const TVec3f&, f32);
};  // namespace MR
