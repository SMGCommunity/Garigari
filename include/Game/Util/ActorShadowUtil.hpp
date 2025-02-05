#pragma once

#include <revolution.h>

class LiveActor;

namespace MR {
    void initShadowFromCSVWithoutInitShadowVolumeSphere(LiveActor *, const char *);

    void onShadowVisibleSyncHostAll(LiveActor *);
    void offShadowVisibleSyncHostAll(LiveActor *);
};
