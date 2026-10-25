#include "Game/Util/HashUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include <cctype>

HashSortTable::HashSortTable(u32 numMax) {
    mHashArray = new u32[numMax];
    mValueArray = new u32[numMax];
    mBucketArray = new u16[256];
    mBucketSizeArray = new u16[256];
    mTableSize = 0;
    mTableSizeMax = numMax;
    mIsSorted = false;
}

bool HashSortTable::add(const char* pName, u32 value, bool isSkip) {
    u32 hashCode = MR::getHashCode(pName);
    if (isSkip) {
        return addOrSkip(hashCode, value);
    } else {
        return add(hashCode, value);
    }
}

bool HashSortTable::add(u32 hash, u32 value) {
    mHashArray[mTableSize] = hash;
    mValueArray[mTableSize] = value;
    mTableSize++;
    return true;
}

bool HashSortTable::addOrSkip(u32 hash, u32 value) {
    for (u32 i = 0; i < mTableSize; i++) {
        if (hash == mHashArray[i]) {
            return false;
        }
    }

    mHashArray[mTableSize] = hash;
    mValueArray[mTableSize] = value;
    mTableSize++;
    return true;
}

void HashSortTable::sort() {
    if (mTableSize == 0)
        return;

    s32 indexArray[0x400];
    MR::sortSmall(mTableSize, mHashArray, indexArray);

    u32 sortedArray[0x400];
    for (int i = 0; i < mTableSize; i++) {
        sortedArray[i] = mValueArray[indexArray[i]];
    }

    for (int i = 0; i < mTableSize; i++) {
        mValueArray[i] = sortedArray[i];
    }

    u32 i = 0;
    u32 currentByteValue;

    for (currentByteValue = 0; currentByteValue < 256; currentByteValue++) {
        u32 hashUpperByte = mHashArray[i] >> 24;

        if (hashUpperByte > currentByteValue) {
            // No hash codes with this upper byte
            mBucketArray[currentByteValue] = 65535;
            mBucketSizeArray[currentByteValue] = 0;
            continue;
        } else if (hashUpperByte != currentByteValue) {
            continue;
        }

        u32 numHashes = 1;
        mBucketArray[currentByteValue] = i;
        i++;

        while (i < mTableSize) {
            u32 hashUpperByte = mHashArray[i] >> 24;

            if (hashUpperByte != currentByteValue)
                break;

            numHashes++;
            i++;
        }

        mBucketSizeArray[currentByteValue] = numHashes;

        if (i == mTableSize) {
            currentByteValue++;
            break;
        }
    }

    for (u32 i = currentByteValue; i < 256; i++) {
        mBucketArray[i] = 65535;
        mBucketSizeArray[i] = 0;
    }

    mIsSorted = true;
}

bool HashSortTable::search(u32 hash, u32* pDst) {
    u8 upperByte = hash >> 24;

    if (pDst != nullptr) {
        *pDst = 0;
    }

    u16 bucketSize = mBucketSizeArray[upperByte];

    if (bucketSize == 0) {
        return false;
    }

    u16 indexFirstHash = mBucketArray[upperByte];
    u32* pCurrentHash = &mHashArray[indexFirstHash];

    for (u32 i = 0; i < bucketSize; i++) {
        if (*pCurrentHash == hash) {
            if (pDst != nullptr) {
                *pDst = mValueArray[i + indexFirstHash];
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

void HashSortTable::swap(const char* pOldName, const char* pNewName) {
    u32 hashCode1 = MR::getHashCode(pOldName);

    for (u32 i = 0; i < mTableSize; i++) {
        if (hashCode1 == mHashArray[i]) {
            u32 hashCode2 = MR::getHashCode(pNewName);
            mHashArray[i] = hashCode2;
            return;
        }
    }

    mHashArray[mTableSize] = hashCode1;
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
}
