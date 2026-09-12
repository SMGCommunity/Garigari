#include "Ride/TubeSlider.hpp"
#include "Ride/TubeSliderFunction.hpp"

#include "LiveActor/Nerve.hpp"
#include "Util/ActionSoundUtil.hpp"
#include "Util/ActorAnimUtil.hpp"
#include "Util/ActorCameraUtil.hpp"
#include "Util/ActorSensorUtil.hpp"
#include "Util/ActorShadowUtil.hpp"
#include "Util/ActorSwitchUtil.hpp"
#include "Util/BgmUtil.hpp"
#include "Util/EffectUtil.hpp"
#include "Util/EventUtil.hpp"
#include "Util/GamePadUtil.hpp"
#include "Util/JMapUtil.hpp"
#include "Util/LiveActorUtil.hpp"
#include "Util/MathUtil.hpp"
#include "Util/ObjUtil.hpp"
#include "Util/PlayerUtil.hpp"
#include "Util/RailUtil.hpp"
#include "Util/SceneUtil.hpp"
#include "Util/SupportPlayUtil.hpp"

namespace {
	f32 one = 1.0f;
	f32 thirty = 30.0f;
	f32 onefifty = 150.0f;

	f32 onehundred = 100.0f;
	f32 twohundred = 200.0f;
}

void TubeSliderInfo::init(f32 f) {
	mRadius = f;
	mPrimaryFloorType = 0;
	mPrimaryFloorAngle = 0.0f;
	mPrimaryFloorWidth = 0.0f;
	mSecondaryFloorType = 0;
	mSecondaryFloorAngle = 0.0f;
	mSecondaryFloorWidth = 0.0f;
}

bool TubeSliderInfo::hasWall(bool s) const { // TRUE for Left side, FALSE for right side.
	if ((mSecondaryFloorType == 0x32) || (s && mSecondaryFloorType == 0x33) || (!s && mSecondaryFloorType == 0x34))
		return true;
	return false;
}

namespace NrvTubeSlider {
	NERVE(TubeSliderNrvWait, TubeSlider, Wait);
	NERVE(TubeSliderNrvEnd, TubeSlider, End);
	NERVE(TubeSliderNrvRideJump, TubeSlider, RideAir);
	NERVE(TubeSliderNrvRideSpin, TubeSlider, RideAir);
	NERVE(TubeSliderNrvRideFall, TubeSlider, RideAir);
	NERVE(TubeSliderNrvRide, TubeSlider, Ride);
	NERVE(TubeSliderNrvRideWallHit, TubeSlider, RideWallHit);
	NERVE(TubeSliderNrvRideLand, TubeSlider, RideLand);
	NERVE(TubeSliderNrvRideDamage, TubeSlider, RideAir);
	NERVE(TubeSliderNrvRideDamageLand, TubeSlider, RideLand);
	NERVE(TubeSliderNrvRideDamageDeath, TubeSlider, DamageDeath);
	NERVE(TubeSliderNrvRideSlamCeiling, TubeSlider, RideSlam);
	NERVE(TubeSliderNrvRideSlamWall, TubeSlider, RideSlam);
}

TubeSlider::TubeSlider(const char* pName) : LiveActor(pName) {
	_90 = nullptr;
	_94 = 0.0f;
	_98.set(0.0f, 0.0f, 1.0f);
	_A4.set(0.0f, 1.0f, 0.0f);
	_E0 = 0.0f;
	mCameraInfo = nullptr;
	mPlayerTheta = 0.0f;
	_EC = 0.0f;
	_F0 = 0.0f;
	_F4 = 0.0f;
	_F8 = 4.0f;
	_FC = 0.0f;
	_100.set(0.0f, 0.0f, 0.0f);
	_10C.set(0.0f, 0.0f, 0.0f);
	_118 = 0;
	_11C = 0.0f;
	_120 = 0;
	mInfo.init(500.0f);
	mRadiusDefault = 500.0f;
	mFloorCodeDefault = 0;
	_148.set(0.0f, 0.0f, 0.0f);
	mShadowDropPos.set(0.0f, 0.0f, 0.0f);
	mShadowDropDir.set(0.0f, 1.0f, 0.0f);
	_16C.set(0.0f, 0.0f, 0.0f);
	_178.set(0.0f, 0.0f, 0.0f);
	_184.set(0.0f, 0.0f, 1.0f);
	_190.set(0.0f, 1.0f, 0.0f);
	_19C = 150.0f;
	_1A0 = &thirty;
	_1A4 = &onefifty;
	_1A8 = false;
	_B0.identity();
}

