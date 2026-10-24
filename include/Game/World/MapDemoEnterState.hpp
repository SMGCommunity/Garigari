#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;

class MapDemoEnterState : public ActorStateBase< GrandGalaxyMap > {
public:
    MapDemoEnterState(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();
    virtual void kill();

    void exeZoom();
    void exeWait();

    /* 0x10 */ f32 mFovy;
};
