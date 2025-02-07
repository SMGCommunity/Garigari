#include "Map/RailPart.hpp"
#include "Map/BezierRail.hpp"
#include <JMath.hpp>

RailPart::RailPart() {
    mLinearRailPart = nullptr;
    mBezierRailPart = nullptr;
}

void RailPart::init(const TVec3f &a1, const TVec3f &a2, const TVec3f &a3, const TVec3f &a4) {
    if (a1.epsilonEquals(a2, 0.1f) && a4.epsilonEquals(a3, 0.1f)) {
        mLinearRailPart = new LinearRailPart();
        mLinearRailPart->set(a1, a4);
    }
    else {
        initForBezier(a1, a2, a3, a4);
    }
}

/* https://decomp.me/scratch/hV4jg */
void RailPart::initForBezier(const TVec3f &a1, const TVec3f &a2, const TVec3f &a3, const TVec3f &a4) {
    mBezierRailPart = new BezierRailPart(a1, a2, a3, a4);
}

void RailPart::calcPos(TVec3f *pPos, f32 a1) const {
    if (mLinearRailPart != nullptr) {
        JMAVECScaleAdd(&mLinearRailPart->mStopPoint, &mLinearRailPart->mStartPoint, pPos, a1);
    }
    else {
        mBezierRailPart->calcPos(pPos, a1);
    }
}

void RailPart::calcVelocity(TVec3f *pVelocity, f32 a1) const {
    if (mLinearRailPart != nullptr) {
        pVelocity->set<f32>(mLinearRailPart->mStopPoint);
    }
    else {
        mBezierRailPart->calcVelocity(pVelocity, a1);
    }
}

f32 RailPart::getLength(f32 a1, f32 a2, int a3) const {
    if (mLinearRailPart != nullptr) {
        return mLinearRailPart->mMag * (a2 - a1);
    }

    return mBezierRailPart->getLength(a1, a2, a3);
}

f32 RailPart::getTotalLength() const {
    if (mLinearRailPart != nullptr) {
        return mLinearRailPart->mMag;
    }

    return mBezierRailPart->mLength;
}

f32 RailPart::getParam(f32 a1) const {
    if (mLinearRailPart != nullptr) {
        return a1 / mLinearRailPart->mMag;
    }

    return mBezierRailPart->getParam(a1);
}

f32 RailPart::getNearestParam(const TVec3f &a1, f32 a2) const {
    if (mLinearRailPart != nullptr) {
        return mLinearRailPart->getNearestParam(a1, a2);
    }

    return mBezierRailPart->getNearestParam(a1, a2);
}

void LinearRailPart::set(const TVec3f &a1, const TVec3f &a2) {
    mStartPoint = a1;
    mStopPoint = a2;
    mStopPoint -= a1;
    mMag = C_VECMag(&mStopPoint);
}

f32 LinearRailPart::getNearestParam(const TVec3f &a1, f32 a2) const {
    TVec3f vec(a1);
    vec -= mStartPoint;
    f32 squareMag = mStopPoint.squareMag();
    f32 dot = vec.dot(mStopPoint) / squareMag;

    f32 v12 = 0.0f;
    if (dot < 0.0f) {
        return 0.0f;
    }

    v12 = 1.0f;
    if (dot > 1.0f) {
        return 1.0f;
    }

    return dot;
}