void TubeSlider::init(const JMapInfoIter& rIter) {
	MR::getJMapInfoArg0NoInit(rIter, &mRadiusDefault);
	MR::getJMapInfoArg1NoInit(rIter, &mFloorCodeDefault);
	s32 arg6 = -1;
	MR::getJMapInfoArg6NoInit(rIter, &arg6);
	if (arg6 == 1) {
		_1A0 = &onehundred;
		_1A4 = &twohundred;
	}
	initRailRider(rIter);
	MR::connectToScene(this, 0x28, -1, -1, -1);
	initSound(8, "Tubeslider", nullptr, TVec3f(0.0f));
	initNerve(&NrvTubeSlider::TubeSliderNrvWait::sInstance, 0);
	MR::initAndSetRailClipping(&_148, this, 100.0f, 500.0f);
	MR::calcRailStartPointPos(&mPosition, this);
	initHitSensor(2);
	MR::addHitSensorCallbackBinder(this, "Bind", 8, 50.0f);
	MR::addHitSensorMtxRide(this, "Ride", 8, 50.0f, _B0, TVec3f(0.0f, 50.0f, 0.0f));
	MR::initUseStageSwitchWriteA(this, rIter);
	MR::initMultiActorCamera(this, rIter, &mCameraInfo, "滑り");
	MR::initActorCameraProgrammable(this);
	MR::initShadowVolumeCylinder(this, 40.0f);
	MR::setShadowDropPositionPtr(this, nullptr, &mShadowDropPos);
	MR::setShadowDropDirectionPtr(this, nullptr, &mShadowDropDir);
	TubeSliderFunction::initChildObjs(this, rIter);
	makeActorAppeared();
}

void TubeSlider::tryCalcInfo(TVec3f* a, TVec3f* b, f32* c, TubeSlider* slider, bool check) {
	f32 flt = MR::getRailCoord(slider);
	MR::moveCoordAndTransToNearestRailPos(slider, *MR::getPlayerCenterPos());
	TubeSliderFunction::updateTubeSliderInfo(slider, true);
	if (a != nullptr)
		a->set(MR::getRailPos(slider));
	if (b != nullptr) {
		b->set(MR::getPlayerCenterPos()->subInline(MR::getRailPos(slider)));
		MR::vecKillElement(*b, MR::getRailDirection(slider), b);
		MR::normalizeOrZero(b);
	}
	if (c != nullptr)
		*c = TubeSliderFunction::getRadius(slider);

	if (!check) {
		MR::setRailCoord(slider, flt);
		TubeSliderFunction::updateTubeSliderInfo(slider, true);
	}
}

void TubeSlider::exeWait() {
	if (MR::isFirstStep(this))
		MR::validateClipping(this);
}

void TubeSlider::exeEnd() {
	if (MR::isStep(this, 15) || MR::isOnGroundPlayer())
		setNerve(&NrvTubeSlider::TubeSliderNrvWait::sInstance);
}

