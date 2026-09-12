#pragma once

#include <revolution.h>

class LiveActor;

namespace MR {
	void startBck(const LiveActor*, const char*, const char*);
	bool isBckStopped(const LiveActor*);
	bool tryStartAllAnim(const LiveActor*, const char*);
	void startAction(const LiveActor*, const char*);

	bool tryStartActionNotPlaying(const LiveActor*, const char*);

	bool isActionEnd(const LiveActor*);
	bool isAnyAnimPlaying(const LiveActor*, const char*);

	void startBckWithInterpole(const LiveActor*, const char*, s32);
	void startBckNoInterpole(const LiveActor*, const char*);
	void startBckAtFirstStep(const LiveActor*, const char*);
	bool tryStartBck(const LiveActor*, const char*, const char*);
	bool tryStartBckAndBtp(const LiveActor*, const char*, const char*);
	void setAllAnimFrame(const LiveActor*, const char*, f32);
	void setAllAnimFrameAndStop(const LiveActor*, const char*, f32);
	void setAllAnimFrameAtEnd(const LiveActor*, const char*);

	bool isAnyAnimStopped(const LiveActor*, const char*);
	bool isAnyAnimOneTimeAndStopped(const LiveActor*, const char*);
	bool isBtkStopped(const LiveActor*);
	bool isBrkStopped(const LiveActor*);
	bool isBtpStopped(const LiveActor*);
	bool isBpkStopped(const LiveActor*);
	bool isBvaStopped(const LiveActor*);
	bool isBckOneTimeAndStopped(const LiveActor*);
	bool isBtkOneTimeAndStopped(const LiveActor*);
	bool isBrkOneTimeAndStopped(const LiveActor*);
	bool isBckLooped(const LiveActor*);
	bool checkPassBckFrame(const LiveActor*, f32);
	bool setBckFrameAtRandom(const LiveActor*);
	bool setBtkFrameAtRandom(const LiveActor*);
	bool setBckFrameAndStop(const LiveActor*, f32);
	bool setBtkFrameAndStop(const LiveActor*, f32);
	bool setBrkFrameAndStop(const LiveActor*, f32);
	bool setBtpFrameAndStop(const LiveActor*, f32);
	bool setBpkFrameAndStop(const LiveActor*, f32);
	bool setBvaFrameAndStop(const LiveActor*, f32);
	bool setBckFrameEndAndStop(const LiveActor*);
	bool setBrkFrameEndAndStop(const LiveActor*);
	void startBckAndSetFrameAndStop(const LiveActor*, const char*, f32);
	void startBtkAndSetFrameAndStop(const LiveActor*, const char*, f32);
	void startBrkAndSetFrameAndStop(const LiveActor*, const char*, f32);
	void startBtpAndSetFrameAndStop(const LiveActor*, const char*, f32);
	void startBvaAndSetFrameAndStop(const LiveActor*, const char*, f32);
	void startBtk(const LiveActor*, const char*);
	void startBrk(const LiveActor*, const char*);
	void startBtp(const LiveActor*, const char*);
	void startBpk(const LiveActor*, const char*);
	void startBva(const LiveActor*, const char*);
	bool startBckIfExist(const LiveActor*, const char*);
	bool startBtkIfExist(const LiveActor*, const char*);
	bool startBrkIfExist(const LiveActor*, const char*);
	bool startBtpIfExist(const LiveActor*, const char*);
	bool startBpkIfExist(const LiveActor*, const char*);
	bool startBvaIfExist(const LiveActor*, const char*);

	void stopBck(const LiveActor*);
	void stopBtk(const LiveActor*);
	void stopBrk(const LiveActor*);
	void stopBtp(const LiveActor*);
	void stopBva(const LiveActor*);
	void setBckRate(const LiveActor*, f32);
	void setBtkRate(const LiveActor*, f32);
	void setBrkRate(const LiveActor*, f32);
	void setBtpRate(const LiveActor*, f32);
	void setBpkRate(const LiveActor*, f32);
	void setBvaRate(const LiveActor*, f32);
	void setBckFrame(const LiveActor*, f32);
	void setBtkFrame(const LiveActor*, f32);
	void setBrkFrame(const LiveActor*, f32);
	void setBtpFrame(const LiveActor*, f32);
	void setBpkFrame(const LiveActor*, f32);
	void setBvaFrame(const LiveActor*, f32);
	bool isBckPlaying(const LiveActor*, const char*);
	bool isBtkPlaying(const LiveActor*, const char*);
	bool isBrkPlaying(const LiveActor*, const char*);
	bool isBtpPlaying(const LiveActor*, const char*);
	bool isBpkPlaying(const LiveActor*, const char*);
	bool isBvaPlaying(const LiveActor*, const char*);
	bool isBckPlayingIfExist(const LiveActor*, const char*);
	bool isBtkPlayingIfExist(const LiveActor*, const char*);
	bool isBrkPlayingIfExist(const LiveActor*, const char*);
	bool isBtpPlayingIfExist(const LiveActor*, const char*);
	bool isBpkPlayingIfExist(const LiveActor*, const char*);
	bool isBvaPlayingIfExist(const LiveActor*, const char*);
	bool isPlayingAnim(const LiveActor*, const char*);
	bool isExistAnim(const LiveActor*, const char*);
	bool isExistBck(const LiveActor*, const char*);
	bool isExistBtk(const LiveActor*, const char*);
	bool isExistBrk(const LiveActor*, const char*);
	bool isExistBtp(const LiveActor*, const char*);
	bool isExistBpk(const LiveActor*, const char*);
	bool isExistBva(const LiveActor*, const char*);
	void* getBckCtrl(const LiveActor*);
	void* getBtkCtrl(const LiveActor*);
	void* getBrkCtrl(const LiveActor*);
	void* getBtpCtrl(const LiveActor*);
	void* getBpkCtrl(const LiveActor*);
	void* getBvaCtrl(const LiveActor*);
	void updateMaterial(LiveActor*);
};
