#pragma once

#include "Game/Ride/SphereController.hpp"

/// @brief A `SphereController` that uses the Pad Stick for control
class SpherePadController : public SphereController {
public:
    /// @brief Creates a new `SpherePadController`.
    SpherePadController();

    virtual f32 calcMoveVector(TVec3f* pMoveDir, const TVec3f& rGravity);
    virtual f32 calcJumpPower() const;
    virtual void update(const TVec3f& rSrc);
    virtual void clacXY(f32* pX, f32* pY);

    f32 calcDirSphereMove(TVec3f* pMoveDir, const TVec3f& rBaseVec, u32 isFrontVec);
};
