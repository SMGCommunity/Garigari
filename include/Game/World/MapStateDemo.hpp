#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;

// TODO: better name
class MapStateDemo : public ActorStateBase<GrandGalaxyMap> {
public:
    MapStateDemo(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();
    virtual void kill();

    void exeNerve1(); // TODO: better name
    void exeNerve2(); // TODO: better name

    /* 0x10 */ f32 _10;
};
