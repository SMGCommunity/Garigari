#pragma once

#include "Game/System/NerveExecutor.hpp"

class GrandGalaxyMap;
class MapDemoStateEnter;
class MapDemoStateInit;
class MapDemoStateWait;
class MapDemoStateWarn;
class MapDemoStateWarp;

class MapDemoManager : public NerveExecutor {
public:
    MapDemoManager(GrandGalaxyMap*);

    void init(bool);
    void fn_804E0640();
    void fn_804E0690();

    void exeEnter();
    void exeWait();
    void exeNews();
    void exePointMove();
    void exeWorldWarp();

    bool isActiveWorldWarp();
    bool isNotWarping();
    bool fn_804E0820();

    /* 0x08 */ GrandGalaxyMap* mMap;
    /* 0x0C */ MapDemoStateEnter* mStateEnter;
    /* 0x10 */ MapDemoStateInit* mStateInit;
    /* 0x14 */ MapDemoStateWait* mStateWait;
    /* 0x18 */ u32 _18;  // Unknown
    /* 0x1C */ MapDemoStateWarn* mStateWarn;
    /* 0x20 */ MapDemoStateWarp* mStateWarp;
    /* 0x24 */ bool mIsPlayerStickMoving;
};
