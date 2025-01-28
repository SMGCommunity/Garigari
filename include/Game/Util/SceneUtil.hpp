#pragma once

#include <JGeometry.hpp>
#include "Util.hpp"

namespace MR {
    const char* getCurrentStageName();

    bool isPlacementLocalStage();

    TPos3f& getZonePlacementMtx(const JMapInfoIter &);
};
