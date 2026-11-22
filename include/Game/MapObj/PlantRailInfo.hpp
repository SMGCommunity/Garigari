#pragma once

#include "Game/Util/JMapInfo.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/types.h>

class PlantPoint;
class RailRider;

class PlantRailInfo {
public:
    /// @brief Creates a new `PlantRailInfo`
    /// @param rIter Reference to the JMapInfo iterator for this object
    /// @param speed Rail speed for this plant rail
    PlantRailInfo(const JMapInfoIter& rIter, f32 speed);

    void calcPosAndAxisY(TVec3f* pPos, TVec3f* pAxisY, f32 coord) const;
    void calcNearestPointPos(TVec3f* pPointPos, const TVec3f& rPos, s32 cutoff) const;

    const RailRider* getRailRider() const {
        return mRailRider;
    }

    inline PlantPoint* getPlantPoint(s32 idx) {
        return mPlantPoints[idx];
    }

    /* 0x00 */ s32 mPlantPointNum;
    /* 0x04 */ PlantPoint** mPlantPoints;
    /* 0x08 */ RailRider* mRailRider;
    /* 0x0C */ f32 mRailSpeed;
};
