#pragma once

#include <revolution/types.h>

class HashSortTable {
public:
    HashSortTable(u32);

    // The below functions have unknown return types; using void for now.
    bool add(const char*, u32, bool);
    bool add(u32, u32);
    bool addOrSkip(u32, u32);
    void sort();
    void search(u32, u32*);
    void search(const char*, u32*);
    void search(const char*, const char*, u32*);
    void swap(const char*, const char*);

    /* 0x00 */ char _0;
    /* 0x04 */ u32* mHashCodeArray;
    /* 0x08 */ u32* mValueArray;
    /* 0x0C */ u32* _C;
    /* 0x10 */ u32* _10;
    /* 0x14 */ u32 mCurrentSize;
    /* 0x18 */ u32 mMaxSize;
};

namespace MR {
    u32 getHashCode(const char*);
    u32 getHashCodeLower(const char*);
};  // namespace MR
