#pragma once

#include <JGeometry.hpp>
#include "Util.hpp"
#include "Util/JMapInfo.hpp"

namespace MR {
    const char* getCurrentStageName();

    bool isPlacementLocalStage();

    TPos3f& getZonePlacementMtx(const JMapInfoIter &);

    void getCameraRailInfo(JMapInfoIter *, const JMapInfo **, s32, s32);

    void getRailInfo(JMapInfoIter *, const JMapInfo **, const JMapInfoIter &);
};
