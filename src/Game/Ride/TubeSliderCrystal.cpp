#include "Ride/TubeSliderCrystal.hpp"

#include "LiveActor/Nerve.hpp"
#include "LiveActor/BreakModel.hpp"
#include "MapObj/DummyDisplayModel.hpp"
#include "Util/ActorInitUtil.hpp"
#include "Util/ActorMovementUtil.hpp"
#include "Util/ActorSensorUtil.hpp"
#include "Util/EventUtil.hpp"
#include "Util/LiveActorUtil.hpp"


namespace NrvTubeSliderCrystal {
	NERVE(TubeSliderCrystalNrvWait, TubeSliderCrystal, Wait);
	NERVE(TubeSliderCrystalNrvBreak, TubeSliderCrystal, Break);
}

TubeSliderCrystal::TubeSliderCrystal(const TVec3f& vec) : LiveActor("クリスタル（チューブスライダー用）"){
	_90.setPS(vec);
	mDisplayModel = nullptr;
	mBreakModel = nullptr;
}

void TubeSliderCrystal::init(const JMapInfoIter& rIter) {
	MR::initActor(this, rIter, "TubeSliderCrystal", false);
	initNerve(&NrvTubeSliderCrystal::TubeSliderCrystalNrvWait::sInstance, 0);
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
	if (isNerve(&NrvTubeSliderCrystal::TubeSliderCrystalNrvWait::sInstance) && MR::isSensorRide(pReceiver))
		setNerve(&NrvTubeSliderCrystal::TubeSliderCrystalNrvBreak::sInstance);
}