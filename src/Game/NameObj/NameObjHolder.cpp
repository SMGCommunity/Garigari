#include "NameObj/NameObj.hpp"
#include "NameObj/NameObjHolder.hpp"
#include "Util/ObjUtil.hpp"

NameObjHolder::NameObjHolder(int a1) : 
    mObjs(0), mMaxObjs(0), mObjCount(0), _4C(0) {
        mObjs = new NameObj*[a1];
        mMaxObjs = a1;
    }

void NameObjHolder::add(NameObj *pObj) {
    u32 count = mObjCount;
    mObjCount = count + 1;
    mObjs[count] = pObj;
}

void NameObjHolder::suspendAllObj() {
    for (s32 i = 0; i < mObjCount; i++) {
        MR::requestMovementOff(mObjs[i]);
    }
}

void NameObjHolder::resumeAllObj() {
    for (s32 i = 0; i < mObjCount; i++) {
        MR::requestMovementOn(mObjs[i]);
    }
}

void NameObjHolder::syncWithFlags() {
    callMethodAllObj(&NameObj::syncWithFlags);
}

/*
void NameObjHolder::callMethodAllObj(func functionPtr) {
    func function = functionPtr;

    NameObj** start = mObjs;
    NameObj** end = &mObjs[mObjCount];
    function = functionPtr;

    while (start != end) {
        (*start->*function)();
        start++;
    }
}
*/

void NameObjHolder::clearArray() {
    mObjCount = 0;
    _4C = 0;
}
