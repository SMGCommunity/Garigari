#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/HitSensorInfo.hpp"
#include "LiveActor/HitSensor.hpp"
#include "Util.hpp"
#include <cstring>

HitSensorKeeper::HitSensorKeeper(int max) {
    mSensorCount = 0;
    mMaxSensorCount = max;
    mSensorInfo = nullptr;
    _C =  0;
    _10 = 0;
    mSensorInfo = new HitSensorInfo*[max];

    for (s32 i = 0; i < mMaxSensorCount; i++) {
        mSensorInfo[i] = nullptr;
    }   
}

HitSensorInfo* HitSensorKeeper::add(const char *pSensorName, u32 sensorType, u16 numSensors, f32 radius, LiveActor *pActor, const TVec3f &rOffs) {
    HitSensorInfo* info = new HitSensorInfo(pSensorName, new HitSensor(sensorType, numSensors, radius, pActor), nullptr, nullptr, rOffs, false);
    registHitSensorInfo(info);
    return info;
}

HitSensorInfo* HitSensorKeeper::addCallback(const char *pSensorName, u32 sensorType, u16 numSensors, f32 radius, LiveActor *pActor) {
    HitSensorInfo* info = new HitSensorInfo(pSensorName, new HitSensor(sensorType, numSensors, radius, pActor), nullptr, nullptr, TVec3f(0.0f), true);
    registHitSensorInfo(info);
    return info;
}

HitSensor* HitSensorKeeper::getSensor(const char *pName) const {
    if (mSensorCount == 1) {
        return mSensorInfo[0]->mSensor;
    }

    u32 hashCode = MR::getHashCode(pName);
    for (s32 i = 0; i < mSensorCount; i++) {
        HitSensorInfo* info = mSensorInfo[i];

        if (hashCode == info->mNameHash && !strcmp(info->mSensorName, pName)) {
            return mSensorInfo[i]->mSensor;
        }
    }

    return nullptr;
}

void HitSensorKeeper::update() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->update();
    }
}

void HitSensorKeeper::doObjCol() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->doObjCol();
    }
}

void HitSensorKeeper::clear() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->mSensor->mSensorCount = 0;
    }
}

void HitSensorKeeper::validate() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->mSensor->validate();
    }
}

void HitSensorKeeper::invalidate() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->mSensor->invalidate();
    }
}

void HitSensorKeeper::validateBySystem() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->mSensor->validateBySystem();
    }
}

void HitSensorKeeper::invalidateBySystem() {
    for (s32 i = 0; i < mSensorCount; i++) {
        mSensorInfo[i]->mSensor->invalidateBySystem();
    }
}

HitSensorInfo* HitSensorKeeper::getNthSensorInfo(int idx) const {
    return mSensorInfo[idx];
}

HitSensorInfo* HitSensorKeeper::getSensorInfo(const char *pName) const {
    if (mSensorCount == 1) {
        return mSensorInfo[0];
    }

    u32 hashCode = MR::getHashCode(pName);
    for (s32 i = 0; i < mSensorCount; i++) {
        HitSensorInfo* info = mSensorInfo[i];

        if (hashCode == info->mNameHash && !strcmp(info->mSensorName, pName)) {
            return mSensorInfo[i];
        }
    }

    return nullptr;
}

void HitSensorKeeper::registHitSensorInfo(HitSensorInfo *pInfo) {
    mSensorInfo[mSensorCount] = pInfo;
    mSensorCount++;
    pInfo->update();
}
