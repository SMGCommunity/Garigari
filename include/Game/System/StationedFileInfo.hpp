#pragma once

#include <revolution/types.h>

namespace MR {
    struct StationedFileInfo {
        enum HeapType {
            HEAP_TYPE_NAPA = 0,
            HEAP_TYPE_GDDR = 1,
            HEAP_TYPE_NONE = 2,
        };

        enum LoadType {
            LOAD_TYPE_HOME_MENU = 0,
            LOAD_TYPE_MESSAGE = 1,
            LOAD_TYPE_UNKNOWN = 2,
            LOAD_TYPE_PLAYER_MARIO = 3,
            LOAD_TYPE_PLAYER_LUIGI = 4,
            LOAD_TYPE_RESOURCE_1 = 5,
            LOAD_TYPE_RESOURCE_2 = 6,
            LOAD_TYPE_LAYOUT_1 = 7,
            LOAD_TYPE_LAYOUT_2 = 8,
        };

        /* 0x0 */ HeapType mHeapType;
        /* 0x4 */ LoadType mLoadType;
        /* 0x8 */ const char* mArchive;
    };

    const StationedFileInfo* getStationedFileInfoTable();
};  // namespace MR
