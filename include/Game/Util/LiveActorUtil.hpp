#pragma once

#include <revolution.h>

class JMapInfoIter;
class LiveActor;
class ResourceHolder;
class HitSensor;
class ModelObj;

namespace MR {
    void initSensors(LiveActor *, const char *, const char *);
    void initSwitches(LiveActor *, const JMapInfoIter &, const char *, const char *);

    bool isDead(const LiveActor *);
    bool isHiddenModel(const LiveActor *);
    void showModel(LiveActor *);

    void hideModelAndOnCalcAnim(LiveActor* );

    void setScale(LiveActor *, f32, f32, f32);
    void setScale(LiveActor *, f32);

    void scaleBinderRadius(LiveActor *, f32);

    void initLightCtrl(LiveActor *);

    void setClippingFarMax(LiveActor *);

    void setGroupClipping(LiveActor *, const JMapInfoIter &, int);

    void setClippingTypeSphere(LiveActor *, f32);

    void initCollisionPartsFromResourceHolder(LiveActor *, const char *, HitSensor *, ResourceHolder *, MtxPtr);

    bool tryStartAllAnim(const LiveActor *, const char *);

    void setClippingTypeSphereContainsModelBoundingBox(LiveActor *, f32);

    void setClippingFar(LiveActor *, f32);

    void invalidateClipping(LiveActor *);

    void calcAnimDirect(LiveActor *);

    void copyTransRotateScale(const LiveActor *, LiveActor *);

    const char* createLowModelObjName(const LiveActor *);
    const char* createMiddleModelObjName(const LiveActor *);

    const char* getModelResName(const LiveActor *);
};
