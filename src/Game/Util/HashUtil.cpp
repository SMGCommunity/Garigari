#include "Game/Util/HashUtil.hpp"
#include "Game/Util/MathUtil.hpp"

HashSortTable::HashSortTable(u32 size) {
    mHashCodeArray = new u32[size];
    mValueArray = new u32[size];
    indexOfHashForUpperByte = new u16[256];
    numHashesForUpperByte = new u16[256];
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

void HashSortTable::sort() {
    if (mCurrentSize == 0)
        return;

    s32 indexArray[0x400];
    MR::sortSmall(mCurrentSize, mHashCodeArray, indexArray);

    u32 sortedArray[0x400];
    for (int i = 0; i < mCurrentSize; i++) {
        sortedArray[i] = mValueArray[indexArray[i]];
    }

    for (int i = 0; i < mCurrentSize; i++) {
        mValueArray[i] = sortedArray[i];
    }

    u32 i = 0;
    u32 currentByteValue;

    for (currentByteValue = 0; currentByteValue < (u32)0x100; currentByteValue++) {
        u32 hashUpperByte = mHashCodeArray[i] >> 24;

        if (hashUpperByte > currentByteValue) {
            indexOfHashForUpperByte[currentByteValue] = 65535;
            numHashesForUpperByte[currentByteValue] = 0;
        } else if (hashUpperByte == currentByteValue) {
            u32 r10 = 1;
            indexOfHashForUpperByte[currentByteValue] = i;
            i++;

            while (i < mCurrentSize) {
                u32 hashUpperByte = mHashCodeArray[i] >> 24;

                if (hashUpperByte != currentByteValue)
                    break;

                r10++;
                i++;
            }

            numHashesForUpperByte[currentByteValue] = r10;

            if (i == mCurrentSize) {
                currentByteValue++;
                break;
            }
        }
    }

    for (u32 i = currentByteValue; i < 256; i++) {
        indexOfHashForUpperByte[i] = 65535;
        numHashesForUpperByte[i] = 0;
    }

    _0 = 1;
}  // namespace MR
