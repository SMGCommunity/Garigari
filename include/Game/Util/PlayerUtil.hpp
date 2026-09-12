#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class BckCtrlData;
class CameraTargetArg;
class HitSensor;
class LiveActor;
class MarioActor;
class NameObj;
class XanimeResourceTable;

namespace MR {
	bool isOnGroundPlayer();
	void getPlayerGroundingPolygon();
	void forceKillPlayerByAbyss();
	void forceKillPlayerByWaterOrGroundRace();
	void forceKillPlayerByGroundRace();

	bool isPlayerInBind();
	bool isPlayerDead();
	bool isPlayerRefuseTalk();
	bool isPlayerTeresaDisappear();
	bool isPlayerInAreaObj(const char*);
	TVec3f* getPlayerPos();
	TVec3f* getPlayerCenterPos();
	TVec3f* getPlayerTakePos(TVec3f*);
	void setPlayerPos(const TVec3f&);
	void setPlayerUpperRotateY(f32);
	TVec3f* getPlayerRotate();
	TVec3f* getPlayerShadowRotate();
	void copyPlayerTR(LiveActor*);
	TVec3f* getPlayerVelocity();
	TVec3f* getPlayerLastMove();
	void setPlayerJumpVec(const TVec3f&);
	f32 getPlayerHitRadius();

	TVec3f* getPlayerGravity();
	void calcPlayerSpinPullVelocity(TVec3f*, const TVec3f&);
	bool checkPlayerSwingTrigger();
	f32 calcDistanceToPlayer(const TVec3f&);
	void getPlayerUpVec(TVec3f*);
	void getPlayerFrontVec(TVec3f*);
	void getPlayerSideVec(TVec3f*);
	void getPlayerThrowVec(TVec3f*);
	void getPlayerGroundPos(TVec3f*);
	TVec3f* getPlayerGroundNormal();
	void setPlayerFrontTargetVec(const TVec3f&, s32);
	void setPlayerFrontVec(const TVec3f&, s32);
	void setPlayerSwingInhibitTimer(u16);
	void setPlayerSwingPermission(bool);
	void setPlayerStateWait();
	void startBckPlayer(const char*, const char*);
	void startBckPlayer(const char*, const BckCtrlData&);

	bool isBckStoppedPlayer();
	bool isBckOneTimeAndStoppedPlayer();
	f32 getBckFrameMaxPlayer();
	f32 getBckFrameMaxPlayer(const char*);
	void startBckPlayerJ(const char*);
	void becomeContinuousBckPlayer();
	void progressPlayerBckOnPause();
	const char* getPlayerCurrentBckName();
	void setBckBlendWeight(f32, f32);
	void setBckBlendWeight(f32, f32, f32);
	void setBckBlendWeight(f32, f32, f32, f32);
	void setBckRatePlayer(f32);

	XanimeResourceTable* getPlayerXanimeResource();
	void jumpPlayer(const TVec3f&);
	void forceJumpPlayer(const TVec3f&);
	void forceFlyPlayer(const TVec3f&, const TVec3f&, s32);
	void tornadoJumpPlayer();
	void miniTornadoJumpPlayer();

	void becomePlayerNormalJumpStatus();
	bool isOnPlayer(const HitSensor*);
	bool isActorOnPlayer(const LiveActor*);
	bool isOnPlayerShadow(const LiveActor*);
	void setPlayerPos(const char*);
	void setPlayerPosAndWait(const TVec3f&, bool);
	void setPlayerPosAndWait(const char*);
	void setPlayerLinkPosAndWait(const NameObj*, const char*, bool);
	void setPlayerPosOnGround(const char*);
	void setPlayerPosOnGroundAndWait(const char*);
	bool isPlayerHipDropFalling();
	bool isPlayerHipDropLand();
	s32 getPlayerLife();
	bool isPlayerLifeOne();

	void incPlayerLife(u32);
	void incPlayerOxygen(u32);
	bool isPlayerConfrontDeath();
	void getStarPiecePlayer();
	void notifyDirectGetStarPiecePlayer();
	void scatterStarPiecePlayer(u32);

	bool isPlayerSwingAction();

	bool isPlayerPointedBy2POnTriggerButton();
	bool isPlayerSquat();
	bool isPlayerInRush();
	bool isPlayerRecovering();
	bool isPlayerNeedBrakingCamera();

	bool isPlayerFlying();

	bool isPlayerHanging();
	bool isPlayerBury();

