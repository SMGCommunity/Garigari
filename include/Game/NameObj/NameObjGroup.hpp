#pragma once

#include "NameObj/NameObj.hpp"

class NameObjGroup : public NameObj {
public:
    NameObjGroup(const char *, int);

    virtual ~NameObjGroup();

    void registerObj(NameObj *);
    void clear();
    bool isFull() const;
    void pauseOffAll() const;
    void initObjArray(int);

    s32 getObjectCount() const {
        return mObjectCount;
    }

    template<typename T>
    T getObj(s32 idx) const {
        return reinterpret_cast<T>(mObjects[idx]);
    }

    s32 mMaxCount;      // 0x14
    s32 mObjectCount;   // 0x18
    NameObj** mObjects; // 0x1C
};
