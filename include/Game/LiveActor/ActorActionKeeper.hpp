#pragma once

#include <revolution.h>

class LiveActor;
class ActorActionKeeper {
public:
    static ActorActionKeeper* tryCreate(LiveActor*, const char*);
    void updateAnimKeeper();
    void update();
    void initFlagCtrl();
};
