#pragma once

#include "LiveActor/LiveActor.hpp"

class TubeSlider;

class TubeSliderCoinCreator : public LiveActor {
public:
	TubeSliderCoinCreator(TubeSlider* pSlider, bool isPurple);
	virtual void init(const JMapInfoIter& rIter);

	bool mIsPurpleCoin;
	TubeSlider* mSlider;
};