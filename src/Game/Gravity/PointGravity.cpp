#include "Game/Gravity/PointGravity.hpp"
#include "Game/Util/MathUtil.hpp"

PointGravity::PointGravity() : PlanetGravity(), mOrigPosition(0, 0, 0), mTranslation(0, 0, 0) {
}

bool PointGravity::calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPosition) const {
    TVec3f direction = mTranslation - rPosition;
    f32 distance = direction.length();

    // Epsilon-equals zero? If so, direction is the zero vector.
    if (MR::isNearZero(distance)) {
        direction.zero();
    }
    // Otherwise, it's a proper direction and it should be normalized.
    else {
        direction /= distance;
    }

    // Out of range? If so, don't update result vector & scalar
    if (!isInRangeDistance(distance)) {
        return false;
    }

    // Update result vector & scalar if applicable
    if (pDest != nullptr) {
        *pDest = direction;
    }

    if (pScalar != nullptr) {
        *pScalar = distance;
    }

    return true;
}

void PointGravity::updateMtx(const TPos3f& rMtx) {
    // Converts relative zone-coordinates into worldspace
    // mTranslation = rMtx * mOrigPosition
    rMtx.mult(mOrigPosition, mTranslation);
}
