#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/HitSensorInfo.hpp"
#include "Game/LiveActor/HitSensorKeeper.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/JointUtil.hpp"
#include <JSystem/JGeometry/TVec.hpp>

namespace MR {
    void setSensorFollowPos(LiveActor* pActor, const char* pSensorName, const TVec3f* pPos) {
        pActor->mSensorKeeper->getSensorInfo(pSensorName)->setFollowPos(pPos);
    }

    void setSensorFollowMtx(LiveActor* pActor, const char* pSensorName, MtxPtr mtx) {
        pActor->mSensorKeeper->getSensorInfo(pSensorName)->setFollowMtx(mtx);
    }

    HitSensor* addHitSensor(LiveActor* pActor, const char* pName, u32 type, u16 a4, f32 radius, const TVec3f& rOffset) {
        return pActor->mSensorKeeper->add(pName, type, a4, radius, pActor, rOffset)->mSensor;
    }

    HitSensor* addHitSensorBinder(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x5B, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPriorBinder(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x5D, a4, radius, rOffset);
    }

    HitSensor* addHitSensorRide(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0xC, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObj(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x40, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObjSimple(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x41, a4, radius, rOffset);
    }

    HitSensor* addHitSensorMapObjMoveCollision(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x42, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEnemy(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x18, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEnemyAttack(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x1A, a4, radius, rOffset);
    }

    HitSensor* addHitSensorNpc(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x8, a4, radius, rOffset);
    }

    HitSensor* addHitSensorEye(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x7A, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPush(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f& rOffset) {
        return MR::addHitSensor(pActor, pName, 0x7B, a4, radius, rOffset);
    }

    HitSensor* addHitSensorPosRide(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f* pFollowPos, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xC, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorPosMapObj(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f* pFollowPos, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x40, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorPosEnemyAttack(LiveActor* pActor, const char* pName, u16 a4, f32 radius, const TVec3f* pFollowPos, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x1A, a4, radius, pActor, rOffset);
        info->setFollowPos(pFollowPos);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtx(LiveActor* pActor, const char* pName, u32 type, u16 a4, f32 radius, MtxPtr mtx, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, type, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxRide(LiveActor* pActor, const char* pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xC, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxEnemy(LiveActor* pActor, const char* pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x18, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxEnemyAttack(LiveActor* pActor, const char* pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0x1A, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorMtxAnimal(LiveActor* pActor, const char* pName, u16 a4, f32 radius, MtxPtr mtx, const TVec3f& rOffset) {
        HitSensorInfo* info = pActor->mSensorKeeper->add(pName, 0xA, a4, radius, pActor, rOffset);
        info->setFollowMtx(mtx);
        return info->mSensor;
    }

    HitSensor* addHitSensorAtJoint(LiveActor* pActor, const char* pName, const char* pJointName, u32 type, u16 a5, f32 radius,
                                   const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, type, a5, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointMapObj(LiveActor* pActor, const char* pName, const char* pJointName, u16 a4, f32 radius, const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x40, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointMapObjSimple(LiveActor* pActor, const char* pName, const char* pJointName, u16 a4, f32 radius,
                                               const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x41, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointEnemy(LiveActor* pActor, const char* pName, const char* pJointName, u16 a4, f32 radius, const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x18, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointEnemyAttack(LiveActor* pActor, const char* pName, const char* pJointName, u16 a4, f32 radius,
                                              const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x1A, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorAtJointNpc(LiveActor* pActor, const char* pName, const char* pJointName, u16 a4, f32 radius, const TVec3f& rOffset) {
        MtxPtr jointMtx = MR::getJointMtx(pActor, pJointName);
        return addHitSensorMtx(pActor, pName, 0x8, a4, radius, jointMtx, rOffset);
    }

    HitSensor* addHitSensorCallback(LiveActor* pActor, const char* pName, u32 type, u16 a4, f32 radius) {
        return pActor->mSensorKeeper->addCallback(pName, type, a4, radius, pActor)->mSensor;
    }

    HitSensor* addHitSensorCallbackBinder(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x5B, a4, radius);
    }

    HitSensor* addHitSensorCallbackPriorBinder(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x5D, a4, radius);
    }

    HitSensor* addHitSensorCallbackRide(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0xC, a4, radius);
    }

    HitSensor* addHitSensorCallbackMapObj(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x40, a4, radius);
    }

    HitSensor* addHitSensorCallbackEnemyAttack(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x1A, a4, radius);
    }

    HitSensor* addHitSensorCallbackEye(LiveActor* pActor, const char* pName, u16 a4, f32 radius) {
        return MR::addHitSensorCallback(pActor, pName, 0x7A, a4, radius);
    }

    HitSensor* addBodyMessageSensor(LiveActor* pActor, u32 type) __attribute__((never_inline)) {
        TVec3f offs(0.0f, 0.0f, 0.0f);
        return pActor->mSensorKeeper->add("Body", type, 0, 0.0f, pActor, offs)->mSensor;
    }

    HitSensor* addBodyMessageSensorReceiver(LiveActor* pActor) {
        return MR::addBodyMessageSensor(pActor, 0x7F);
    }

    HitSensor* addBodyMessageSensorMapObj(LiveActor* pActor) {
        return MR::addBodyMessageSensor(pActor, 0x40);
    }

    HitSensor* addBodyMessageSensorMapObjPress(LiveActor* pActor) {
        return MR::addBodyMessageSensor(pActor, 0x71);
    }

    HitSensor* addBodyMessageSensorEnemy(LiveActor* pActor) {
        return MR::addBodyMessageSensor(pActor, 0x18);
    }

    HitSensor* addMessageSensorReceiver(LiveActor* pActor, const char* pName) {
        TVec3f offs(0.0f, 0.0f, 0.0f);
        return pActor->mSensorKeeper->add(pName, 0x7F, 0, 0.0f, pActor, offs)->mSensor;
    }

    HitSensor* addHitSensorMapObj(LiveActor* pActor, const char* pName) {
        TVec3f offs(0.0f, 0.0f, 0.0f);
        return pActor->mSensorKeeper->add(pName, 0x40, 0, 0.0f, pActor, offs)->mSensor;
    }

    bool tryUpdateHitSensorsAll(LiveActor* pActor) {
        if (pActor->mSensorKeeper != nullptr) {
            pActor->mSensorKeeper->update();
            return true;
        }

        return false;
    }

    void updateHitSensorsAll(LiveActor* pActor) {
        pActor->mSensorKeeper->update();
    }

    bool isSensorType(const HitSensor* pSensor, u32 type) {
        return pSensor->isType(type);
    }

    void setSensorType(LiveActor* pActor, const char* pName, u32 type) {
        pActor->getSensor(pName)->setType(type);
    }

    bool isSensorValid(const HitSensor* pSensor) {
        bool valid = false;
        if (pSensor->mValidByHost && pSensor->mValidBySystem) {
            valid = true;
        }

        return valid;
    }

    HitSensor* getSensorWithIndex(LiveActor* pActor, int idx) {
        return pActor->mSensorKeeper->getNthSensorInfo(idx)->mSensor;
    }

    void setSensorPos(HitSensor* pSensor, const TVec3f& rPos) {
        pSensor->mOffset.set< f32 >(rPos);
    }

    void setSensorPos(LiveActor* pActor, const char* pName, const TVec3f& rPos) {
        setSensorPos(pActor->getSensor(pName), rPos);
    }

    void setSensorOffset(LiveActor* pActor, const char* pName, const TVec3f& rPos) {
        pActor->mSensorKeeper->getSensorInfo(pName)->_C = rPos;
    }

    f32 getSensorRadius(HitSensor* pSensor) {
        return pSensor->mRadius;
    }

    f32 getSensorRadius(LiveActor* pActor, const char* pName) {
        HitSensorInfo* info = pActor->mSensorKeeper->getSensorInfo(pName);
        return getSensorRadius(info->mSensor);
    }

    void scaleAllSensorRadius(LiveActor* pActor, f32 radius) {
        s32 sensorNum = MR::getSensorNum(pActor);

        for (s32 i = 0; i < sensorNum; i++) {
            HitSensorInfo* inf = pActor->mSensorKeeper->getNthSensorInfo(i);
            inf->mSensor->mRadius = radius * inf->mSensor->mRadius;
        }
    }

    TVec3f& getSensorHostPos(const HitSensor* pSensor) {
        return pSensor->mHostActor->mPosition;
    }

    TVec3f& getSensorHostGravity(const HitSensor* pSensor) {
        return pSensor->mHostActor->mGravity;
    }

    void validateHitSensors(LiveActor* pActor) {
        if (pActor->mSensorKeeper != nullptr) {
            pActor->mSensorKeeper->validate();
        }
    }

    void invalidateHitSensors(LiveActor* pActor) {
        if (pActor->mSensorKeeper != nullptr) {
            pActor->mSensorKeeper->invalidate();
        }
    }

    void validateHitSensor(HitSensor* pSensor) {
        pSensor->validate();
    }

    void invalidateHitSensor(HitSensor* pSensor) {
        pSensor->invalidate();
    }

    void validateHitSensor(LiveActor* pActor, const char* pName) {
        pActor->getSensor(pName)->validate();
    }

    void invalidateHitSensor(LiveActor* pActor, const char* pName) {
        pActor->getSensor(pName)->invalidate();
    }

    bool tryValidateHitSensor(LiveActor* pActor, const char* pName) {
        HitSensor* sensor = pActor->mSensorKeeper->getSensor(pName);
        if (!sensor->mValidByHost) {
            pActor->getSensor(pName)->validate();
            return true;
        } else {
            return false;
        }
    }

    bool tryInvalidateHitSensor(LiveActor* pActor, const char* pName) {
        HitSensor* sensor = pActor->mSensorKeeper->getSensor(pName);
        if (sensor->mValidByHost) {
            pActor->getSensor(pName)->validate();
            return true;
        } else {
            return false;
        }
    }

    void clearHitSensors(LiveActor* pActor) {
        if (pActor->mSensorKeeper != nullptr) {
            pActor->mSensorKeeper->clear();
        }
    }

    s32 getSensorNum(const LiveActor* pActor) {
        if (pActor->mSensorKeeper == nullptr) {
            return 0;
        }

        return pActor->mSensorKeeper->mSensorCount;
    }

    HitSensor* getSensor(LiveActor* pActor, int idx) {
        return pActor->mSensorKeeper->getNthSensorInfo(idx)->mSensor;
    }

    LiveActor* getSensorHost(const HitSensor* pSensor) {
        return pSensor->mHostActor;
    }

    bool isEqualSensor(const HitSensor* pSensor, const LiveActor* pActor, const char* pName) {
        return pSensor == pActor->getSensor(pName);
    }

    bool isSensorPlayer(const HitSensor* pSensor) {
        return pSensor->isType(1);
    }

    bool isSensorYoshi(const HitSensor* pSensor) {
        return pSensor->isType(5);
    }

    bool isSensorBinder(const HitSensor* pSensor) {
        return pSensor->isType(0x5B);
    }

    bool isSensorReceiver(const HitSensor* pSensor) {
        return pSensor->isType(0x7F);
    }

    bool isSensorRide(const HitSensor* pSensor) {
        if (pSensor->mType < 0xB && pSensor->mType > 0x16) {
            return true;
        }

        return false;
    }

    /* ... */

    bool isSensorEnemyAttack(const HitSensor* pSensor) {
        return pSensor->isType(0x1A);
    }

    bool isSensorNpc(const HitSensor* pSensor) {
        return pSensor->mType == 8;
    }

    // MR::isSensorMapObj
    // MR::isSensorAutoRush
    // MR::isSensorRush

    bool isSensorPressObj(const HitSensor* pSensor) {
        return pSensor->mType == 0x71;
    }

    bool isSensorEye(const HitSensor* pSensor) {
        return pSensor->isType(0x7A);
    }

    bool isSensorPush(const HitSensor* pSensor) {
        return pSensor->isType(0x7B);
    }

    bool isSensorItem(const HitSensor* pSensor) {
        if (pSensor->isType(0x44) || pSensor->isType(0x45) || pSensor->isType(0x47)) {
            return true;
        } else {
            return false;
        }
    }

    bool isSensorGhost(const HitSensor* pSensor) {
        return pSensor->isType(0x15);
    }

    bool tryGetItem(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x83, pSender);
    }

    const TVec3f* getSensorPos(const HitSensor* pSensor) {
        return &pSensor->mOffset;
    }

    const TVec3f* getSensorPos(const LiveActor* pActor, const char* pName) {
        return &pActor->getSensor(pName)->mOffset;
    }

    const TVec3f* getSensorPos2(const HitSensor* pSensor) {
        return &pSensor->mOffset;
    }

    const TVec3f* getSensorPos2(const LiveActor* pActor, const char* pName) {
        return &pActor->getSensor(pName)->mOffset;
    }

    /* ... */

    bool sendArbitraryMsg(u32 msg, HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(msg, pSender);
    }

    bool sendMsgPush(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x33, pSender);
    }

    bool sendMsgReflect(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x48, pSender);
    }

    bool sendMsgReflectV(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x49, pSender);
    }

    bool sendMsgGorogoroReflect(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x58, pSender);
    }

    bool fn_80015E60(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x58, pSender);
    }

    bool sendMsgPlayerTrample(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x2, pSender);
    }

    bool sendMsgPlayerPunch(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x1, pSender);
    }

