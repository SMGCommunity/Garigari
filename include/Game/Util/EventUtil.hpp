#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class JMapIdInfo;
class JMapInfoIter;
class LiveActor;
class NameObj;

namespace MR {
	void incPlayerAndTryScenarioMissNum();
	s32 getPlayerLeft();
	void addPlayerLeft(int lives);
	void decPlayerLeft();
	void incPlayerGameOverNum();

	bool isPlayerLuigi();

	s32 getStarPieceNum();
	void addStarPiece(int itemCount);
	void incCoin(int itemCount, LiveActor* pHost);
	void decCoin(int itemCount);
	s32 getCoinNum();
	void incPurpleCoin();
	s32 getPurpleCoinNum();
	bool isPurpleCoinNum100();

	void explainBeeMarioIfAtFirst();
	void explainTeresaMarioIfAtFirst();
	void explainHopperMarioIfAtFirst();
	void explainFireMarioIfAtFirst();
	void explainIceMarioIfAtFirst();
	void explainFlyingMarioIfAtFirst();
	void explainInvincibleMarioIfAtFirst();
	void explainRockMarioIfAtFirst();
	void explainCloudMarioIfAtFirst();
	void explainDrillIfAtFirst();
	void explainLifeUpIfAtFirst();
	void explainOneUpIfAtFirst();
	void explainYoshiIfAtFirst(LiveActor* pHost);
	void explainCometMedalIfAtFirst(LiveActor* pHost);
	void explainMarioFacePlanetAtFirst(LiveActor* pHost);

	void onGameEventFlagBeeMarioAtFirst();
	void onGameEventFlagTeresaMarioAtFirst();
	void onGameEventFlagHopperMarioAtFirst();
	void onGameEventFlagFireMarioAtFirst();
	void onGameEventFlagIceMarioAtFirst();
	void onGameEventFlagFlyingMarioAtFirst();
	void onGameEventFlagInvincibleMarioAtFirst();
	void onGameEventFlagRockMarioAtFirst();
	void onGameEventFlagCloudMarioAtFirst();
	void onGameEventFlagDrillAtFirst();
	void onGameEventFlagLifeUpAtFirst();
	void onGameEventFlagOneUpAtFirst();
	void onGameEventFlagTamakoroTutorialAtFirst();
	void onGameEventFlagGliBirdTutorialAtFirst();
	void onGameEventFlagYoshiAtFirst();
	void onGameEventFlagCometMedalAtFirst();
	void onGameEventFlagSupportTicoAtFirst();
	void onGameEventFlagKinopioBankAtFirst();

	bool isOnGameEventFlagBeeMarioAtFirst();
	bool isOnGameEventFlagTeresaMarioAtFirst();
	bool isOnGameEventFlagHopperMarioAtFirst();
	bool isOnGameEventFlagFireMarioAtFirst();
	bool isOnGameEventFlagIceMarioAtFirst();
	bool isOnGameEventFlagFlyingMarioAtFirst();
	bool isOnGameEventFlagInvincibleMarioAtFirst();
	bool isOnGameEventFlagRockMarioAtFirst();
	bool isOnGameEventFlagCloudMarioAtFirst();
	bool isOnGameEventFlagDrillAtFirst();
	bool isOnGameEventFlagLifeUpAtFirst();
	bool isOnGameEventFlagOneUpAtFirst();
	bool isOnGameEventFlagTamakoroTutorialAtFirst();
	bool isOnGameEventFlagGliBirdTutorialAtFirst();
	bool isOnGameEventFlagYoshiAtFirst();
	bool isOnGameEventFlagCometMedalAtFirst();
	bool isOnGameEventFlagSupportTicoAtFirst();
	bool isOnGameEventFlagKinopioBankAtFirst();
	bool isOnGameEventFlagNormalEnding();
	bool isOnGameEventFlag120PowerStarsEnding();

	bool isPreventDisplayInformationMessage();

	bool setupAlreadyDoneFlag(int* outIndex, const char* name, const JMapInfoIter& rIter, bool useless);
	void onAlreadyDoneFlag(const char* name);
	void onAlreadyDoneFlag(int index);
	bool isOnAlreadyDoneFlag(const char* name);

	bool isAlreadyVisitedCurrentStageAndScenario();

	bool hasPowerStarInCurrentStage(s32 powerStarId);
	bool isPowerStarGreenInCurrentStage(s32 powerStarId);
	bool isPowerStarBronzeInCurrentStage(s32 powerStarId);
	bool isGrandStarInCurrentStage(s32 powerStarId);
	bool hasPowerStarInCurrentStageWithDeclarer(const char* pDeclarer, s32 powerStarId);
	bool isPowerStarGreenInCurrentStageWithDeclarer(const char* pDeclarer, s32 powerStarId);
	bool isPowerStarBronzeInCurrentStageWithDeclarer(const char* pDeclarer, s32 powerStarId);
	bool isGrandStarInCurrentStageWithDeclarer(const char* pDeclarer, s32 powerStarId);
	bool isScenarioOpenInCurrentStageWithDeclarer(const char* pDeclarer);
	bool isPowerStarWithDeclarer(const char* pDeclarer, s32 powerStarId);
	bool isOnGameEventFlagPowerStarSuccess(const char* pDeclarer, s32 powerStarId);
	bool hasGrandStar(int grandStarId);
	s32 getPowerStarNumOwnedInStage(const char* pStageName);
	bool isPowerStarGreen(const char* pStageName, s32 powerStarId);
	bool isPowerStarGreenInCurrentStage();
	bool isPowerStarBronze(const char* pStageName, s32 powerStarId);

	s32 getPowerStarNum();
	bool hasAllNormalPowerStarWithoutComet(const char* pStageName);

	void setRaceBestTime(int raceId, s32 bestTime);
	s32 getRaceBestTime(int raceId);
	s32 getRaceCurrentTime();

	s32 registerStorageSpinDriverPathDrawRange(const NameObj*, const JMapInfoIter&, int, f32*); // useless
	void updateStorageSpinDriverPathDrawRange(int, f32); // useless

	bool isGalaxyDarkCometAppearInCurrentStage();
	bool isGalaxyQuickCometAppearInCurrentStage();
	bool isGalaxyPurpleCometAppearInCurrentStage();
	bool isGalaxyHorrorCometAppearInCurrentStage(); // always false
	bool isGalaxyRainbowCometAppearInCurrentStage(); // always false

	void startGalaxyCometEvent();
	void endGalaxyCometEvent();
	bool isGalaxyCometEvent();

	// various unknown functions

	bool isGalaxyCompletedNoGreen(const char* pStageName);
	bool isGalaxyCompletedWithGreen(const char* pStageName);

	const JMapIdInfo* getRestartMarioNo();
	void setRestartMarioNo(const JMapIdInfo& rIdInfo);

	bool isGhostLuigiOpenInStage();

	// various PostmanEvent functions

	bool isIslandFleetGalaxy1FirstTime();
};
