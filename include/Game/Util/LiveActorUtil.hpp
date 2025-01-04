#pragma once

#include <revolution.h>

class JMapInfoIter;
class LiveActor;

namespace MR {
    void initSensors(LiveActor *, const char *, const char *);
    void initSwitches(LiveActor *, const JMapInfoIter &, const char *, const char *);

    bool isDead(const LiveActor *);
    bool isHiddenModel(const LiveActor *);
    void showModel(LiveActor *);

    void setScale(LiveActor *, f32, f32, f32);
    void setScale(LiveActor *, f32);

    void initDefaultPos(LiveActor *, const JMapInfoIter &);

    void initLightCtrl(LiveActor *);

    void setClippingFarMax(LiveActor *);

    void setGroupClipping(LiveActor *, const JMapInfoIter &, int);

    void setClippingTypeSphere(LiveActor *, f32);
};
