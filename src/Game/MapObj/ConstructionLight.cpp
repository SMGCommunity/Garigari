#include "Game/MapObj/ConstructionLight.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"

namespace NrvConstructionLight {
    NEW_NERVE(ConstructionLightNrvNormal, ConstructionLight, Normal);
    NEW_NERVE(ConstructionLightNrvBreak, ConstructionLight, Break);
};  // namespace NrvConstructionLight

ConstructionLight::ConstructionLight(const char* pName) : LiveActor(pName), mSpawnsCoin() {
}

void ConstructionLight::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    MR::getJMapInfoArg0NoInit(rIter, &mSpawnsCoin);

    if (mSpawnsCoin) {
        MR::declareCoin(this, 1);
    } else {
        MR::declareStarPiece(this, 3);
    }

    initNerve(GET_NERVE(ConstructionLight, ConstructionLightNrvNormal));

    makeActorAppeared();
}

void ConstructionLight::appear() {
    LiveActor::appear();
    MR::emitEffect(this, "Appear");
    MR::startActionSound(this, "Appear");
}

void ConstructionLight::exeNormal() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Normal");
        MR::setBvaFrameAndStop(this, 0.0f);
    }

    MR::attachSupportTicoToTarget(this);
}

void ConstructionLight::exeBreak() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Break");
        MR::startHitReaction(this, "壊れリアクション");
        MR::setBvaFrameAndStop(this, 0.0f);

        MR::invalidateCollisionParts(this);

        if (mSpawnsCoin) {
            MR::appearCoinPop(this, mPosition, 1);
        } else {
            MR::appearStarPiece(this, mPosition, 3, 10.0f, 40.0f, false);
        }
    }
}

bool ConstructionLight::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (isNerve(GET_NERVE(ConstructionLight, ConstructionLightNrvBreak))) {
        return false;
    }

    if (MR::isEqualSensor(pReceiver, this, "Body")) {
        return false;
    }

    if (MR::isMsgStarPieceAttack(msg) || MR::isMsgPlayerSpinAttackOrSupportTico(msg) || MR::isMsgDrillAttack(msg) || MR::isMsgRockAttack(msg)) {
        setNerve(GET_NERVE(ConstructionLight, ConstructionLightNrvBreak));
        return true;
    }

    return false;
}
