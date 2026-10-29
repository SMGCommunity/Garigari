#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;
class MapPartsRailGuideDrawer;

class MapPartsRailGuideHolder : public NameObj {
public:
    MapPartsRailGuideHolder();

    virtual void init(const JMapInfoIter& rIter);

    MapPartsRailGuideDrawer* createRailGuide(LiveActor* pHost, const char* pModelName, const JMapInfoIter& rIter);
    MapPartsRailGuideDrawer* find(s32 railId);

    /* 0x014 */ MapPartsRailGuideDrawer* mDrawers[64];
    /* 0x114 */ s32 mNumRailGuides;
};
