#include "Game/MapObj/PlantRailInfo.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/LiveActor/RailRider.hpp"
#include "Game/MapObj/PlantPoint.hpp"
#include "Game/Util.hpp"
#include "Game/Util/MathUtil.hpp"

PlantRailInfo::PlantRailInfo(const JMapInfoIter& rIter, f32 speed) : mRailSpeed(speed), mPlantPointNum(), mPlantPoints(), mRailRider() {
    mRailRider = new RailRider(rIter);
    mRailRider->setSpeed(mRailSpeed);

    mPlantPointNum = static_cast< s32 >(mRailRider->getTotalLength() / mRailSpeed) + 2;

    mPlantPoints = new PlantPoint*[mPlantPointNum];

    for (s32 idx = 0; idx < mPlantPointNum - 1; idx++) {
        mPlantPoints[idx] = new PlantPoint(mRailRider->mCurPos, mRailRider->mCurDirection, 1.0f, TVec3f(1.0f, 0.0f, 0.0f));
        mRailRider->move();
    }

    mRailRider->setCoord(mRailRider->getTotalLength());

    PlantPoint* point = new PlantPoint(mRailRider->getCurPos(), getPlantPoint(mPlantPointNum - 2)->getUpVec(), 1.0f, TVec3f(1.0f, 0.0f, 0.0f));
    s32 index = mPlantPointNum - 1;
    mPlantPoints[index] = point;

    PlantPoint* firstPoint = getPlantPoint(0);
    PlantPoint* lastPoint = getPlantPoint(mPlantPointNum - 2);
    firstPoint->setAxisAndPos(lastPoint->mSide, lastPoint->mUp, lastPoint->mFront, firstPoint->mPosition);
}

void PlantRailInfo::calcPosAndAxisY(TVec3f* pPos, TVec3f* pAxisY, f32 coord) const {
    f32 normalized = (coord / mRailRider->getTotalLength()) * mPlantPointNum;

    s32 start = normalized;
    s32 end = start + 1;

    if (start >= mPlantPointNum) {
        start = mPlantPointNum - 1;
    }

    if (end >= mPlantPointNum) {
        end = mPlantPointNum - 1;
    }

    normalized -= start;
    f32 t = normalized;
    f32 negt = 1.0f - t;

    pPos->x = negt * mPlantPoints[start]->mPosition.x + t * mPlantPoints[end]->mPosition.x;
    pPos->y = negt * mPlantPoints[start]->mPosition.y + t * mPlantPoints[end]->mPosition.y;
    pPos->z = negt * mPlantPoints[start]->mPosition.z + t * mPlantPoints[end]->mPosition.z;

    pAxisY->x = negt * mPlantPoints[start]->mUp.x + t * mPlantPoints[end]->mUp.x;
    pAxisY->y = negt * mPlantPoints[start]->mUp.y + t * mPlantPoints[end]->mUp.y;
    pAxisY->z = negt * mPlantPoints[start]->mUp.z + t * mPlantPoints[end]->mUp.z;

    MR::normalize(pAxisY);
}

void PlantRailInfo::calcNearestPointPos(TVec3f* pPointPos, const TVec3f& rPos, s32 cutoff) const {
    s32 nearestIdx = 0;
    f32 closestMag = 100000.0f * 100000.0f;

    for (s32 idx = cutoff; idx < mPlantPointNum - cutoff; idx++) {
        f32 mag = mPlantPoints[idx]->mPosition.squared(rPos);

        if (mag < closestMag) {
            nearestIdx = idx;
            closestMag = mag;
        }
    }

    PlantPoint* nearestPoint = mPlantPoints[nearestIdx];
    pPointPos->x = nearestPoint->mPosition.x;
    pPointPos->y = nearestPoint->mPosition.y;
    pPointPos->z = nearestPoint->mPosition.z;
}
