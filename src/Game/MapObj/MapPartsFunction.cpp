#include "Game/MapObj/MapPartsFunction.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Spine.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "revolution/types.h"

MapPartsFunction::MapPartsFunction(LiveActor* pHost, const char* pName)
    : NameObj(pName != nullptr ? pName : "マップパーツ機能"), mSpine(), mHost(pHost), mIsActive(true), mSpeed(1.0f), mHostSensorName("Body") {
}

void MapPartsFunction::init(const JMapInfoIter& rIter) {
    MR::useStageSwitchReadParam(mHost, rIter);
    MR::getJMapInfoParamScale(rIter, &mSpeed);
}

void MapPartsFunction::movement() {
    if (mIsActive) {
        mSpine->update();
        control();
    }
}

void MapPartsFunction::resetHostSensorName() {
    mHostSensorName = nullptr;
}

void MapPartsFunction::initNerve(const Nerve* pNerve) {
    mSpine = new Spine(this, pNerve);
}

void MapPartsFunction::setNerve(const Nerve* pNerve) {
    mSpine->setNerve(pNerve);
}

s32 MapPartsFunction::getStep() const {
    return mSpine->mStep;
}

bool MapPartsFunction::isStep(s32 step) const {
    return step == mSpine->mStep;
}

bool MapPartsFunction::isNerve(const Nerve* pNerve) const {
    return mSpine->getCurrentNerve() == pNerve;
}

bool MapPartsFunction::isFirstStep() const {
    return mSpine->mStep == 0;
}

bool MapPartsFunction::sendMsgToHost(u32 msg) {
    if (mHostSensorName == nullptr) {
        return false;
    }

    if (MR::getSensorNum(mHost) <= 0) {
        return false;
    }

    LiveActor* host = mHost;
    return host->receiveMessage(msg, host->getSensor(mHostSensorName), host->getSensor(mHostSensorName));
}

f32 MapPartsFunction::getSpeed() const {
    if (MR::isValidSwitchParam(mHost) && MR::isOnSwitchParam(mHost)) {
        return mSpeed;
    }

    return 1.0f;
}
