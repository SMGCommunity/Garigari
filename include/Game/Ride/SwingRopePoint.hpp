#pragma once

#include <JSystem/JGeometry/TVec.hpp>

/// @brief A control point used in multiple rope-like objects
class SwingRopePoint {
public:
    /// @brief Creates a new `SwingRopePoint`
    /// @param rPos The base position of the object
    SwingRopePoint(const TVec3f& rPos);

    virtual void updatePos(f32 friction);

    void addAccel(const TVec3f& rAccel);
    bool restrict(const TVec3f& rAnchor, f32 length, const TVec3f* pVel);
    void strain(const TVec3f& rAnchor, f32 length);
    void updateAxis(const TVec3f& rAxis);
    void updatePosAndAxis(const TVec3f& rAxis, f32 friction);
    void stop();
    void setInfo(const TVec3f& rTarget, const TVec3f& rVelocity, const TVec3f& rAnchor, f32 length);
    void setPosAndAxis(const TVec3f& rPos, const TVec3f& rSide, const TVec3f& rUp, const TVec3f& rFront);
    void setAndUpdatePosAndAxis(const TVec3f& rPos, const TVec3f& rUp, const TVec3f& rAxis);

    const TVec3f& getSide() const {
        return mSide;
    }

    const TVec3f& getUp() const {
        return mUp;
    }

    const TVec3f& getFront() const {
        return mFront;
    }

    const TVec3f& getPosition() const {
        return mPosition;
    }

    /* 0x04 */ TVec3f mPosition;
    /* 0x10 */ TVec3f mVelocity;
    /* 0x1C */ TVec3f mSide;
    /* 0x28 */ TVec3f mUp;
    /* 0x34 */ TVec3f mFront;
};