void TubeSlider::exeRideAir() {
	if (MR::isFirstStep(this))
		_118 = 0;

	bool isReachedGoal = MR::isRailReachedNearGoal(this, 50.0f);
	if (!isReachedGoal) {
		TVec3f railEndPos(0.0f);
		MR::calcRailEndPos(&railEndPos, this);
		f32 distToEnd = PSVECDistance(railEndPos, MR::getPlayerCenterPos());
		TVec3f* center = MR::getPlayerCenterPos();
		f32 distToRailPos = PSVECDistance(MR::getRailPos(this), center);
		if (distToEnd <= distToRailPos)
			isReachedGoal = true;
	}

	if (isReachedGoal) {
		// Missing function here

		MR::endActorCameraProgrammable(this, -1, true);
		MR::endBindAndPlayerJump(this, _10C, 0);
		MR::invalidateShadow(this, nullptr);
		if (MR::isValidSwitchA(this))
			MR::offSwitchA(this);
		MR::tryDeleteEffect(_90, "共通スリップ坂");
		_90 = nullptr;
		MR::resetSupportTicoAttachRangeTubeSlider();
		setNerve(&NrvTubeSlider::TubeSliderNrvEnd::sInstance);

		if (isReachedGoal && !_1A8) {
			if (MR::isEqualStageName("BigTree2Galaxy")) {
				if (MR::getCurrentScenarioNo() == 3) {
					if (MR::isPurpleCoinNum100()) {
						MR::startLevelSoundPlayer("JumpObj", -1, -1);
						MR::startSubBGM("BGM_RACE_WIN", false);
					}
					else {
						MR::startSubBGM("BGM_RACE_LOSE", false);
					}
				}
				else {
					MR::startLevelSoundPlayer("JumpObj", -1, -1);
					MR::startSubBGM("BGM_RACE_WIN", false);
				}
			}

			_1A8 = true;
			return;
		}
	}
	else {
		MR::startActionSound(this, "Wind", (s32)_E0, MR::clamp(0 + 600, 0, (s32)1000), -1); // TODO: There's a LOT of missing math here...

		if (isNerve(&NrvTubeSlider::TubeSliderNrvRideFall::sInstance) && MR::isLessEqualStep(this, 10) && tryPlayerJump(false))
			return;

		if (_118 > 0)
			_118--;

		if (MR::testCorePadTriggerA(0))
			_118 = 5;

		TVec3f fro(1.0f, 0.0f, 0.0f);
		TVec3f up(_98);
		MR::makeAxisUpFront(&fro, &up, _A4, up);

		if (isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance)) {
			_10C.scale(0.98f);
		}
		else {
			_10C.scale(0.995f);
		}
		TVec3f unk(0.0f, 1.0f, 0.0f);
		TubeSlider::tryCalcInfo(nullptr, &unk, nullptr, this, false);
		if (unk.dot(_A4) < 0.0f) {
			MR::turnVecToVecDegree(&_A4, _A4, -unk, 0.85f, TVec3f((int)0, (int)1, (int)0));
		}
		if (MR::getSubPadStickX(0) != 0.0f) {
			if (isNerve(&NrvTubeSlider::TubeSliderNrvRideSpin::sInstance)) {
				_10C.sub(fro.scaleInline(MR::getSubPadStickX(0)).scaleInline(0.2f));
			}
			else if (isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance)) {
				_10C.sub(fro.scaleInline(MR::getSubPadStickX(0)).scaleInline(0.3f));
			}
			else {
				_10C.sub(fro.scaleInline(MR::getSubPadStickX(0)).scaleInline(0.03f));
			}
		}
		_10C.sub(_A4.scaleInline(0.88f));
		_100.add(_10C);
		_B0.setXYZDir(fro, _A4, up);
		TVec3f igh(_98);
		if (MR::isGreaterEqualStep(this, 10)) {
			TubeSlider::tryCalcInfo(nullptr, nullptr, nullptr, this, true);
			igh.set(MR::getRailDirection(this));
		}

		updateCameraAndShadow(MR::getRailDirection(this));

		if (!isNerve(&NrvTubeSlider::TubeSliderNrvRideSpin::sInstance) && !isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance) && _10C.dot(_A4) < 0.0f && tryPlayerSpin())
			return;

		if (MR::isGreaterStep(this, 120))
			MR::forceKillPlayerByAbyss();
	}
}

void TubeSlider::exeRide() {
	if (MR::isFirstStep(this))
		MR::startBckPlayerJ("チューブスライダー");
	updateOnGround();
}

void TubeSlider::exeRideWallHit() {
	if (MR::isFirstStep(this)) {
		MR::startLevelSoundPlayer("WallHitSlider", -1, -1);
		MR::startBckPlayerJ("チューブスライダー壁ヒット");
	}
	if (!updateOnGround() && MR::isActionEnd(_90))
		setNerve(&NrvTubeSlider::TubeSliderNrvRide::sInstance);
}

