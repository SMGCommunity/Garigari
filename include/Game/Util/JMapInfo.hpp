#pragma once

#include <revolution.h>

struct JMapItem {
    u32 mHash;        // _0
    u32 mMask;        // _4
    u16 mOffsetData;  // _8
    u8 mShift;        // _A
    u8 mType;         // _B
};

struct JMapData {
    s32 _0;
    s32 mNumData;     // _4
    s32 mDataOffset;  // _8
    u32 _C;
    JMapItem mItems[1];  // _10
};

class JMapInfoIter;

class JMapInfo {
public:
    JMapInfo();

    void attach(const void*);

    int searchItemInfo(const char*) const;

    bool getValueFast(int, int, const char**) const;
    bool getValueFast(int, int, u32*) const;
    bool getValueFast(int, int, s32*) const;
    inline bool getValueFast(int row, int item, f32* value) const ALWAYS_INLINE {
        const JMapItem* field = &mData->mItems[item];
        const char* data = reinterpret_cast< const char* >(mData) + mData->mDataOffset + row * mData->_C;
        *value = *reinterpret_cast< const f32* >(data + field->mOffsetData);
        return true;
    }

    template < typename T >
    inline const bool getValue(int row, const char* key, T* value) const ALWAYS_INLINE {
        int item = searchItemInfo(key);
        if (item < 0) {
            return false;
        }
        return getValueFast(row, item, value);
    }

    u32 getValueType(const char*) const;

    inline s32 getLength() const {
        return mData != nullptr ? mData->_0 : 0;
    }

    const JMapData* mData;  // 0x00
    const char* mName;      // 0x04
};

class JMapInfoIter {
public:
    inline JMapInfoIter() {
    }
    inline JMapInfoIter(const JMapInfo* pInfo, s32 index) : mInfo(pInfo), mIndex(index) {
    }

    template < typename T >
    bool getValue(const char* key, T* value) const NO_INLINE {
        return mInfo->getValue(mIndex, key, value);
    }

    bool isValid() const {
        return mInfo != nullptr && mIndex >= 0 && mIndex < mInfo->getLength();
    }

    const JMapInfo* mInfo;  // 0x00
    s32 mIndex;             // 0x04
};

template <>
inline bool JMapInfoIter::getValue< f32 >(const char* key, f32* value) const {
    const JMapInfo* info = mInfo;
    s32 row = mIndex;
    int item = info->searchItemInfo(key);
    if (item < 0) {
        return false;
    }
    const JMapData* data = info->mData;
    const JMapItem* field = &data->mItems[item];
    const char* entry = reinterpret_cast< const char* >(data) + data->mDataOffset + row * data->_C;
    *value = *reinterpret_cast< const f32* >(entry + field->mOffsetData);
    return true;
}
