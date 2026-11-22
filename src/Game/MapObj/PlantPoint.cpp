#include "Game/MapObj/PlantPoint.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util.hpp"
#include "Game/Util/MathUtil.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/mtx.h>

PlantPoint::PlantPoint(const TVec3f& rPosition, const TVec3f& rUp, f32 thickness, const TVec3f& rSide)
    : mPosition(rPosition.x, rPosition.y, rPosition.z), mSide(rSide), mUp(rUp), mFront(0.0f, 0.0f, 1.0f), mThickness(thickness) {
    TVec3f front = mSide.cross(mUp);

    if (MR::isNearZero(front)) {
        MR::makeAxisUpFront(&mSide, &mFront, mUp, mFront);
    } else {
        MR::makeAxisUpSide(&mFront, &mSide, mUp, mSide);
    }
}

void PlantPoint::setAxisAndPos(const TVec3f& pSide, const TVec3f& pUp, const TVec3f& pFront, const TVec3f& pPosition) {
    mSide.set(pSide);
    mUp.set(pUp);
    mFront.set(pFront);
    mPosition.set(pPosition);
}
