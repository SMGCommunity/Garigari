#include "NameObj/NameObjGroup.hpp"
#include "Util/ObjUtil.hpp"

NameObjGroup::NameObjGroup(const char *pGroupName, int maxCount) : NameObj(pGroupName) {
    mMaxCount = 0;
    mObjectCount = 0;
    mObjects = 0;
    initObjArray(maxCount);
}

NameObjGroup::~NameObjGroup() {
    delete[] mObjects;
}

void NameObjGroup::registerObj(NameObj *pObj) {
    mObjects[mObjectCount] = pObj;
    mObjectCount++;
}

void NameObjGroup::clear() {
    for (s32 i = 0; i < mMaxCount; i++) {
        mObjects[i] = nullptr;
    }

    mObjectCount = 0;
}

bool NameObjGroup::isFull() const {
    return mObjectCount == mMaxCount;
}

void NameObjGroup::pauseOffAll() const {
    for (s32 i = 0; i < mObjectCount; i++) {
        MR::requestMovementOn(mObjects[i]);
    }
}

void NameObjGroup::initObjArray(int maxCount) {
    mMaxCount = maxCount;
    mObjects = new NameObj*[maxCount];

    for (s32 i = 0; i < mMaxCount; i++) {
        mObjects[i] = 0;
    }
}
