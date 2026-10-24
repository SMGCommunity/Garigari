#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class GrandGalaxyMap;
class TalkMessageCtrl;

class MapDemoStateGrandGalaxyMapNews : public ActorStateBase< GrandGalaxyMap > {
public:
    MapDemoStateGrandGalaxyMapNews(GrandGalaxyMap*);

    virtual void init();
    virtual void appear();
    virtual void kill();

    bool fn_804E29D0();  // TODO: better name

    void exeNerve1();  // TODO: better name
    void exeNerve2();  // TODO: better name
    void exeNerve3();  // TODO: better name
    void exeNerve4();  // TODO: better name

    void fn_804E2C40();  // TODO: better name
    void fn_804E2C80();  // TODO: better name
    void fn_804E2D40();  // TODO: better name

    /* 0x10 */ s32 mWorldId;
    /* 0x14 */ TalkMessageCtrl** mTalkMessageCtrlArray;
};