	bool isPlayerElementModeTornado();
	bool isPlayerElementModeInvincible();
	bool isPlayerElementModeBee();
	bool isPlayerElementModeHopper();
	bool isPlayerElementModeTeresa();
	bool isPlayerElementModeIce();
	bool isPlayerElementModeFire();
	bool isPlayerElementModeCloud();
	bool isPlayerElementModeRock();
	bool isPlayerElementModeNormal();
	bool isPlayerElementModeYoshi();
	bool isPlayerElementModeYoshiDash();
	bool isPlayerElementModeYoshiLight();
	void changePlayerModeBee();
	void changePlayerModeHopper();
	void changePlayerModeTeresa();
	void changePlayerModeIce();
	void changePlayerModeFire();
	void changePlayerModeYoshi();
	void changePlayerModeCloud();
	void changePlayerModeRock();
	void changePlayerModeFoo();
	void changePlayerModeInvincible();
	void changePlayerItemLifeUp();
	void curePlayerElementMode();
	void startDashYoshiMode();
	void startBalloonYoshiMode();

	bool isPlayerParalyzing();
	bool isPlayerDamaging();

	bool isPlayerStaggering();
	bool isPlayerSwimming();
	bool isPlayerSleeping();
	bool isPlayerJumpRising();
	void endBindAndPlayerWait(LiveActor*);
	void endBindAndPlayerJump(LiveActor*, const TVec3f&, u32);
	void endBindAndPlayerForceJump(LiveActor*, const TVec3f&, u32);
	void endBindAndPlayerWeakGravityJump(LiveActor*, const TVec3f&);
	void endBindAndPlayerForceWeakGravityJump(LiveActor*, const TVec3f&);
	void endBindAndPlayerForceWeakGravityJumpInputOff(LiveActor*, const TVec3f&);
	void endBindAndPlayerWeakGravityLimitJump(LiveActor*, const TVec3f&);
	void endBindAndSpinDriverJump(LiveActor*, const TVec3f&);
	void endBindAndPlayerDamage(LiveActor*, const TVec3f&);
	void endBindAndPlayerFlip(LiveActor*, const TVec3f&);
	void endBindAndPlayerJumpWithRollLanding(LiveActor*, const TVec3f&, u32);
	void endBindAndPlayerDamageMsg(LiveActor*, u32);
	void endBindAndPlayerDamageMsg(LiveActor*, u32, const TVec3f&);
	void endBindAndPlayerAcidDamage(LiveActor*);
	void endBindAndPlayerFreezeDamage(LiveActor*);
	void endBindAndPlayerFireDamage(LiveActor*);
	void endBindAndPlayerElectricDamage(LiveActor*);
	LiveActor* getCurrentRushActor();
	HitSensor* getCurrentRushSensor();
	void tryPlayerCoinPull();
	void tryPlayerPullActor(HitSensor*);
	void tryPlayerDropTakingActor();
	void tryPlayerKillTakingActor();
	bool isPlayerCarrySensorType(u32);
	bool isPlayerCarryAny();
	LiveActor* getPlayerCarrySensorHost();

	void startSoundPlayer(const char*, s32, s32);
	void startLevelSoundPlayer(const char*, s32, s32);
	void startLevelSoundPlayerOrYoshi(const char* pPlayerSoundName, const char* pYoshiSoundName, s32 unk);

	void stopSoundPlayer(const char*, u32);
	void startSoundPlayerJ(const char*);
	void emitEffectPlayer(const char*);
	void deleteEffectPlayer(const char*);
	void showPlayer();
	void hidePlayer();

	void hidePlayerTryDeleteEffect();
	void showPlayerJoint(const char*);
	void hidePlayerJoint(const char*);

	void setPlayerSpot(f32, u32);
	void startPlayerDownWipe();
	void setCameraTargetToPlayer(CameraTargetArg*);
	bool isPlayerDisableFpView();
	bool isFpViewChangingFailure();
	void stopPlayerFpView();
	void startPlayerTalk(const LiveActor*);
	void endPlayerTalk();

	bool isCurrentRushActor(const char*);
	bool isCurrentRushRockMario();
	bool isCurrentRushTamakoro();
	bool isCurrentRushSpinDriver();
	bool isCurrentRushItemDrill();
	bool isExistMario();
	void startPlayerEvent(const char*);
	void offPlayerControl();
	void onPlayerControl(bool);
	bool isOffPlayerControl();
	void unlockPlayerAnimation();
	void resetPlayerStatus();
	void resetPlayerEffect();
	void setPlayerBaseMtx(MtxPtr);

	MtxPtr getPlayerBaseMtx();

	MarioActor* getPlayerDemoActor();

	void calcPlayerJointMtx(MtxPtr, const char*);
	void concatWithPlayerJointMtx(MtxPtr, const char*);

	void pushPlayer(const TVec3f&);
	void pushPlayerFromArea(const TVec3f&);

	bool isPlayerInWaterMode();
	bool isPlayerOnWaterSurface();
	bool isPlayerHidden();
	void calcPlayerWorldPadDir(TVec3f*, f32, f32);

	// getFullScreenBlurTexture();

	u16 getPlayerMovementTimer();
	HitSensor* getPlayerBodySensor();

	bool changePlayerAnimAndStartBvaIfExist(const char*);
};
