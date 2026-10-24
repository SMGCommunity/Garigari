#include "Game/Gravity/ParallelGravity.hpp"
#include "Game/Util/MathUtil.hpp"

ParallelGravity::ParallelGravity()
    : PlanetGravity(), mPlanePosition(0, 0, 0), mPlaneUpVec(0.0f, 1.0f, 0.0f), mWorldPlanePosition(0, 0, 0), mWorldPlaneUpVec(0.0f, 1.0f, 0.0f),
      mCylinderHeight(1000.0f), mCylinderRadius(500.0f), mBaseDistance(2000.0f), mRangeType(RangeType_Sphere),
      mDistanceCalcType(DistanceCalcType_Default) {
    mLocalMtx.identity();
    mWorldMtx.identity();
}

bool ParallelGravity::calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPosition) const {
    if (!isInRange(rPosition, pScalar)) {
        return false;
    }

    if (pDest != nullptr) {
        // FIXME: needs to not inline
        *pDest = -mWorldPlaneUpVec;
    }

    return true;
}

void ParallelGravity::updateMtx(const TPos3f& rMtx) {
    rMtx.mult33(mPlaneUpVec, mWorldPlaneUpVec);
    rMtx.mult(mPlanePosition, mWorldPlanePosition);
    MR::normalizeOrZero(&mWorldPlaneUpVec);

    if (mRangeType == RangeType_Box) {
        mWorldMtx.concat(rMtx, mLocalMtx);

        TVec3f tempDir;
        mWorldMtx.getXDir(tempDir);
        mExtentX = tempDir.squared();
        mWorldMtx.getYDir(tempDir);
        mExtentY = tempDir.squared();
        mWorldMtx.getZDir(tempDir);
        mExtentZ = tempDir.squared();
    }
}

void ParallelGravity::setPlane(const TVec3f& rPlaneUp, const TVec3f& rPlanePos) {
    mPlaneUpVec.normalize(rPlaneUp);
    mPlanePosition = rPlanePos;
}

void ParallelGravity::setRangeBox(const TPos3f& rMtx) {
    mLocalMtx = rMtx;
    updateIdentityMtx();
}

void ParallelGravity::setRangeCylinder(f32 radius, f32 height) {
    mCylinderRadius = radius;
    mCylinderHeight = height;
}

void ParallelGravity::setRangeType(RANGE_TYPE rangeType) {
    mRangeType = rangeType;
}

void ParallelGravity::setBaseDistance(f32 distance) {
    if (distance < 0.0f) {
        mBaseDistance = 2000.0f;
    } else {
        mBaseDistance = distance;
    }
}

void ParallelGravity::setDistanceCalcType(DISTANCE_CALC_TYPE distanceCalcType) {
    mDistanceCalcType = distanceCalcType;
}

bool ParallelGravity::isInSphereRange(const TVec3f& rPosition, f32* pScalar) const {
    if (pScalar != nullptr) {
        *pScalar = mBaseDistance;
    }

    if (mRange < 0.0f) {
        return true;
    }

    TVec3f dirToCenter(mWorldPlanePosition - rPosition);
    f32 range = mRange;
    return dirToCenter.squared() < range * range;
}

bool ParallelGravity::isInBoxRange(const TVec3f& rPosition, f32* pScalar) const {
    TVec3f translation;
    mWorldMtx.getTrans(translation);
    TVec3f dirToCenter(rPosition - translation);

    TVec3f xDir;
    mWorldMtx.getXDir(xDir);
    f32 xDot = dirToCenter.dot(xDir);

    if (xDot < -mExtentX || mExtentX < xDot) {
        return false;
    }

    TVec3f yDir;
    mWorldMtx.getYDir(yDir);
    f32 yDot = dirToCenter.dot(yDir);

    if (yDot < -mExtentY || mExtentY < yDot) {
        return false;
    }

    TVec3f zDir;
    mWorldMtx.getZDir(zDir);
    f32 zDot = dirToCenter.dot(zDir);

    if (zDot < -mExtentZ || mExtentZ < zDot) {
        return false;
    }

    if (pScalar != nullptr) {
        switch (mDistanceCalcType) {
        case DistanceCalcType_X:
            *pScalar = mBaseDistance + MR::abs(xDot) / MR::sqrt(mExtentX);
            break;
        case DistanceCalcType_Y:
            *pScalar = mBaseDistance + MR::abs(yDot) / MR::sqrt(mExtentY);
            break;
        case DistanceCalcType_Z:
            *pScalar = mBaseDistance + MR::abs(zDot) / MR::sqrt(mExtentZ);
            break;
        case DistanceCalcType_Default:
            *pScalar = mBaseDistance;
            break;
        }
    }

    return true;
}

bool ParallelGravity::isInCylinderRange(const TVec3f& rPosition, f32* pScalar) const {
    f32 height = mWorldPlaneUpVec.dot(rPosition - mWorldPlanePosition);

    if (height < 0.0f || mCylinderHeight < height) {
        return false;
    }

    TVec3f positionOnWorldPlane;
    positionOnWorldPlane.killElement2(rPosition - mWorldPlanePosition, mWorldPlaneUpVec);

    f32 radius = positionOnWorldPlane.length();
    
    if (radius > mCylinderRadius) {
        return false;
    }

    *pScalar = mBaseDistance + radius;

    return true;
}

bool ParallelGravity::isInRange(const TVec3f& rPosition, f32* pScalar) const {
    switch (mRangeType) {
    case RangeType_Sphere:
        return isInSphereRange(rPosition, pScalar);
    case RangeType_Box:
        return isInBoxRange(rPosition, pScalar);
    case RangeType_Cylinder:
        return isInCylinderRange(rPosition, pScalar);
    }

    return false;
}
