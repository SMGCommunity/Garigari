#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/Spine.hpp"
#include "Map/StageSwitch.hpp"

void LiveActor::init(const JMapInfoIter &) {}

void LiveActor::appear() {
    makeActorAppeared();
}

// LiveActor::makeActorAppeared
// LiveActor::kill
// LiveActor::makeActorDead
// LiveActor::movement
// LiveActor::calcAnim
// LiveActor::calcAnmMtx
// J3DModel::setBaseScale
// LiveActor::calcViewAndEntry
// LiveActor::receiveMessage
// LiveActor::calcAndSetBaseMtx
// LiveActor::getTakingMtx

void LiveActor::setNerve(const Nerve *pNerve) {
    mSpine->setNerve(pNerve);
}

bool LiveActor::isNerve(const Nerve *pNerve) const {
    return mSpine->getCurrentNerve() == pNerve;
}

s32 LiveActor::getNerveStep() const {
    return mSpine->mCurrentStep;
}

HitSensor* LiveActor::getSensor(const char *pSensorName) const {
    if (mSensorKeeper != nullptr) {
        return mSensorKeeper->getSensor(pSensorName);
    }

    return nullptr;
}

// LiveActor::getBaseMtx
// LiveActor::startClipped
// LiveActor::endClipped
// LiveActor::initModelManagerWithAnm

void LiveActor::initNerve(const Nerve *pNerve, s32 numStates) {
    mSpine = new Spine(this, pNerve, numStates);
}

void LiveActor::initHitSensor(s32 numSensors) {
    mSensorKeeper = new HitSensorKeeper(numSensors);
}

// LiveActor::initBinder
// LiveActor::initRailRider
// LiveActor::initEffectKeeper
// LiveActor::initSound
// LiveActor::initShadowControllerList
// LiveActor::initActorCollisionParts

void LiveActor::initStageSwitch(const JMapInfoIter &rIter) {
    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

// LiveActor::initActorStarPointerTarget
// LiveActor::initActorLightCtrl

void LiveActor::attackSensor(HitSensor *, HitSensor *) {
    
}

// LiveActor::updateBinder
