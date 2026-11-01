#include "Game/Gravity/BarrelGravity.hpp"
#include "Game/Util/MathUtil.hpp"

BarrelGravity::BarrelGravity()
    : PlanetGravity(), mLocalPos(0.0f, 0.0f, 0.0f), _34(0.0f, 0.0f, 0.0f), mUpDir(0.0f, 1.0f, 0.0f), _4C(0.0f, 1.0f, 0.0f), mRadius(1000.0f),
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

void BarrelGravity::updateMtx(const TPos3f& rMtx) {
    rMtx.mult(mLocalPos, _34);
    rMtx.mult33(mUpDir, _4C);

    f32 scalar;
    MR::separateScalarAndDirection(&scalar, &_4C, _4C);

    _5C = mRadius * scalar;
}

bool BarrelGravity::calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPosition) const {
    TVec3f vec;
    vec = (rPosition - _34);
    f32 dot = vec.dot(_4C);

    if (dot <= 0.0f || dot >= _5C) {
        return false;
    }

    TVec3f vec2(_34 + _4C * dot);
    TVec3f direction;
    f32 scalar;
    MR::separateScalarAndDirection(&scalar, &direction, vec2 - rPosition);

    TVec3f destVec;
    if (MR::isNearZero(direction)) {
        // does not set pDest to anything, meaning this line of code does nothing
        MR::makeAxisVerticalZX(&destVec, _4C);
        return true;
    }

    destVec.cross(direction, _4C);
    MR::rotateVecRadian(&destVec, _4C, MR::clamp(mThreshold / scalar, 0.0f, MR::toRadian(45.0f)));
    MR::normalize(&destVec);
    if (!isInRangeDistance(scalar)) {
        return false;
    }

    *pScalar = scalar;
    pDest->set(destVec);
    return true;
}
