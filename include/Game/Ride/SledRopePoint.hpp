#pragma once

#include "Game/Ride/SwingRopePoint.hpp"

class Binder;

/// @brief A variant of the `SwingRopePoint` that can interact with the collision map
class SledRopePoint : public SwingRopePoint {
public:
    /// @brief Creates a new `SledRopePoint`
    /// @param rPos The base position of the object
    /// @param bindRadius The radius of the collision binder
    SledRopePoint(const TVec3f& rPos, f32 bindRadius);

    virtual void updatePos(f32 friction);

    bool bindToMapCollision(f32 rebound);

    /* 0x40 */ Binder* mBinder;
    /* 0x44 */ bool mNoBind;
};
