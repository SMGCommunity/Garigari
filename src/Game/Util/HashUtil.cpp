#include "Game/Util/HashUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include <cctype>

HashSortTable::HashSortTable(u32 numMax) {
    mHashCodes = new u32[numMax];
    mValues = new u32[numMax];
    mBucketStartIndices = new u16[256];
    mBucketSizes = new u16[256];
    mTableSize = 0;
    mTableMaxSize = numMax;
    mlsSorted = false;
}

bool HashSortTable::add(const char* pName, u32 value, bool skip) {
    u32 hashCode = MR::getHashCode(pName);
    if (skip) {
        return addOrSkip(hashCode, value);
    } else {
        return add(hashCode, value);
    }
}

bool HashSortTable::add(u32 hash, u32 value) {
    mHashCodes[mTableSize] = hash;
    mValues[mTableSize] = value;
    mTableSize++;
    return true;
}

bool HashSortTable::addOrSkip(u32 hash, u32 value) {
    for (u32 i = 0; i < mTableSize; i++) {
        if (hash == mHashCodes[i]) {
            return false;
        }
    }

    mHashCodes[mTableSize] = hash;
    mValues[mTableSize] = value;
    mTableSize++;
    return true;
}

void HashSortTable::sort() {
    if (mTableSize == 0)
        return;

    s32 indexArray[0x400];
    MR::sortSmall(mTableSize, mHashCodes, indexArray);

    u32 sortedArray[0x400];
    for (int i = 0; i < mTableSize; i++) {
        sortedArray[i] = mValues[indexArray[i]];
    }

    for (int i = 0; i < mTableSize; i++) {
        mValues[i] = sortedArray[i];
    }

    u32 i = 0;
    u32 currentByteValue;

    for (currentByteValue = 0; currentByteValue < 256; currentByteValue++) {
        u32 hashUpperByte = mHashCodes[i] >> 24;

        if (hashUpperByte > currentByteValue) {
            // No hash codes with this upper byte
            mBucketStartIndices[currentByteValue] = 65535;
            mBucketSizes[currentByteValue] = 0;
            continue;
        } else if (hashUpperByte != currentByteValue) {
            continue;
        }

        u32 numHashes = 1;
        mBucketStartIndices[currentByteValue] = i;
        i++;

        while (i < mTableSize) {
            u32 hashUpperByte = mHashCodes[i] >> 24;

            if (hashUpperByte != currentByteValue)
                break;

            numHashes++;
            i++;
        }

        mBucketSizes[currentByteValue] = numHashes;

        if (i == mTableSize) {
            currentByteValue++;
            break;
        }
    }

    for (u32 i = currentByteValue; i < 256; i++) {
        mBucketStartIndices[i] = 65535;
        mBucketSizes[i] = 0;
    }

    mlsSorted = true;
}

bool HashSortTable::search(u32 hash, u32* pDst) {
    u8 upperByte = hash >> 24;

    if (pDst != nullptr) {
        *pDst = 0;
    }

    u16 bucketSize = mBucketSizes[upperByte];

    if (bucketSize == 0) {
        return false;
    }

    u16 indexFirstHash = mBucketStartIndices[upperByte];
    u32* pCurrentHash = &mHashCodes[indexFirstHash];

    for (u32 i = 0; i < bucketSize; i++) {
        if (*pCurrentHash == hash) {
            if (pDst != nullptr) {
                *pDst = mValues[i + indexFirstHash];
            }

            return true;
        }

        if (*pCurrentHash > hash) {
            return false;
        }

        pCurrentHash++;
    }

    return false;
}

bool HashSortTable::search(const char* pName, u32* pDst) {
    return search(MR::getHashCode(pName), pDst);
}

bool HashSortTable::search(const char* pName1, const char* pName2, u32* pDst) {
    u32 combinedHashCode = MR::getHashCode(pName1) + MR::getHashCode(pName2);
    return search(combinedHashCode, pDst);
}

void HashSortTable::swap(const char* pName1, const char* pName2) {
    u32 hashCode1 = MR::getHashCode(pName1);

    for (u32 i = 0; i < mTableSize; i++) {
        if (hashCode1 == mHashCodes[i]) {
            u32 hashCode2 = MR::getHashCode(pName2);
            mHashCodes[i] = hashCode2;
            return;
        }
    }

    mHashCodes[mTableSize] = hashCode1;
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
