#include "Game/Util/HashUtil.hpp"
#include <cctype>

HashSortTable::HashSortTable(u32 pSize) {
    hashCodeArray = new u32[pSize];
    valueArray = new u32[pSize];
    _C = new u32[128];
    _10 = new u32[128];
    currentSize = 0;
    maxSize = pSize;
    _0 = 0;
}

bool HashSortTable::add(const char* pName, u32 valueToAdd, bool orSkip) {
    u32 hashCode = MR::getHashCode(pName);
    if (orSkip) {
        return addOrSkip(hashCode, valueToAdd);
    } else {
        return add(hashCode, valueToAdd);
    }
}

bool HashSortTable::add(u32 hashCode, u32 valueToAdd) {
    hashCodeArray[currentSize] = hashCode;
    valueArray[currentSize] = valueToAdd;
    currentSize++;
    return true;
}

bool HashSortTable::addOrSkip(u32 hashCode, u32 valueToAdd) {
    for (u32 i = 0; i < currentSize; i++) {
        if (hashCode == hashCodeArray[i]) {
            return false;
        }
    }

    hashCodeArray[currentSize] = hashCode;
    valueArray[currentSize] = valueToAdd;
    currentSize++;
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