void TubeSlider::exeRideLand() {
	if (MR::isFirstStep(this)) {
		if (isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance)) {
			MR::startBckPlayerJ("チューブスライダーダメージ着地");
			MR::startLevelSoundPlayer("SliderDamageLand", -1, -1);
		}
		else {
			MR::startBckPlayerJ("チューブスライダー着地");
			if (TubeSliderFunction::isGroundIce(this)) {
				MR::startLevelSoundPlayer("LandSkate", -1, -1);
			}
			else {
				MR::startLevelSoundPlayer("Land", -1, -1);
			}
		}
		MR::emitEffect(_90, "共通スリップ坂");
	}

	bool isDamaging = isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance);
	if (isDamaging && MR::isStep(this, 40)) {
		MR::startLevelSoundPlayer("SliderDamageLand2nd", -1, -1);
	}

	if (tryPlayerJump(true)) {
		if (isDamaging) {
			// TODO: MISSING FUNCTION
			return;
		}
	}

	if (updateOnGround()) {
		if (isDamaging) {
			// TODO: MISSING FUNCTION
			return;
		}
	}

	if (MR::isActionEnd(_90)) {
		if (isDamaging) {
			// TODO: MISSING FUNCTION
		}
	}

	setNerve(&NrvTubeSlider::TubeSliderNrvRide::sInstance);
}

void TubeSlider::exeDamageDeath() {
	if (MR::isFirstStep(this))
		MR::startBckPlayerJ("チューブスライダーダメージ着地");
}

void TubeSlider::exeRideSlam() {
	if (MR::isFirstStep(this) && isNerve(&NrvTubeSlider::TubeSliderNrvRideSlamWall::sInstance)) {
		MR::startBckPlayerJ("壁ヒット");
	}

	_10C.sub(_A4.scaleInline(0.88f));
	_100.add(_10C);

	TVec3f front(1.0f, 0.0f, 0.0f);
	TVec3f up(_98);
	MR::makeAxisUpFront(&front, &up, _A4, up);
	_B0.setXYZDir(front, _A4, up);
	_B0.setTrans(_100);
	updateCameraAndShadow(_98);

	if (MR::isGreaterStep(this, 120))
		MR::forceKillPlayerByAbyss();
}

void TubeSlider::updateHitSensor(HitSensor* sensor) {
	if (!_90 || (
		isNerve(&NrvTubeSlider::TubeSliderNrvRideJump::sInstance) ||
		isNerve(&NrvTubeSlider::TubeSliderNrvRideSpin::sInstance) ||
		isNerve(&NrvTubeSlider::TubeSliderNrvRideFall::sInstance) ||
		isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance))) {
		TVec3f A(0.0f);
		TVec3f B(0.0f);
		f32 C = 0.0f;
		TubeSlider::tryCalcInfo(&A, &B, &C, this, false);
		B.scale(C + MR::getSensorRadius(sensor));
		A.add(B);
		MR::setSensorPos(sensor, A);
	}
}

void TubeSlider::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
	if (!_90)
		return;

	if (MR::isSensorBinder(pSender) && (
		isNerve(&NrvTubeSlider::TubeSliderNrvRideJump::sInstance) ||
		isNerve(&NrvTubeSlider::TubeSliderNrvRideSpin::sInstance) ||
		(isNerve(&NrvTubeSlider::TubeSliderNrvRideFall::sInstance) && MR::isGreaterEqualStep(this, 5)) ||
		isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance)
		) && MR::isSensorPlayer(pReceiver)) {
		const TVec3f* senderPos = MR::getSensorPos(pSender);
		const TVec3f* receiverPos = MR::getSensorPos(pReceiver);
		TVec3f scratch(*receiverPos);
		scratch.sub(*senderPos);
		TVec3f scratch2(0.0f);
		TubeSlider::tryCalcInfo(nullptr, &scratch2, nullptr, this, true);
		scratch2.scale(-1.0f);
		f32 dotA = scratch.dot(scratch2);
		f32 dotB = _10C.dot(scratch2);

		if (dotB < 0.0f && !(dotA >= 50.0f) && isOffSlide()) {
			MR::tryRumblePadMiddle(this, 0);
			MR::shakeCameraNormal();
			if (MR::isPlayerDead())
				setNerve(&NrvTubeSlider::TubeSliderNrvRideDamageDeath::sInstance);
			else if (isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance))
				setNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance);
			else {
				// Missing mario function
				setNerve(&NrvTubeSlider::TubeSliderNrvRideLand::sInstance);
			}

			return;
		}

		if (TubeSliderFunction::isUnknown2(this))
		   return;

		if (dotB > 0.0f && dotA < -50.0f && dotA < -30.0f) {
			MR::tryRumblePadMiddle(this, 0);
			MR::shakeCameraNormal();
			_10C.sub(scratch2.scaleInline(dotB).scaleInline(1.0f + 0.6f));
			// Missing mario function
			setNerve(&NrvTubeSlider::TubeSliderNrvRideSlamCeiling::sInstance);
			return;
		}
		if (dotA >= -30.0f && dotA < 50.0f) {
			MR::tryRumblePadMiddle(this, 0);
			MR::shakeCameraNormal();
			_10C.sub(_98.scaleInline(_10C.dot(_98)).scaleInline(1.0f + 0.2f));
			// Missing mario function
			setNerve(&NrvTubeSlider::TubeSliderNrvRideSlamWall::sInstance);
			return;
		}
	}
	else {
		if (MR::tryGetItem(pSender, pReceiver))
			return;
	}
}

