#include "Game/Util/HashUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include <cctype>

HashSortTable::HashSortTable(u32 size) {
    mHashCodeArray = new u32[size];
    mValueArray = new u32[size];
    indexFirstHashForUpperByte = new u16[256];
    numHashesForUpperByte = new u16[256];
    mCurrentSize = 0;
    mMaxSize = size;
    hasBeenSorted = false;
}

bool HashSortTable::add(const char* pName, u32 value, bool skip) {
    u32 hashCode = MR::getHashCode(pName);
    if (skip) {
        return addOrSkip(hashCode, value);
    } else {
        return add(hashCode, value);
    }
}

bool HashSortTable::add(u32 hashCode, u32 value) {
    mHashCodeArray[mCurrentSize] = hashCode;
    mValueArray[mCurrentSize] = value;
    mCurrentSize++;
    return true;
}

bool HashSortTable::addOrSkip(u32 hashCode, u32 value) {
    for (u32 i = 0; i < mCurrentSize; i++) {
        if (hashCode == mHashCodeArray[i]) {
            return false;
        }
    }

    mHashCodeArray[mCurrentSize] = hashCode;
    mValueArray[mCurrentSize] = value;
    mCurrentSize++;
    return true;
}

void HashSortTable::sort() {
    if (mCurrentSize == 0)
        return;

    s32 indexArray[0x400];
    /*
    Once this function is complete, indexArray[0] will contain the index of the lowest hash code in mHashCodeArray,
    indexArray[1] will contain the index of the second-lowest hash code, and so on.
    */
    MR::sortSmall(mCurrentSize, mHashCodeArray, indexArray);

    /*
    The values in mValueArray will be transferred here (in the order indicated in indexArray) 
    before being copied back into mValueArray.
    */
    u32 sortedArray[0x400];
    for (int i = 0; i < mCurrentSize; i++) {
        sortedArray[i] = mValueArray[indexArray[i]];
    }

    for (int i = 0; i < mCurrentSize; i++) {
        mValueArray[i] = sortedArray[i];
    }

    u32 i = 0; //< Index in mHashCodeArray
    u32 currentByteValue;

    // Cycle through every possible byte (0 through 255)
    for (currentByteValue = 0; currentByteValue < 256; currentByteValue++) {
        u32 hashUpperByte = mHashCodeArray[i] >> 24;

        /*
        If the first hash code we encounter has an upper byte higher than currentByteValue,
        there is no hash code with an upper byte equal to currentByteValue.
        */
        if (hashUpperByte > currentByteValue) {
            // No hash codes with this upper byte
            indexFirstHashForUpperByte[currentByteValue] = 65535;
            numHashesForUpperByte[currentByteValue] = 0;
        } else if (hashUpperByte == currentByteValue) {
            u32 numHashes = 1;  // We now know there is at least 1 hash code with this upper byte.
            indexFirstHashForUpperByte[currentByteValue] = i;   // Store the index of the first one we found
            i++;

            /*
            Keep advancing through mHashCodeArray until we find a hash code whose upper byte is greater than currentByteValue.
            We'll keep track of how many hash codes we ended up finding with an upper byte equal to currentByteValue.
            Then, we can move on to the next currentByteValue.
            */
            while (i < mCurrentSize) {
                u32 hashUpperByte = mHashCodeArray[i] >> 24;

                if (hashUpperByte != currentByteValue)
                    break;

                numHashes++;
                i++;
            }

            numHashesForUpperByte[currentByteValue] = numHashes;

            if (i == mCurrentSize) {
                currentByteValue++;
                break;
            }
        }
    }

    /*
    If we've gotten all the way to the end of mHashCodeArray and haven't gotten through all possible bytes,
    then there are zero hash codes whose upper bytes match any of the remaining possible bytes.
    */
    for (u32 i = currentByteValue; i < 256; i++) {
        indexFirstHashForUpperByte[i] = 65535;
        numHashesForUpperByte[i] = 0;
    }

    hasBeenSorted = true;
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
