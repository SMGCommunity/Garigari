#pragma once

#include <revolution/types.h>

class GrandGalaxyMapIcon;

class GrandGalaxyMapIconHolder {
public:
    GrandGalaxyMapIconHolder();

    void init();
    GrandGalaxyMapIcon* findMapIcon(const char*);

    /* 0x0 */ s32 mCount;
    /* 0x4 */ GrandGalaxyMapIcon** mMapIcons;
};
