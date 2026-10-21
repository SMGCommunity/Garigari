#include "Game/Gravity/ConeGravity.hpp"
#include "Game/Util/MathUtil.hpp"

ConeGravity::ConeGravity() : PlanetGravity(), mValidDegree(360.0f), mValidCos(-1.0f), mWorldRadius(), mEnableBottom(true), mTopCutRate() {
    mLocalMtx.identity();
    mWorldMtx.identity();
}

void ConeGravity::setLocalMatrix(const TPos3f& rMtx) {
    mLocalMtx.set(rMtx);
    updateIdentityMtx();
}

void ConeGravity::setEnableBottom(bool isBottom) {
    mEnableBottom = isBottom;
}

void ConeGravity::setTopCutRate(f32 rate) {
    mTopCutRate = rate < 0.0f ? 0.0f : rate > 1.0f ? 1.0f : rate;
}

void ConeGravity::updateMtx(const TPos3f& rMtx) {
    mWorldMtx.concat(rMtx, mLocalMtx);

    TVec3f xDir;
    mWorldMtx.getXDir(xDir);
    mWorldRadius = xDir.length();

    TVec3f yDir;
    mWorldMtx.getYDir(yDir);
}

bool ConeGravity::calcOwnGravityVector(TVec3f* pDest, f32* pScalar, const TVec3f& rPos) const {
    TVec3f worldBaseCenter, worldCentralAxis;
    mWorldMtx.getYDir(worldCentralAxis);
    mWorldMtx.getTrans(worldBaseCenter);

    TVec3f unitWorldCentralAxis;
    f32 centralAxisLength;
    MR::separateScalarAndDirection(&centralAxisLength, &unitWorldCentralAxis, worldCentralAxis);

    TVec3f relativePosition = rPos - worldBaseCenter;
    TVec3f positionOnBasePlane;
    positionOnBasePlane.killElement(relativePosition, unitWorldCentralAxis);

    if (MR::isNearZero(positionOnBasePlane)) {
        f32 positionOnCentralAxis = relativePosition.dot(unitWorldCentralAxis);
        f32 distance = MR::abs(positionOnCentralAxis);

        if (positionOnCentralAxis > 0.0f) {
            distance -= centralAxisLength * (1.0f - mTopCutRate);
            if (distance < 0.0f) {
                distance = 0.0f;
            }
        }

        if (!isInRangeDistance(distance)) {
            return false;
        }

        if (positionOnCentralAxis > 0.0f) {
            pDest->set(-unitWorldCentralAxis);
        } else {
            pDest->set(unitWorldCentralAxis);
        }

        *pScalar = distance;

        return true;
    }

    f32 distanceToCentralAxis = positionOnBasePlane.length();
    f32 centralAxisY = unitWorldCentralAxis.dot(relativePosition);

    bool isInsideCone = false;

    if (MR::isNearZero(centralAxisLength) || MR::isNearZero(mWorldRadius)) {
        // The cone is too small to have an inner region
        isInsideCone = false;
    } else if (distanceToCentralAxis < mWorldRadius - centralAxisY * (mWorldRadius / centralAxisLength)) {
        isInsideCone = true;
    }

    TVec3f pointOfAttraction;
    TVec3f dirOnDirectrix = worldBaseCenter + positionOnBasePlane * (mWorldRadius / distanceToCentralAxis);
    TVec3f apex = worldBaseCenter + worldCentralAxis;

    if (relativePosition.dot(worldCentralAxis) < 0.0f) {
        if (!mEnableBottom) {
            return false;
        }

        MR::calcPerpendicFootToLineInside(&pointOfAttraction, rPos, worldBaseCenter, dirOnDirectrix);

        if (MR::isNearZero(pointOfAttraction - rPos)) {
            *pDest = -unitWorldCentralAxis;
            *pScalar = 0.0f;

            return true;
        } else {
            return calcGravityFromMassPosition(pDest, pScalar, rPos, pointOfAttraction);
        }
    }

    if (mTopCutRate < 0.01f) {
        MR::calcPerpendicFootToLineInside(&pointOfAttraction, rPos, dirOnDirectrix, apex);
    } else {
        TVec3f generatrixTermination;
        generatrixTermination.set(apex * (1.0f - mTopCutRate) + dirOnDirectrix * mTopCutRate);

        TVec3f frustumBaseCenter;
        frustumBaseCenter.set(worldBaseCenter + worldCentralAxis * (1.0f - mTopCutRate));

        if ((rPos - generatrixTermination).dot(generatrixTermination - frustumBaseCenter) <= 0.0f) {
            // Attracted to the frustum
            f32 distanceToCentralAxis = unitWorldCentralAxis.dot(rPos - frustumBaseCenter);

            if (distanceToCentralAxis < 0.0f) {
                distanceToCentralAxis = 0.0f;
            }

            if (isInRangeDistance(distanceToCentralAxis)) {
                *pDest = -unitWorldCentralAxis;
                *pScalar = distanceToCentralAxis;

                return true;
            } else {
                return false;
            }
        }

        MR::calcPerpendicFootToLineInside(&pointOfAttraction, rPos, dirOnDirectrix, generatrixTermination);
    }

    if (MR::isNearZero(pointOfAttraction - rPos)) {
        TVec3f generatrixDirection = apex - dirOnDirectrix;
        MR::normalizeOrZero(&generatrixDirection);

        TVec3f gravity;
        gravity.killElement((-positionOnBasePlane), generatrixDirection);

        if (MR::isNearZero(gravity)) {
            *pDest = -unitWorldCentralAxis;
        } else {
            MR::normalize(pDest, gravity);
        }

        *pScalar = 0.0f;

        return true;
    }

    if (isInsideCone) {
        MR::normalize(pDest, rPos - pointOfAttraction);
        *pScalar = 0.0f;

        return true;
    }

    return calcGravityFromMassPosition(pDest, pScalar, rPos, pointOfAttraction);
}
