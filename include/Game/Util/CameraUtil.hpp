#pragma once

#include "Game/Camera/CameraTargetArg.hpp"
#include "Game/LiveActor/ActorCameraInfo.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>

namespace MR {
    f32 calcCameraDistanceZ(const TVec3f&);

    void declareEventCamera(ActorCameraInfo*, const char*);
    void declareEventCameraProgrammable(const char*);
    void startEventCamera(const ActorCameraInfo*, const char*, const CameraTargetArg&, s32);
    void startEventCameraAnim(const ActorCameraInfo*, const char*, const CameraTargetArg&, s32, f32);
    void startGlobalEventCameraNoTarget(const char*, s32);
    void endEventCamera(const ActorCameraInfo*, const char*, bool, s32);
    void endEventCameraAtLanding(const ActorCameraInfo*, const char*, f32);
    void endGlobalEventCamera(const char*, s32, bool);
    bool isEventCameraActive(const ActorCameraInfo*, const char*);
    void setProgrammableCameraParam(const char*, const TVec3f&, const TVec3f&, const TVec3f&, bool);
    void setProgrammableCameraParamFovy(const char*, f32);
    s32 getAnimCameraFrame(const ActorCameraInfo*, const char*);
    bool isAnimCameraEnd(const ActorCameraInfo*, const char*);
    s32 getEventCameraFrames(const ActorCameraInfo*, const char*);
};  // namespace MR
