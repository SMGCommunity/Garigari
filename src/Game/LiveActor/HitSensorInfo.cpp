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
    mSensorName(pSensorName), mNameHash(MR::getHashCode(pSensorName)), _C(static_cast<const Vec&>(rVec)), mSensor(pSensor), mFollowPos(pFollowPos), mFollowMtx(followMtx) {
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
        v20.set<f32>(mFollowMtx[0][3], mFollowMtx[1][3], mFollowMtx[2][3]);
        v20.x += ((mFollowMtx[0][2] * _C.z) + ((mFollowMtx[0][0] * _C.x) + (mFollowMtx[0][1] * _C.y)));
        MtxPtr const& anotherMtx = mFollowMtx;
        v20.y += ((anotherMtx[1][2] * _C.z) + ((anotherMtx[1][0] * _C.x) + (anotherMtx[1][1] *_C.y)));
        v20.z += ((anotherMtx[2][2] * _C.z) + ((anotherMtx[2][0] * _C.x) + (anotherMtx[2][1] * _C.y)));
    }
    else {
        if (mFollowPos != nullptr) {
            v20.set<f32>(mFollowPos->x, mFollowPos->y, mFollowPos->z);
        }
        else {
            v20.set<f32>(mSensor->mHostActor->mPosition);
        }

        MtxPtr mtx = mSensor->mHostActor->getBaseMtx();

        if (mtx != nullptr) {
            v20.x += ((mtx[0][2] * _C.z) + ((mtx[0][0] * _C.x) + (mtx[0][1] * _C.y)));
            v20.y += ((mtx[1][2] * _C.z) + ((mtx[1][0] * _C.x) + (mtx[1][1] * _C.y)));
            v20.z += ((mtx[2][2] * _C.z) + ((mtx[2][0] * _C.x) + (mtx[2][1] * _C.y)));
        }
        else {
            JMathInlineVEC::PSVECAdd(&v20, &_C, &v20);
        }
    }

    mSensor->mOffset.set<f32>(v20);
}

void HitSensorInfo::doObjCol() {
    for (s32 i = 0; i < mSensor->mSensorCount; i++) {
        if (!MR::isDead(mSensor->mSensors[i]->mHostActor)) {
            mSensor->mHostActor->attackSensor(mSensor, mSensor->mSensors[i]);
        }
    }
}
