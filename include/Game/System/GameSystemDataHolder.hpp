#pragma once

#include "Game/Util/JMapInfo.hpp"

class GameSystemDataHolder {
public:
    GameSystemDataHolder();

    void init();

    /* 0x00 */ JMapInfo* mHeapSizeExcept;
    /* 0x04 */ JMapInfo* mGalaxyDataTable;
    /* 0x08 */ JMapInfo* mMarioFaceShipEventDataTable;
    /* 0x0C */ JMapInfo* mMarioFaceShipEventCastTable;
    /* 0x10 */ JMapInfo* mGalaxyWorldOrderList;
    /* 0x10 */ JMapInfo* mWorldMapHeapGalaxy;
    /* 0x10 */ JMapInfo* mWorldMapHeapResource;
};

namespace GameSystemDataFunction {
    const JMapInfo* getHeapSizeExcept();
    const JMapInfo* getMarioFaceShipEventDataTable();
    const JMapInfo* getMarioFaceShipEventCastTable();
    const JMapInfo* getGalaxyWorldOrderList();
    const JMapInfo* getWorldMapHeapGalaxy();
    const JMapInfo* getWorldMapHeapResource();
}
