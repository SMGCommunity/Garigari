#pragma once

#include <revolution.h>

namespace MR {
	bool startStageBGM(const char*, bool);
	bool startStageBGM(u32, bool);
	bool startStageBGMIfNotPlaying(const char*, bool);
	bool startStageBGMFromStageName(const char*, const char*, s32);

	void stopStageBGM(u32);
	void unlockStageBGM();
	void moveVolumeStageBGM(f32, u32);
	void moveVolumeStageBGMForNoteFairy(f32, u32);
	void startCurrentStageBGM(bool);
	void startLastStageBGM();
	bool isPlayingStageBgm();
	bool isPlayingStageBgmID(u32);
	bool isPlayingStageBgmName(const char*);
	bool isPreparedStageBgm();
	void setStageBGMState(s32, u32);
	void setStageBGMStateBit(u32);

	void startSubBGM(const char*, bool);
	void stopSubBGM(u32);
	void moveVolumeSubBGM(f32, u32);
	bool isPlayingSubBgmID(u32);
	void startBossBGM(s32);
	void startDepartBGM();
	void startGliderBGM();
	void startMinigameBGM();

	void startBossRushBGM();
	void startAfterBossRushBGM();

	void startStarChanceBGM(bool);

	void startMarioFaceShipBGM();
	void startGrandStarReturnBGM();
	bool isFirstGrandStarReturnBGMStage();

	void setCubeBgmChangeInvalid();

	void clearBgmQueue();
};