bool TubeSlider::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
	if (MR::isMsgPlayerHipDrop(msg)) {
		MR::sendMsgAwayJump(pSender, pReceiver);
		return true;
	}
	return false;
}

bool TubeSlider::receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
	if (!_90)
		return false;

	if (!isNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance) && !isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance) && !isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageDeath::sInstance)) {
		startDamage();
		return true;
	}
	return false;
}

bool TubeSlider::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
	if (MR::isMsgAutoRushBegin(msg)) {
		if (isNerve(&NrvTubeSlider::TubeSliderNrvEnd::sInstance) || MR::isOnGroundPlayer())
			return false;
		_90 = MR::getSensorHost(pSender);
		MR::invalidateClipping(this);
		if (!isOffSlide()) {
			MR::validateClipping(this);
			_90 = nullptr;
			return false;
		}
		MR::tryRumblePadMiddle(this, 0);
		if (MR::isValidSwitchA(this))
			MR::onSwitchA(this);
		MR::startActorCameraProgrammable(this, -1);
		_184.set(_98);
		_190.set(_A4);
		_120 = 0;
		_11C = 0.0f;
		MR::tryRumblePadMiddle(this, 0);
		MR::shakeCameraNormal();
		MR::setSupportTicoAttachRangeTubeSlider();
		MR::validateShadow(this, nullptr);
		setNerve(&NrvTubeSlider::TubeSliderNrvRideLand::sInstance);
		return true;
	}
	if (MR::isMsgUpdateBaseMtx(msg)) {
		_120++;
		MR::setBaseTRMtx(_90, _B0);
		return true;
	}
	if (MR::isMsgRushCancel(msg)) {
		MR::endActorCameraProgrammable(this, -1, true);
		if (MR::isValidSwitchA(this))
			MR::offSwitchA(this);
		MR::tryDeleteEffect(_90, "共通スリップ坂");
		_90 = nullptr;
		MR::resetSupportTicoAttachRangeTubeSlider();
		setNerve(&NrvTubeSlider::TubeSliderNrvEnd::sInstance);
		return true;
	}
	return false;
}

bool TubeSlider::isOffSlide() {
	TVec3f temp;
	TubeSlider::tryCalcInfo(nullptr, &temp, nullptr, this, true);
	TVec3f temp2;
	TubeSliderFunction::getRailUpVec(&temp2, this);
	_94 = MR::getRailCoord(this);
	mPlayerTheta = MR::diffAngleSigned(temp2, temp, MR::getRailDirection(this)) * 57.29578f;
	if (TubeSliderFunction::isUnknown2(this) && !TubeSliderFunction::isHitLeftWall(this, &mPlayerTheta) && !TubeSliderFunction::isHitRightWall(this, &mPlayerTheta)) {
		return false;
	}

	_98.set(MR::getRailDirection(this));
	_A4.set(-temp);
	MR::repeatDegree(&mPlayerTheta);
	MR::setRailDirectionToEnd(this);
	_E0 = MR::getPlayerVelocity()->dot(MR::getRailDirection(this));
	_E0 = MR::clamp(_E0, 20.0f, 45.0f);
	_EC = 0.0f;
	_F4 = 0.0f;
	_FC = 0.0f;
	_19C = *_1A4;
	updateMarioPos();
	return true;
}

