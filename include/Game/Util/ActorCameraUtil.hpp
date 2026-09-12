#pragma once

#include <revolution.h>
#include "JGeometry.hpp"

/* FINISHED */

class ActorCameraInfo;
class CameraTargetArg;
class CameraTargetMtx;
class JMapInfoIter;
class LiveActor;
class ResourceHolder;

namespace {
	void createActorCameraName(char* pDest, u32 size, const LiveActor* pActor, const ActorCameraInfo* pCameraInfo);
	void createMultiActorCameraName(char* pDest, u32 size, const LiveActor* pActor, const ActorCameraInfo* pCameraInfo, const char* pClassifier);
};

namespace MR {
	ActorCameraInfo* createActorCameraInfo(const JMapInfoIter& rIter);
	bool createActorCameraInfoIfExist(const JMapInfoIter& rIter, ActorCameraInfo** pInfoDest);
	bool initActorCamera(const LiveActor* pActor, const JMapInfoIter& rIter, ActorCameraInfo** pInfoDest);
	bool initMultiActorCamera(const LiveActor* pActor, const JMapInfoIter& rIter, ActorCameraInfo** pInfoDest, const char* pName);
	bool initMultiActorCameraNoInit(const LiveActor* pActor, ActorCameraInfo* pInfo, const char* pClassifier);
	void initActorCameraProgrammable(const LiveActor* pActor);

	bool startActorCameraNoTarget(const LiveActor* pActor, const ActorCameraInfo* pInfo, s32);
	bool startActorCameraTargetPlayer(const LiveActor* pActor, const ActorCameraInfo* pInfo, s32);
	bool startActorCameraTargetSelf(const LiveActor* pActor, const ActorCameraInfo* pInfo, s32);
	bool startActorCameraTargetMtx(const LiveActor* pActor, const ActorCameraInfo* pInfo, CameraTargetMtx* pTargetMtx, s32);
	bool startActorCameraTargetOther(const LiveActor* pActor, const ActorCameraInfo* pInfo, const CameraTargetArg& rTargetArg, s32);
	bool startMultiActorCameraNoTarget(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, s32);
	bool startMultiActorCameraTargetPlayer(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, s32);
	bool startMultiActorCameraTargetSelf(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, s32);
	bool startMultiActorCameraTargetMtx(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, CameraTargetMtx* pTargetMtx, s32);
	bool startMultiActorCameraTargetOther(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, const CameraTargetArg& rTargetArg, s32);
	void startAnimCameraTargetPlayer(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName, s32, bool, f32);
	void startAnimCameraTargetSelf(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName, s32, bool, f32);
	void startAnimCameraTargetOther(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName, const CameraTargetArg& rTargetArg, s32, bool, f32);
	void startActorCameraProgrammable(const LiveActor* pActor, s32);

	bool endActorCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, bool, s32);
	bool endMultiActorCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier, bool, s32);
	bool endActorCameraAtLanding(const LiveActor* pActor, const ActorCameraInfo* pInfo, s32);
	bool endActorCameraProgrammable(const LiveActor* pActor, s32, bool);

	bool isActiveActorCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo);
	bool isActiveMultiActorCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier);

	void setProgrammableCameraParam(const LiveActor* pActor, const TVec3f&, const TVec3f&, const TVec3f&);
	void setProgrammableCameraParamFovy(const LiveActor* pActor, f32 fovy);

	void initAnimCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName);
	void initAnimCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName, ResourceHolder* pResourceHolder);
	void endAnimCamera(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName, s32, bool);
	void setAnimCameraLastFrame(const LiveActor* pActor, const ActorCameraInfo* pCameraInfo, const char* pAnimCameraName);
	bool isAnimCameraEnd(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pAnimCameraName);

	s32 getActorCameraFrames(const LiveActor* pActor, const ActorCameraInfo* pInfo);
	s32 getMultiActorCameraFrames(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char* pClassifier);
	bool isExistActorCamera(const ActorCameraInfo* pInfo);

	void startRumbleWithShakeCameraWeak(const LiveActor* pActor, const char*, const char*, f32, f32);
	void startRumbleWithShakeCameraNormalWeak(const LiveActor* pActor, const char*, const char*, f32, f32);
	void startRumbleWithShakeCameraStrong(const LiveActor* pActor, const char*, const char*, f32, f32);
};
