#pragma once

#include "LiveActor/LiveActor.hpp"

class DummyDisplayModel;
class BreakModel;

class TubeSliderCrystal : public LiveActor {
public:
	TubeSliderCrystal(const TVec3f& vec);

	virtual void init(const JMapInfoIter&);
	virtual void calcAndSetBaseMtx();
	virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);

	void exeWait();
	void exeBreak();

	TVec3f _90;
	DummyDisplayModel* mDisplayModel; // 0x9C
	BreakModel* mBreakModel; // 0xA0
};