bool TubeSlider::tryEndSlide() {
	if (!MR::isRailReachedGoal(this))
		return false;

	MR::moveCoordToEndPos(this);
	TVec3f vec;
	_B0.getTrans(vec);
	MR::setPlayerPos(vec);
	TVec3f vec2;
	_B0.setZDirInline(vec2);
	MR::setPlayerFrontTargetVec(vec2, 1);
	TVec3f vec3(vec2);
	vec3.scale(20.0f);
	vec3.add(TVec3f(0.0f, 1.0f, 0.0f).scaleInline(10.0f));
	MR::startBckPlayerJ("チューブスライダージャンプ");
	// Unknown mario function here
	MR::endActorCameraProgrammable(this, -1, true);
	MR::endBindAndPlayerForceWeakGravityJumpInputOff(this, vec3);
	MR::invalidateShadow(this, nullptr);
	if (MR::isValidSwitchA(this))
		MR::offSwitchA(this);
	MR::tryDeleteEffect(_90, "共通スリップ坂");
	_90 = nullptr;
	MR::resetSupportTicoAttachRangeTubeSlider();
	setNerve(&NrvTubeSlider::TubeSliderNrvEnd::sInstance);
	return true;
}

bool TubeSlider::tryPlayerJump(bool b) {
	if ((!b && MR::testCorePadTriggerA(0)) || (b && _118 > 0)) {
		if (TubeSliderFunction::isGroundIce(this))
			MR::startLevelSoundPlayer("JumpSkate", -1, -1);
		else
			MR::startLevelSoundPlayer("JumpS", -1, -1);
		MR::tryDeleteEffect(_90, "共通スリップ坂");
		startJump(25.0f);
		MR::startBckPlayerJ("チューブスライダージャンプ");
		setNerve(&NrvTubeSlider::TubeSliderNrvRideJump::sInstance);
		return true;
	}

	return false;
}

bool TubeSlider::tryPlayerSpin() {
	if (MR::isPadSwing(0)) {
		MR::startLevelSoundPlayer("JumpSpin", -1, -1);
		MR::tryRumblePadMiddle(this, 0);
		MR::vecKillElement(_10C, _A4, &_10C);
		_10C.add(_A4.scaleInline(22.0f));
		MR::startBckPlayer("Spin", nullptr);
		MR::emitEffect(_90, "SliderSpinLight");
		setNerve(&NrvTubeSlider::TubeSliderNrvRideSpin::sInstance);
		return true;
	}
	return false;
}

bool TubeSlider::tryPlayerFall() {
	if (TubeSliderFunction::isUnknown2(this)) {
		MR::tryDeleteEffect(_90, "共通スリップ坂");
		MR::startBckPlayerJ("落下");
		startJump(0.0f);
		setNerve(&NrvTubeSlider::TubeSliderNrvRideJump::sInstance);
		return true;
	}
	return false;
}

void TubeSlider::startDamage() {
	// Two missing functions here
	MR::tryRumblePadMiddle(this, 0);
	MR::startLevelSoundPlayer("DamageS", -1, -1);
	MR::startBckPlayerJ("チューブスライダーダメージ");
	MR::emitEffect(_90, "TubeSlideDamage");
	MR::tryDeleteEffect(_90, "共通スリップ坂");
	startJump(25.0f);
	setNerve(&NrvTubeSlider::TubeSliderNrvRideDamage::sInstance);
}

void TubeSlider::startJump(f32 power) {
	TVec3f a(1.0f, 0.0f, 0.0f);
	TVec3f b(_98);
	MR::makeAxisUpFront(&a, &b, _A4, b);
	_100.set(*MR::getPlayerPos());
	_10C.set(_98.scaleInline(_E0).addInline(_A4.scaleInline(power)).subInline(a.scaleInline(_EC).scaleInline(2.0f)));
}

bool TubeSlider::updateOnGround() {
	if (updatePlayer())
		return true;

	if (tryPlayerFall())
		return true;

	if (TubeSliderFunction::isGroundDamage(this) && !isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance)) {
		startDamage();
		return true;
	}

	if (tryPlayerJump(false)) {
		return true;
	}

	// Too much math...

	if (isNerve(&NrvTubeSlider::TubeSliderNrvRide::sInstance) || isNerve(&NrvTubeSlider::TubeSliderNrvRideLand::sInstance)) {
		// MORE MATH
	}

	// ActionSound I can't interpret

	if (TubeSliderFunction::isGroundWood(this)) {
		//MR::startActionSound "SlipWood"
		return false;
	}

	if (TubeSliderFunction::isGroundIce(this)) {
		//MR::startActionSound "SlipIce"
		return false;
	}

	if (TubeSliderFunction::isGroundNormal(this)) {
		TubeSliderFunction::isGroundNormal2(this);
		//MR::startActionSound "SlipNormal"
		return false;
	}
}