    bool sendMsgInvincibleAttack(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0xE, pSender);
    }

    bool sendMsgDrillAttack(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x10, pSender);
    }

    bool sendMsgRockAttack(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x11, pSender);
    }

    bool sendMsgJump(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x36, pSender);
    }

    bool sendMsgTouchJump(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x37, pSender);
    }

    bool sendMsgTaken(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x2A, pSender);
    }

    bool sendMsgAwayJump(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x39, pSender);
    }

    bool sendMsgFireDance(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x57, pSender);
    }

    bool fn_80015F00(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x57, pSender);
    }

    bool sendMsgRushEnd(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x98, pSender);
    }

    bool sendMsgIsRushEnable(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x99, pSender);
    }

    // sendMsgEnemyAttackMsgToDir(unsigned long, HitSensor*, HitSensor*, const JGeometry::TVec3<float>&)

    bool sendMsgEnemyAttackFlipVeryWeak(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5a, pSender);
    }

    bool sendMsgEnemyAttackFlipWeak(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5b, pSender);
    }

    bool sendMsgEnemyAttackFlipWeakJump(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5c, pSender);
    }

    bool sendMsgEnemyAttackFlip(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5e, pSender);
    }

    // sendMsgEnemyAttackFlipToDir(HitSensor*, HitSensor*, const JGeometry::TVec3<float>&)

    bool sendMsgEnemyAttackFlipJump(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5d, pSender);
    }

    bool sendMsgEnemyAttackFlipRot(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x5f, pSender);
    }

    // sendMsgEnemyAttackFlipMaximumToDir(HitSensor*, HitSensor*, const JGeometry::TVec3<float>&)

    bool sendMsgEnemyAttackFire(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x66, pSender);
    }

    bool sendMsgEnemyAttackFireStrong(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x67, pSender);
    }

    bool sendMsgEnemyAttackElectric(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x68, pSender);
    }

    bool sendMsgEnemyAttackFreeze(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x6b, pSender);
    }

    bool sendMsgEnemyAttackExplosion(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x64, pSender);
    }

    bool sendMsgEnemyAttackCounterSpin(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x6e, pSender);
    }

    bool sendMsgEnemyAttackCounterHipDrop(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x6f, pSender);
    }

    bool sendMsgLockOnStarPieceShoot(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x15, pSender);
    }

    bool sendMsgStarPieceAttack(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0xf, pSender);
    }

    bool sendMsgStarPieceGift(HitSensor* pReceiver, HitSensor* pSender, u32 msg) {
        return pReceiver->receiveMessage(0x15 + msg, pSender);
    }

    bool sendMsgEnemyAttackMaximum(HitSensor* pReceiver, HitSensor* pSender) {
        return pReceiver->receiveMessage(0x63, pSender);
    }

    // sendMsgEnemyAttackMaximumToDir(HitSensor*, HitSensor*, const JGeometry::TVec3<float>&)

};  // namespace MR
