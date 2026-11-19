#pragma once

#include <JSystem/JGeometry/TVec.hpp>

/// @brief A control point for multi-segmented Plant objects
class PlantPoint {
public:
    /// @brief Creates a new `PlantPoint`
    /// @param rPosition Base position for this point
    /// @param rUp Up basis vector for this point
    /// @param thickness Thickness of the plant at this point
    /// @param rSide Side basis vector for this point
    PlantPoint(const TVec3f& rPosition, const TVec3f& rUp, f32 thickness, const TVec3f& rSide);

    virtual void setAxisAndPos(const TVec3f& pSide, const TVec3f& pUp, const TVec3f& pFront, const TVec3f& pPosition);

    const TVec3f& getUpVec() const {
        return mUp;
    }

    /* 0x04 */ TVec3f mPosition;
    /* 0x10 */ TVec3f mSide;
    /* 0x1C */ TVec3f mUp;
    /* 0x28 */ TVec3f mFront;
    /* 0x34 */ f32 mThickness;
};