bool TubeSlider::updatePlayer() {
	TVec3f railDir(MR::getRailDirection(this));
	_E0 += 1.0f;
	if (isNerve(&NrvTubeSlider::TubeSliderNrvRide::sInstance)) {
		if (TubeSliderFunction::isGroundSlow(this)) {
			_E0 *= 0.95f;
		}
		else if (TubeSliderFunction::isGroundIce(this)) {
			_E0 *= 0.995f;
		}
		else {
			_E0 *= 0.99f;
		}
	}
	else if (isNerve(&NrvTubeSlider::TubeSliderNrvRideDamageLand::sInstance)) {
		_E0 *= 0.95f;
	}
	else {
		_E0 *= one;
	}
	_E0 = MR::clamp(_E0, 20.0f, 45.0f);
	MR::moveCoordAndFollowTrans(this, _E0);
	TubeSliderFunction::updateTubeSliderInfo(this, true);
	TVec3f front(1.0f, 0.0f, 0.0f);
	TVec3f cross;
	PSVECCrossProduct(front, _A4, &cross);
	MR::normalizeOrZero(&cross);
	_EC -= cross.dot(MR::getRailDirection(this)) * 7.0f;
	TVec3f vec(0.0f);
	_B0.getTrans(vec);
	TVec3f vec2(0.0f);
	TVec3f vec3(_A4);
	if (!TubeSliderFunction::isUnknown2(this)) {
		TVec3f upVec(0.0f, 1.0f, 0.0f);
		TubeSliderFunction::getRailUpVec(&upVec, this);
		TPos3f mtx;
		mtx.identity();
		f32 rot = (180.0f + _E0) * 0.017453292f;
		mtx.setRotate(-MR::getRailDirection(this), rot);
		mtx.mult(upVec, upVec);
		MR::turnVecToVecDegree(&vec3, vec3, upVec, 10.0f, TVec3f((int)0, (int)1, (int)0));
	}
	vec2.set(mPosition.subInline(vec3.scaleInline(TubeSliderFunction::getRadius(this) - _F4 - _F8)));
	_11C += _E0 - vec2.subInline(vec).dot(cross);
	MR::turnVecToVecDegree(&_98, _98, MR::getRailDirection(this), 1.0f, TVec3f((int)0, (int)1, (int)0));
	if (!TubeSliderFunction::isUnknown2(this) && MR::getSubPadStickX(0)) {
		_EC += (0.215f * MR::getSubPadStickX(0));
		f32 range = 1.45f;
		_EC = MR::clamp(_EC, -range, range);

		if (MR::getSubPadStickX(0) < 0.0f) {
			_F0 = MR::getInterpolateValue(0.3f, _F0, MR::clamp(_EC, -1.0f, 0.0f));
		}
		else if (MR::getSubPadStickX(0) > 0.0f) {
			_F0 = MR::getInterpolateValue(0.3f, _F0, MR::clamp(_EC, 0.0f, 1.0f));
		}
	}
	else {
		mPlayerTheta += _EC;
		_F0 = MR::getInterpolateValue(0.3f, _F0, 0.0f);
	}

	if (isNerve(&NrvTubeSlider::TubeSliderNrvRide::sInstance)) {
		f32 one = 1.0f;
		one *= _F0;
		f32 clamp = MR::clamp(one, -1.0f, 1.0f);
		if (clamp > 0.0f) {
			MR::setBckBlendWeight(1.0f - clamp, 0.0f, clamp);
		}
		else {
			MR::setBckBlendWeight(1.0f + clamp, -clamp, 0.0f);
		}
	}

	bool hasHitWall = false;
	f32 two = 2.0f;
	if (_EC <= 0.0f) {
		bool missingfunc;
		if (missingfunc) {
			_EC = two;
			mPlayerTheta += two;
			MR::repeatDegree(&mPlayerTheta);
			_E0 *= 0.2f;
			MR::tryRumblePadMiddle(this, 0);
			if (_F4 <= 0.0f) {
				hasHitWall = true;
				MR::emitEffect(_90, "SliderWallHitL");
				setNerve(&NrvTubeSlider::TubeSliderNrvRideWallHit::sInstance);
			}
		}
	}
	if (_EC >= 0.0f) {
		bool missingfunc;
		if (missingfunc) {
			_EC = -two;
			mPlayerTheta += -two;
			MR::repeatDegree(&mPlayerTheta);
			_E0 *= 0.2f;
			MR::tryRumblePadMiddle(this, 0);
			if (_F4 <= 0.0f) {
				hasHitWall = true;
				MR::emitEffect(_90, "SliderWallHitR");
				setNerve(&NrvTubeSlider::TubeSliderNrvRideWallHit::sInstance);
			}
		}
	}

	updateMarioPos();

	// Sound code here that I can't figure out :(

	if (hasHitWall) {
		return true;
	}

	if (tryEndSlide()) {
		if (!_1A8) {
			if (MR::isEqualStageName("BigTree2Galaxy")) {
				if (MR::getCurrentScenarioNo() == 3) {
					if (MR::isPurpleCoinNum100()) {
						MR::startLevelSoundPlayer("JumpObj", -1, -1);
						MR::startSubBGM("BGM_RACE_WIN", false);
					}
					else {
						MR::startSubBGM("BGM_RACE_LOSE", false);
					}
				}
				else {
					MR::startLevelSoundPlayer("JumpObj", -1, -1);
					MR::startSubBGM("BGM_RACE_WIN", false);
				}
			}
			_1A8 = true;
		}
		return true;
	}

	return false;
}

