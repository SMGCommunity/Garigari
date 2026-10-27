#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/Array.hpp"

class WorldMapModel : public LiveActor {
public:
    WorldMapModel(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();

    void appearAll();
    void killAll();

    /* 0x90 */ MR::AssignableArray< LiveActor* > mChildObjs;
};
