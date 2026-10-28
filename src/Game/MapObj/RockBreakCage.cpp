#include "Game/MapObj/RockBreakCage.hpp"
#include "Game/LiveActor/BreakModel.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/StringUtil.hpp"

namespace NrvRockBreakCage {
    NEW_NERVE(RockBreakCageNrvWait, RockBreakCage, Wait);
    NEW_NERVE(RockBreakCageNrvBreak, RockBreakCage, Break);
    NEW_NERVE(RockBreakCageNrvCrack, RockBreakCage, Crack);
};  // namespace NrvRockBreakCage

void RockBreakCage_FORCE_MATCH_SDATA2() {
    (void)1.0f;
    (void)0.0f;
    (void)2.0f;
    (void)2.0f;
    (void)4.0f;
}

RockBreakCage::RockBreakCage(const char* pName) : LiveActor(pName), mRemainingHits(2), mBreakModel(), mObjectName() {
}

void RockBreakCage::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(RockBreakCage, RockBreakCageNrvWait));

    MR::startBva(this, "RockBreakCage");
    MR::setBvaFrameAndStop(this, 0.0f);

    MR::initUseStageSwitchWriteDead(this, rIter);

    mBreakModel = MR::tryCreateBreakModel(this, nullptr);

    MR::getObjectName(&mObjectName, rIter);

    makeActorAppeared();
}

bool RockBreakCage::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(RockBreakCage, RockBreakCageNrvWait))) {
        return false;
    }

    if (MR::isMsgRockAttack(msg)) {
        if (--mRemainingHits <= 0) {
            mBreakModel->appear();

            if (MR::isEqualString(mObjectName, "RockBreakCageL")) {
                MR::setScale(mBreakModel, 4.0f);
            } else {
                MR::setScale(mBreakModel, 2.0f);
            }

            MR::startActionSound(this, "Break");

            setNerve(GET_NERVE(RockBreakCage, RockBreakCageNrvBreak));
        } else {
            MR::startActionSound(this, "Crack");

            MR::setBvaFrameAndStop(this, 1.0f);

            setNerve(GET_NERVE(RockBreakCage, RockBreakCageNrvCrack));
        }

        return true;
    }

    return false;
}

void RockBreakCage::kill() {
    if (MR::isValidSwitchDead(this)) {
        MR::onSwitchDead(this);
    }

    LiveActor::kill();
}

void RockBreakCage::exeWait() {
}

void RockBreakCage::exeBreak() {
    if (MR::isFirstStep(this)) {
        if (MR::isValidSwitchDead(this)) {
            MR::onSwitchDead(this);
        }

        MR::setBvaFrameAndStop(this, 2.0f);
        MR::invalidateCollisionParts(this);
    }
}

void RockBreakCage::exeCrack() {
    if (MR::isGreaterEqualStep(this, 30)) {
        setNerve(GET_NERVE(RockBreakCage, RockBreakCageNrvWait));
    }
}
