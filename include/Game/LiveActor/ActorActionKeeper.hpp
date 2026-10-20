#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <revolution.h>

class ActorAnimKeeper;
class ActionFlagCtrl;
class ActorPadAndCameraCtrl;
class ActorHitReactionCtrl;
class ActorItemGenerator;
class ActorParam;
class ActionScreenBlurCtrl;
class ActionFootPrintCtrl;
class ActionBgmCtrl;

class ActorActionKeeper {
public:
    ActorActionKeeper(LiveActor*, ActorAnimKeeper*, ActionFlagCtrl*, ActorPadAndCameraCtrl*, ActorHitReactionCtrl*, ActorItemGenerator*, ActorParam*,
                      ActionScreenBlurCtrl*, ActionFootPrintCtrl*, ActionBgmCtrl*);

    void tryCreate(LiveActor*, const char*);
    void initFlagCtrl();
    void startAction(const char*);
    void updateAnimKeeper();
    void update();
};
