#include "Game/Gravity/BarrelGravity.hpp"

BarrelGravity::BarrelGravity()
    : PlanetGravity(), mLocalPos(0.0f, 0.0f, 0.0f), _34(0.0f, 0.0f, 0.0f), mUpDir(0.0f, 1.0f, 0.0f), _4C(), _50(1.0f), _54(), mRadius(1000.0f),
      _5C(1000.0f), _60(500.0f), mThreshold(1.0f) {
}

void BarrelGravity::setLocalPosition(const TVec3f& rPosition) {
    mLocalPos.set(rPosition);
}

void BarrelGravity::setUpDirection(const TVec3f& rDirection) {
    mUpDir.set(rDirection);
}

void BarrelGravity::setRadius(f32 radius) {
    mRadius = radius;
}

void BarrelGravity::setUnusedArg0(f32 arg0) {
    _60 = arg0;
}

void BarrelGravity::setInwardsThreshold(f32 threshold) {
    mThreshold = threshold;
}
