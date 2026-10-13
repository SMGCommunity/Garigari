#include "Game/Util/HashUtil.hpp"
#include <cctype>

HashSortTable::HashSortTable(u32 size) {
    mHashCodeArray = new u32[size];
    mValueArray = new u32[size];
    _C = new u32[128];
    _10 = new u32[128];
    mCurrentSize = 0;
    mMaxSize = size;
    _0 = 0;
}

bool HashSortTable::add(const char* pName, u32 valueToAdd, bool skip) {
    u32 hashCode = MR::getHashCode(pName);
    if (skip) {
        return addOrSkip(hashCode, valueToAdd);
    } else {
        return add(hashCode, valueToAdd);
    }
}

bool HashSortTable::add(u32 hashCode, u32 valueToAdd) {
    mHashCodeArray[mCurrentSize] = hashCode;
    mValueArray[mCurrentSize] = valueToAdd;
    mCurrentSize++;
    return true;
}

bool HashSortTable::addOrSkip(u32 hashCode, u32 valueToAdd) {
    for (u32 i = 0; i < mCurrentSize; i++) {
        if (hashCode == mHashCodeArray[i]) {
            return false;
        }
    }

    mHashCodeArray[mCurrentSize] = hashCode;
    mValueArray[mCurrentSize] = valueToAdd;
    mCurrentSize++;
    return true;
}

namespace MR {
    u32 getHashCode(const char* pStr) {
        u32 hash;

        for (hash = 0; *pStr != '\0'; pStr++) {
            hash = *pStr + hash * 31;
        }

        return hash;
    }

    u32 getHashCodeLower(const char* pStr) {
        u32 hash;

        for (hash = 0; *pStr != '\0'; pStr++) {
            hash = tolower(*pStr) + hash * 31;
        }

        return hash;
    }
}  // namespace MR
