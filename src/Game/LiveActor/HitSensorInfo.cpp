#include "LiveActor/HitSensorInfo.hpp"
#include "LiveActor/HitSensor.hpp"
#include "LiveActor/LiveActor.hpp"
#include "Util.hpp"

void HitSensorInfo::setFollowPos(const TVec3f *pFollowPos) {
    mFollowPos = pFollowPos;
}

void HitSensorInfo::setFollowMtx(MtxPtr followMtx) {
    mFollowMtx = followMtx;
}

HitSensorInfo::HitSensorInfo(const char *pSensorName, HitSensor *pSensor, const TVec3f *pFollowPos, MtxPtr followMtx, const TVec3f &rVec, bool flag) :
    mSensorName(pSensorName), mNameHash(MR::getHashCode(pSensorName)), _C(rVec), mSensor(pSensor), mFollowPos(pFollowPos), mFollowMtx(followMtx) {
        mHasCallback = flag;
}

// https://decomp.me/scratch/IDjcw
void HitSensorInfo::update() {
    if (mHasCallback) {
        mSensor->mHostActor->updateHitSensor(mSensor);
        return;
    }

    TVec3f v20;

    if (mFollowMtx != nullptr) {
        v20.set((*mFollowMtx)[3], (*mFollowMtx)[7], (*mFollowMtx)[11]);
        v20.x += (((*mFollowMtx)[2] * _C.z) + (((*mFollowMtx)[0] * _C.x) + ((*mFollowMtx)[1] * _C.y)));
        MtxPtr anotherMtx = mFollowMtx;
        v20.y += (((*mFollowMtx)[6] * _C.z) + (((*mFollowMtx)[4] * _C.x) + ((*mFollowMtx)[5] *_C.y)));
        v20.z += (((*mFollowMtx)[10] * _C.z) + (((*mFollowMtx)[8] * _C.x) + ((*mFollowMtx)[9] * _C.y)));
    }
    else {
        if (mFollowPos != nullptr) {
            v20.set(mFollowPos->x, mFollowPos->y, mFollowPos->z);
        }
        else {
            v20.set(mSensor->mHostActor->mPosition);
        }

        MtxPtr mtx = mSensor->mHostActor->getBaseMtx();

        if (mtx != nullptr) {
            v20.x += (((*mtx)[2] * _C.z) + (((*mtx)[0] * _C.x) + ((*mtx)[1] * _C.y)));
            v20.y += (((*mtx)[6] * _C.z) + (((*mtx)[4] * _C.x) + ((*mtx)[5] * _C.y)));
            v20.z += (((*mtx)[10] * _C.z) + (((*mtx)[8] * _C.x) + ((*mtx)[9] * _C.y)));
        }
        else {
            JMathInlineVEC::PSVECAdd(&v20, &_C, &v20);
        }
    }

    mSensor->mOffset.set(v20);
}

void HitSensorInfo::doObjCol() {
    for (s32 i = 0; i < mSensor->mSensorCount; i++) {
        if (!MR::isDead(mSensor->mSensors[i]->mHostActor)) {
            mSensor->mHostActor->attackSensor(mSensor, mSensor->mSensors[i]);
        }
    }
}
