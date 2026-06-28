#pragma once

#include "LiveActor/LiveActor.hpp"

class ActorCameraInfo;

struct TubeSliderInfo {
public:
	void init(f32);
	bool hasWall(bool) const;

	f32 mRadius;              // 0x00 | 0x124 : Relative to it's usage in TubeSlider
	s32 mPrimaryFloorType;    // 0x04 | 0x128
	f32 mPrimaryFloorAngle;   // 0x08 | 0x12C
	f32 mPrimaryFloorWidth;   // 0x0C | 0x130
	s32 mSecondaryFloorType;  // 0x10 | 0x134
	f32 mSecondaryFloorAngle; // 0x14 | 0x138
	f32 mSecondaryFloorWidth; // 0x18 | 0x13C

	inline f32 getRadius() const {
		return mRadius;
	}
};

class TubeSlider : public LiveActor {
public:
	TubeSlider(const char*);

	virtual void init(const JMapInfoIter&);
	virtual void updateHitSensor(HitSensor*);
	virtual void attackSensor(HitSensor*, HitSensor*);
	virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
	virtual bool receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
	virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

	static void tryCalcInfo(TVec3f*, TVec3f*, f32*, TubeSlider*, bool);
	bool isOffSlide();
	bool tryEndSlide();

	bool tryPlayerJump(bool);
	bool tryPlayerSpin();
	bool tryPlayerFall();
	void startDamage();
	void startJump(f32 power);
	bool updateOnGround();
	bool updatePlayer();   // updates player movement
	void updateMarioPos(); // Updates specifically mario's visual position along the slide.
	void updateCameraAndShadow(const TVec3f& rDir);

	void exeWait();
	void exeEnd();
	void exeRideAir();
	void exeRide();
	void exeRideWallHit();
	void exeRideLand();
	void exeDamageDeath();
	void exeRideSlam();

	inline f32 getPlayerTheta() const {
		return mPlayerTheta;
	}

	LiveActor* _90; // 0x90
	f32 _94; // 0x94 : mRailCoord?
	TVec3f _98; // 0x98
	TVec3f _A4; // 0xA4
	TPos3f _B0; // 0xB0
	f32 _E0; // 0xE0
	ActorCameraInfo* mCameraInfo; // 0xE4
	f32 mPlayerTheta; // 0xE8 : Represents the angle around the tube that the player should currently be at
	f32 _EC; // 0xEC
	f32 _F0; // 0xF0
	f32 _F4; // 0xF4
	f32 _F8; // 0xF8
	f32 _FC; // 0xFC : seems to never be read from, only written to...
	TVec3f _100; // 0x100
	TVec3f _10C; // 0x10C
	s32 _118; // 0x118
	f32 _11C; // 0x11C
	s32 _120; // 0x120
	TubeSliderInfo mInfo; // 0x124
	f32 mRadiusDefault; // 0x140 : Obj_arg0
	s32 mFloorCodeDefault; // 0x144 : Obj_arg1
	TVec3f _148; // 0x148
	TVec3f mShadowDropPos; // 0x154
	TVec3f mShadowDropDir; // 0x160
	TVec3f _16C; // 0x16C
	TVec3f _178; // 0x178
	TVec3f _184; // 0x184
	TVec3f _190; // 0x190
	f32 _19C; // 0x19C
	f32* _1A0; // 0x1A0
	f32* _1A4; // 0x1A4
	bool _1A8; // 0x1A8
};