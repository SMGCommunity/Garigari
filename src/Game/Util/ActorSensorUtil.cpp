#include "Util/ActorSensorUtil.hpp"
#include "LiveActor/HitSensor.hpp"
#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/HitSensorInfo.hpp"
#include "Util/JointUtil.hpp"

namespace MR {
    void setSensorFollowPos(LiveActor *pActor, const char *pSensorName, const TVec3f *pPos) {
        pActor->mSensorKeeper->getSensorInfo(pSensorName)->setFollowPos(pPos);
    }

    void setSensorFollowMtx(LiveActor *pActor, const char *pSensorName, MtxPtr mtx) {
        pActor->mSensorKeeper->getSensorInfo(pSensorName)->setFollowMtx(mtx);
    }

    HitSensor* addHitSensor(LiveActor *pActor, const char *pName, u32 type, u16 a4, f32 radius, const TVec3f &rOffset) {
        return pActor->mSensorKeeper->add(pName, type, a4, radius, pActor, rOffset)->mSensor;
    }

    HitSensor* addHitSensorBinder(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x5B, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPriorBinder(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x5D, a4, radius, rOffset);
    }

    HitSensor* addHitSensorRide(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0xC, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObj(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x40, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObjSimple(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x41, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObjMoveCollision(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x42, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEnemy(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x18, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEnemyAttack(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x1A, a4, radius, rOffset);
    }

    HitSensor* addHitSensorNpc(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x8, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEye(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x7A, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPush(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f &rOffset) {
        return MR::addHitSensor(pActor, pName, 0x7B, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPosRide(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f *pFollowPos, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xC, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorPosMapObj(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f *pFollowPos, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x40, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorPosEnemyAttack(LiveActor *pActor, const char *pName, u16 a4, f32 radius, const TVec3f *pFollowPos, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x1A, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtx(LiveActor *pActor, const char *pName, u32 type, u16 a4, f32 radius, MtxPtr mtx, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, type, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxRide(LiveActor *pActor, const char *pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xC, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxEnemy(LiveActor *pActor, const char *pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x18, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxEnemyAttack(LiveActor *pActor, const char *pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x1A, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxAnimal(LiveActor *pActor, const char *pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f &rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xA, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorAtJoint(LiveActor *pActor, const char *pName, const char *pJointName, u32 type, u16 a5, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, type, a5, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointMapObj(LiveActor *pActor, const char *pName, const char *pJointName, u16 a4, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x40, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointMapObjSimple(LiveActor *pActor, const char *pName, const char *pJointName, u16 a4, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x41, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointEnemy(LiveActor *pActor, const char *pName, const char *pJointName, u16 a4, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x18, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointEnemyAttack(LiveActor *pActor, const char *pName, const char *pJointName, u16 a4, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x1A, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointNpc(LiveActor *pActor, const char *pName, const char *pJointName, u16 a4, f32 radius, const TVec3f &rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x8, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorCallback(LiveActor *pActor, const char *pName, u32 type, u16 a4, f32 radius) {
        return pActor->mSensorKeeper->addCallback(pName, type, a4, radius, pActor)->mSensor;
    }

    HitSensor* addHitSensorCallbackBinder(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x5B, a4, radius);
    }

    HitSensor* addHitSensorCallbackPriorBinder(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x5D, a4, radius);
    }

    HitSensor* addHitSensorCallbackRide(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0xC, a4, radius);
    }

    HitSensor* addHitSensorCallbackMapObj(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x40, a4, radius);
    }

    HitSensor* addHitSensorCallbackEnemyAttack(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x1A, a4, radius);
    }

    HitSensor* addHitSensorCallbackEye(LiveActor *pActor, const char *pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x7A, a4, radius);
    }

    HitSensor* addBodyMessageSensor(LiveActor *pActor, u32 type) __attribute__((never_inline)) {
        TVec3f offs(0.0f, 0.0, 0.0f);
        return pActor->mSensorKeeper->add("Body", type, 0, 0.0f, pActor, offs)->mSensor;
    }

    HitSensor* addBodyMessageSensorReceiver(LiveActor *pActor) {
        return MR::addBodyMessageSensor(pActor, 0x7F);
    }

    HitSensor* addBodyMessageSensorMapObj(LiveActor *pActor) {
        return MR::addBodyMessageSensor(pActor, 0x40);
    }

    HitSensor* addBodyMessageSensorMapObjPress(LiveActor *pActor) {
        return MR::addBodyMessageSensor(pActor, 0x71);
    }

    HitSensor* addBodyMessageSensorEnemy(LiveActor *pActor) {
        return MR::addBodyMessageSensor(pActor, 0x18);
    }
};
