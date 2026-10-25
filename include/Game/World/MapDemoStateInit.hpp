#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;

class MapDemoStateInit : public ActorStateBase< GrandGalaxyMap > {
public:
    MapDemoStateInit(GrandGalaxyMap*);

    virtual ~MapDemoStateInit();
    virtual void init();
    virtual void appear();
    virtual void kill();

    void exeNerve1();
};
