#include "Game/Gravity/PlanetGravity.hpp"
#include "Game/Util/MathUtil.hpp"

PlanetGravity::PlanetGravity()
    : mRange(-1.0f), mDistant(), mPriority(), mGravityId(-1), mHost(this), mGravityType(GRAVITY_TYPE_NORMAL), mGravityPower(GRAVITY_POWER_NORMAL),
      mActivated(true), mIsInverse(false), _22(false), mValidFollower(true), mIsRegistered(false), mAppeared(true) {
}

void PlanetGravity::setPriority(s32 priority) {
    mPriority = priority;
}

bool PlanetGravity::calcGravity(TVec3f* pDest, const TVec3f& rPos) const {
    f32 radius = 0.0f;
    TVec3f gravity(0.0f, 0.0f, 0.0f);

    if (!calcOwnGravityVector(&gravity, &radius, rPos)) {
        return false;
    }

    radius -= mDistant;

    if (radius < 1.0f) {
        radius = 1.0f;
    }

    gravity.scale(4000000.0f / (radius * radius));

    if (mIsInverse) {
        gravity = -gravity;
    }

    if (_22) {
        gravity.set< f32 >(0.0f, 0.0f, 0.0f);
    }

    pDest->set(gravity);

    return true;
}

bool PlanetGravity::calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPosition) const {
    return false;
}

bool PlanetGravity::isInRangeSquare(f32 radius) const {
    if (mRange < 0.0f) {
        return true;
    } else {
        f32 distance = mRange + mDistant;
        return radius < distance * distance;
    }
}

bool PlanetGravity::isInRangeDistance(f32 radius) const {
    if (mRange < 0.0f) {
        return true;
    } else {
        return radius < mRange + mDistant;
    }
}

bool PlanetGravity::calcGravityFromMassPosition(TVec3f* pGravity, f32* pDistance, const TVec3f& rPos, const TVec3f& rMassPos) const {
    TVec3f dir = rMassPos - rPos;
    f32 distance;

    MR::separateScalarAndDirection(&distance, &dir, dir);

    if (!isInRangeDistance(distance)) {
        return false;
    }

    if (pGravity != nullptr) {
        *pGravity = dir;
    }

    if (pDistance != nullptr) {
        *pDistance = distance;
    }

    return true;
}

void PlanetGravity::updateMtx(const TPos3f& rMtx) {
}

void PlanetGravity::updateIdentityMtx() {
    TPos3f mtx;
    mtx.identity();
    updateMtx(mtx);
}
