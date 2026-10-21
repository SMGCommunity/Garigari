#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class MirrorCamera : public NameObj {
public:
    MirrorCamera(const char*);

    void setMirrorMapInfo(const TVec3f&, const TVec3f&);
};

namespace MR {
    MirrorCamera* getMirrorCamera();
};  // namespace MR