void TubeSlider::updateMarioPos() {
	MR::repeatDegree(&mPlayerTheta);
	TPos3f pos;
	pos.identity();
	f32 rot = (180.0f + mPlayerTheta) * 0.017453292f;
	pos.setRotate(-MR::getRailDirection(this), rot);

	if (!TubeSliderFunction::isUnknown2(this)) {
		TVec3f railup(0.0f, 1.0f, 0.0f);
		TubeSliderFunction::getRailUpVec(&railup, this);
		pos.mult(railup, railup);
		MR::turnVecToVecDegree(&_A4, _A4, railup, 10.0f, TVec3f((int)0, (int)1, (int)0));
	}
	TVec3f translation(0.0f);
	_B0.getTrans(translation);
	TVec3f front(1.0f, 0.0f, 0.0f);
	TVec3f up(_98);
	MR::makeAxisUpFront(&front, &up, _A4, up);
	_B0.setXYZDir(front, _A4, up);
	_F8 = MR::lerp(_F8, 0.0f, 0.5f); // The 0.0f isn't real?
	_B0.setTrans(mPosition.subInline(_A4.scaleInline(TubeSliderFunction::getRadius(this) - _F4 - _F8)));
	updateCameraAndShadow(MR::getRailDirection(this));
}

void TubeSlider::updateCameraAndShadow(const TVec3f& rDir) {
	mShadowDropDir.set(-_A4);
	_B0.getTrans(mShadowDropPos);
	mShadowDropPos.add(_A4.scaleInline(10.0f));
	MR::turnVecToVecDegree(&_184, _184, rDir, 0.85f, TVec3f((int)0, (int)1, (int)0));
	MR::vecBlend(_190, _190, &_A4, 0.03f);
	_19C = MR::lerp(_19C, *_1A4, 0.03f);
	_178 = MR::getPlayerPos()->addInline(_190.scaleInline(_19C));
	_16C = _178.subInline(_184.scaleInline(550.0f)).addInline(_190.scaleInline(*_1A0));
	f32 railCoord = MR::getRailCoord(this);
	MR::moveCoordAndTransToNearestRailPos(this, _16C);
	f32 rad = TubeSliderFunction::getRadius(this) - 100.0f;
	if (PSVECDistance(mPosition, _16C) > rad) {
		_16C.sub(mPosition);
		MR::normalize(&_16C);
		_16C.scale(rad);
		_16C.add(mPosition);
	}
	TubeSliderFunction::updateTubeSliderInfo(this, true);
	MR::setRailCoord(this, railCoord);
	TubeSliderFunction::updateTubeSliderInfo(this, true);
	MR::setProgrammableCameraParam(this, _178, _16C,_190);
}