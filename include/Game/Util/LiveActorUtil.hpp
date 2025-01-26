#pragma once

#include <revolution.h>

class JMapInfoIter;
class LiveActor;
class ResourceHolder;
class HitSensor;

namespace MR {
    void initSensors(LiveActor *, const char *, const char *);
    void initSwitches(LiveActor *, const JMapInfoIter &, const char *, const char *);

    bool isDead(const LiveActor *);
    bool isHiddenModel(const LiveActor *);
    void showModel(LiveActor *);

    void setScale(LiveActor *, f32, f32, f32);
    void setScale(LiveActor *, f32);

    void scaleBinderRadius(LiveActor *, f32);

    void initLightCtrl(LiveActor *);

    void setClippingFarMax(LiveActor *);

    void setGroupClipping(LiveActor *, const JMapInfoIter &, int);

    void setClippingTypeSphere(LiveActor *, f32);

    void initCollisionPartsFromResourceHolder(LiveActor *, const char *, HitSensor *, ResourceHolder *, MtxPtr);

    bool tryStartAllAnim(const LiveActor *, const char *);
};
