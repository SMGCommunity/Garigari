#include "Game/MapObj/SnowMan.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Map/CollisionParts.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

namespace NrvSnowMan {
    NEW_NERVE(SnowManNrvWait, SnowMan, Wait);
    NEW_NERVE(SnowManNrvWaitBody, SnowMan, WaitBody);
    NEW_NERVE(SnowManNrvWaitHead, SnowMan, WaitHead);
    NEW_NERVE(SnowManNrvMeltHead, SnowMan, MeltHead);
    NEW_NERVE(SnowManNrvMeltBody, SnowMan, MeltBody);
    NEW_NERVE(SnowManNrvDownHead, SnowMan, DownHead);
    NEW_NERVE(SnowManNrvDownBody, SnowMan, DownBody);
};  // namespace NrvSnowMan

SnowMan::SnowMan(const char* pName)
    : LiveActor(pName), mHeadCollisionParts(), mBodyCollisionParts(), mDemoObj(), mAnimScaleCtrl(), mAnimScaleParam() {
}

void SnowMan::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    mHeadCollisionParts = MR::createCollisionPartsFromLiveActor(this, "HeadCol", getSensor("Head"), MR::getJointMtx(this, "Head"),
                                                                MR::CollisionScaleType_NotUsingScale);
    mBodyCollisionParts = MR::createCollisionPartsFromLiveActor(this, "BodyCol", getSensor("Body"), MR::getJointMtx(this, "Body"),
                                                                MR::CollisionScaleType_NotUsingScale);
    MR::validateCollisionParts(mHeadCollisionParts);
    MR::validateCollisionParts(mBodyCollisionParts);
    mAnimScaleParam = new AnimScaleParam();
    mAnimScaleParam->_8 = 0.95f;
    mAnimScaleParam->_C = 1.05f;
    mAnimScaleParam->_24 = 0.60f;
    mAnimScaleParam->_28 = 0.8f;
    mAnimScaleCtrl = new AnimScaleController(mAnimScaleParam);
    mDemoObj = MR::tryCreateBreakDustDemoObj(this, getBaseMtx());
    initNerve(GET_NERVE(SnowMan, SnowManNrvWait));
    makeActorAppeared();
}

void SnowMan::exeWait() {
}

void SnowMan::exeWaitBody() {
}

void SnowMan::exeWaitHead() {
}

void SnowMan::exeMeltHead() {
    if (MR::isFirstStep(this)) {
        MR::invalidateCollisionParts(mHeadCollisionParts);
        MR::startAction(this, "MeltHead");
        MR::shakeCameraWeak();
        if (MR::isValidSwitchA(this)) {
            MR::onSwitchA(this);
        }
    }

    if (MR::isActionEnd(this)) {
        MR::hideMaterial(this, "SnowManBucketMat_v");
        setNerve(GET_NERVE(SnowMan, SnowManNrvWaitBody));
    }
}

void SnowMan::exeMeltBody() {
    if (MR::isFirstStep(this)) {
        MR::invalidateCollisionParts(mBodyCollisionParts);
        MR::startAction(this, "MeltBody");
        MR::shakeCameraWeak();
        if (MR::isValidSwitchA(this)) {
            MR::onSwitchA(this);
        }

        if (MR::isValidSwitchB(this)) {
            MR::onSwitchB(this);
        }
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(SnowMan, SnowManNrvWaitHead));
    }
}

void SnowMan::exeDownHead() {
    if (MR::isFirstStep(this)) {
        MR::invalidateCollisionParts(mHeadCollisionParts);
        MR::invalidateCollisionParts(mBodyCollisionParts);
        MR::startAction(this, "DownHead");
        MR::shakeCameraWeak();
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}

void SnowMan::exeDownBody() {
    if (MR::isFirstStep(this)) {
        MR::invalidateCollisionParts(mHeadCollisionParts);
        MR::invalidateCollisionParts(mBodyCollisionParts);
        MR::startAction(this, "DownBody");
        MR::shakeCameraWeak();
        if (MR::isValidSwitchB(this)) {
            MR::onSwitchB(this);
        }
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}

void SnowMan::calcAndSetBaseMtx() {
    LiveActor::calcAndSetBaseMtx();
    MR::setBaseScale(this, mAnimScaleCtrl->_C * mScale);
}

void SnowMan::control() {
    if (mHeadCollisionParts->_CC) {
        mHeadCollisionParts->setMtx();
    }

    if (mBodyCollisionParts->_CC) {
        mBodyCollisionParts->setMtx();
    }
    mAnimScaleCtrl->updateNerve();
}

void SnowMan::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (isNerve(GET_NERVE(SnowMan, SnowManNrvMeltBody)) && MR::isEqualSensor(pSender, this, "Push")) {
        MR::sendMsgPush(pReceiver, pSender);
    }
}

bool SnowMan::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isEqualSensor(pReceiver, this, "Push")) {
        return false;
    }

    if (MR::isMsgFireBallAttack(msg) || MR::isMsgRockAttack(msg) || MR::isMsgSnowBallAttack(msg)) {
        if (pReceiver == getSensor("Head")) {
            damageHead();
        } else {
            damageBody();
        }

        return true;
    }

    if (MR::isMsgPlayerSpinAttackOrSupportTico(msg)) {
        if (mAnimScaleCtrl->isHitReaction(-1)) {
            return false;
        } else {
            mAnimScaleCtrl->startHitReaction();
            MR::startActionSound(this, "Shake");
            return true;
        }
    }

    return false;
}

void SnowMan::damageHead() {
    if (isNerve(GET_NERVE(SnowMan, SnowManNrvWait))) {
        setNerve(GET_NERVE(SnowMan, SnowManNrvMeltHead));
    } else if (isNerve(GET_NERVE(SnowMan, SnowManNrvWaitHead))) {
        setNerve(GET_NERVE(SnowMan, SnowManNrvDownHead));
    }
}

void SnowMan::damageBody() {
    if (isNerve(GET_NERVE(SnowMan, SnowManNrvWait))) {
        setNerve(GET_NERVE(SnowMan, SnowManNrvMeltBody));
    } else if (isNerve(GET_NERVE(SnowMan, SnowManNrvWaitBody))) {
        setNerve(GET_NERVE(SnowMan, SnowManNrvDownBody));
    }

    if (mDemoObj != nullptr && MR::isDead(mDemoObj)) {
        mDemoObj->appear();
    }
}
