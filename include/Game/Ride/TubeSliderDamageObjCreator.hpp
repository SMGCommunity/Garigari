#pragma once

#include "LiveActor/LiveActor.hpp"

class TubeSlider;

class TubeSliderDamageObj : public LiveActor {
public:
	TubeSliderDamageObj(s32 t, const TVec3f& vec);

	virtual void init(const JMapInfoIter&);
	virtual void control();
	virtual void calcAndSetBaseMtx();
	virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
	virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);


	void exeWait();
	void exeShake();
	void exeSupportFreeze();

	s32 mType; // 0 = Spike Plants, 1 = Fire (unused)
	TVec3f _94;
	bool _A0;
	f32 _A4;
};


class TubeSliderDamageObjCreator : public LiveActor {
public:
	TubeSliderDamageObjCreator(TubeSlider*);

	virtual void init(const JMapInfoIter&);

	TubeSlider* mSlider;
};