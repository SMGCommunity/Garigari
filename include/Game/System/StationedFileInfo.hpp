#pragma once

#include <revolution/types.h>

namespace MR {
    struct StationedFileInfo {
        enum HeapType {
            /* 0x0 */ HEAP_TYPE_NAPA,
            /* 0x1 */ HEAP_TYPE_GDDR,
            /* 0x2 */ HEAP_TYPE_NONE,
        };

        enum LoadType {
            /* 0x0 */ LOAD_TYPE_HOME_MENU,
            /* 0x1 */ LOAD_TYPE_MESSAGE,
            /* 0x2 */ LOAD_TYPE_UNKNOWN,
            /* 0x3 */ LOAD_TYPE_PLAYER_MARIO,
            /* 0x4 */ LOAD_TYPE_PLAYER_LUIGI,
            /* 0x5 */ LOAD_TYPE_RESOURCE_1,
            /* 0x6 */ LOAD_TYPE_RESOURCE_2,
            /* 0x7 */ LOAD_TYPE_LAYOUT_1,
            /* 0x8 */ LOAD_TYPE_LAYOUT_2,
        };

        /* 0x0 */ HeapType mHeapType;
        /* 0x4 */ LoadType mLoadType;
        /* 0x8 */ const char* mArchive;
    };

    const StationedFileInfo* getStationedFileInfoTable();
};  // namespace MR
