#pragma once

#include "Game/Util/ActorCameraUtil.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class LiveActor;
class ActorCameraInfo;
class CameraTargetArg;
class NameObj;
class JMapInfoIter;

namespace MR {
    bool calcScreenPosition(TVec2f*, const TVec3f&);
    bool calcScreenPosition(TVec3f*, const TVec3f&);
    bool calcNormalizedScreenPosition(TVec3f*, const TVec3f&);
    bool calcNormalizedScreenPositionFromView(TVec3f*, const TVec3f&);
    bool calcWorldPositionFromScreen(TVec3f*, const TVec2f&, f32);
    bool calcWorldPositionFromCenterScreen(TVec3f*, const TVec2f&, f32);
    bool calcWorldRayDirectionFromScreen(TVec3f*, const TVec2f&);

    f32 calcCameraDistanceZ(const TVec3f&);

    f32 getFovy();
    void setFovy(f32);

    void declareEventCamera(const ActorCameraInfo*, const char*);
    void declareEventCameraProgrammable(const char*);
    void startEventCamera(const ActorCameraInfo*, const char*, const CameraTargetArg&, s32);
    void startEventCameraAnim(const ActorCameraInfo*, const char*, const CameraTargetArg&, s32, f32);
    void startGlobalEventCameraNoTarget(const char*, s32);
    void endEventCamera(const ActorCameraInfo*, const char*, bool, s32);
    void endEventCameraAtLanding(const ActorCameraInfo*, const char*, s32);
    void endGlobalEventCamera(const char*, s32, bool);
    bool isEventCameraActive(const ActorCameraInfo*, const char*);
    void setProgrammableCameraParam(const char*, const TVec3f&, const TVec3f&, const TVec3f&, bool);
    void setProgrammableCameraParamFovy(const char*, f32);
    s32 getAnimCameraFrame(const ActorCameraInfo*, const char*);
    bool isAnimCameraEnd(const ActorCameraInfo*, const char*);
    s32 getEventCameraFrames(const ActorCameraInfo*, const char*);

    void declareEventCameraAnim(const ActorCameraInfo*, const char*, void*);
    bool endMultiActorCameraAtLanding(const LiveActor* pActor, const ActorCameraInfo* pInfo, const char*, s32);

    // TODO: position properly
    bool isStartPosCameraEnd();
    const TPos3f& getCameraViewMtx();
    bool isActiveLauncherCamera();
    bool isActiveLauncherFlightCamera();
    const TVec3f getCamPos();
    TVec3f getCamXdir();
    TVec3f getCamYdir();
    TVec3f getCamZdir();
};  // namespace MR
