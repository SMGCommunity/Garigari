#include "Game/Ride/TubeSliderCrystal.hpp"

#include "Game/LiveActor/BreakModel.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/DummyDisplayModel.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvTubeSliderCrystal {
    NEW_NERVE(TubeSliderCrystalNrvWait, TubeSliderCrystal, Wait);
    NEW_NERVE(TubeSliderCrystalNrvBreak, TubeSliderCrystal, Break);
}  // namespace NrvTubeSliderCrystal

TubeSliderCrystal::TubeSliderCrystal(const TVec3f& vec) : LiveActor("クリスタル（チューブスライダー用）") {
    _90.setPS(vec);
    mDisplayModel = nullptr;
    mBreakModel = nullptr;
}

void TubeSliderCrystal::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "TubeSliderCrystal", false);
    initNerve(GET_NERVE(TubeSliderCrystal, TubeSliderCrystalNrvWait), 0);
    mDisplayModel = MR::createDummyDisplayModelCrystalItem(this, 4, TVec3f(0.0f, 0.0f, 0.0f), TVec3f(0.0f, 0.0f, 0.0f));
    mBreakModel = MR::createBreakModel(this, nullptr);
    makeActorAppeared();
}

void TubeSliderCrystal::calcAndSetBaseMtx() {
    MR::calcAndSetBaseTRMtxFromGravityAndZAxis(this, _90);
}

void TubeSliderCrystal::exeWait() {
    if (MR::isFirstStep(this)) {
    }
}
void TubeSliderCrystal::exeBreak() {
    if (MR::isFirstStep(this)) {
        MR::addStarPiece(8);
        mBreakModel->appear();
        kill();
    }
}

void TubeSliderCrystal::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (isNerve(GET_NERVE(TubeSliderCrystal, TubeSliderCrystalNrvWait)) && MR::isSensorRide(pReceiver))
        setNerve(GET_NERVE(TubeSliderCrystal, TubeSliderCrystalNrvBreak));
}
