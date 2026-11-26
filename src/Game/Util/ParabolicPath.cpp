#include "Game/Util/ParabolicPath.hpp"
#include "Game/Util/MathUtil.hpp"

ParabolicPath::ParabolicPath() : mPosition(0, 0, 0), mAxisY(0, 1, 0), mAxisZ(0, 0, 1), mAccel(), mVelocity(), mScalar() {
}

void ParabolicPath::initFromMaxHeight(const TVec3f& rStart, const TVec3f& rEnd, const TVec3f& rUp) {
    TVec3f direction;
    f32 scalar;
    MR::separateScalarAndDirection(&scalar, &direction, rUp - rEnd);
    initFromUpVector(rStart, rEnd, direction, direction.dot(rUp - rStart));
}

void ParabolicPath::initFromUpVector(const TVec3f& rStart, const TVec3f& rEnd, const TVec3f& rUp, f32 max) {
    mAxisY.set(rUp);

    f32 dot = mAxisY.dot(rEnd - rStart);
    mAxisZ = rEnd - rStart - (mAxisY * dot);

    MR::separateScalarAndDirection(&mScalar, &mAxisZ, mAxisZ);
    MR::calcParabolicFunctionParam(&mAccel, &mVelocity, max, dot);

    mPosition.set(rStart);
}

void ParabolicPath::initFromUpVectorAddHeight(const TVec3f& rStart, const TVec3f& rEnd, const TVec3f& rUp, f32 max) {
    f32 dot = rUp.dot(rEnd - rStart);

    if (dot < 0.0f) {
        dot = 0.0f;
    }

    initFromUpVector(rStart, rEnd, rUp, max + dot);
}

void ParabolicPath::calcPosition(TVec3f* pOut, f32 f1) const {
    f32 scalarZ = mScalar * f1;
    f32 scalarY = f1 * (mVelocity + mAccel * f1);

    pOut->set(mPosition + mAxisY * scalarY + mAxisZ * scalarZ);
}

void ParabolicPath::calcDirection(TVec3f* pOut, f32 f1, f32 step) const {
    f32 startParam, endParam;
    if (f1 < step) {
        endParam = step;
        startParam = 0.0f;
    } else if (f1 > 1.0f - step) {
        endParam = 1.0f;
        startParam = 1.0f - step;
    } else {
        startParam = f1;
        endParam = f1 + step;
    }

    TVec3f startPosition, endPosition;
    calcPosition(&startPosition, startParam);
    calcPosition(&endPosition, endParam);
    pOut->set(endPosition - startPosition);
    MR::normalizeOrZero(pOut);
}

f32 ParabolicPath::getLength(f32 startParam, f32 endParam, s32 numSegments) const {
    if (numSegments <= 0) {
        numSegments = 1;
    }

    f32 parameterLengthSegment = (endParam - startParam) / numSegments;
    f32 length = 0.0f;

    f32 f6 = (mScalar * parameterLengthSegment) * (mScalar * parameterLengthSegment);
    f32 f2 = startParam * (mAccel * startParam + mVelocity);

    for (int i = 0; i < numSegments; i++) {
        f32 endSegmentParam = startParam + parameterLengthSegment * (i + 1);
        f32 f4 = endSegmentParam * (mAccel * endSegmentParam + mVelocity);

        length += MR::fastSqrtf((f4 - f2) * (f4 - f2) + f6);
        f2 = f4;
    }

    return length;
}

f32 ParabolicPath::getTotalLength(s32 numSegments) const {
    return getLength(0.0f, 1.0f, numSegments);
}

f32 ParabolicPath::calcPathSpeedFromAverageSpeed(f32 avgSpeed) const {
    return avgSpeed / getLength(0.0f, 1.0f, 10);
}
