#include "NameObj/NameObj.hpp"
#include "NameObj/NameObjHolder.hpp"
#include "Util/ObjUtil.hpp"
#include "Util/HashUtil.hpp"
#include <cstring>

NameObjHolder::NameObjHolder(int a1) : 
    mObjs(0), mMaxObjs(0), mObjCount(0) {
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

namespace {
    struct HolderMethod {
        func method;
        HolderMethod(func value) : method(value) {}
        void operator()(NameObj* object) const { (object->*method)(); }
    };
    ALWAYS_INLINE HolderMethod callMethods(NameObj** begin, NameObj** end, HolderMethod method) {
        for (; begin != end; ++begin) method(*begin);
        return method;
    }
}

void NameObjHolder::callMethodAllObj(func method) {
    callMethods(mObjs, mObjs + mObjCount, HolderMethod(method));
}

void NameObjHolder::clearArray() {
    mObjCount = 0;
    mCache.count = 0;
}

namespace {
    struct equal_fullname {
        u32 hash;
        const char* name;
        equal_fullname(const char* value) : hash(MR::getHashCode(value)), name(value) {}
        bool operator()(NameObj* object) const { return strcmp(object->mName, name) == 0; }
    };
}
namespace std {
    template<class Iter, class Predicate>
    Iter find_if(Iter first, Iter last, Predicate predicate) NO_INLINE {
        while (first != last && !predicate(*first)) ++first;
        return first;
    }
}
namespace MR {
    template<class Storage>
    typename Vector<Storage>::value_type* Vector<Storage>::insert(value_type* position, const value_type& value) {
        value_type* cursor = end();
        while (cursor != position) {
            *cursor = *(cursor - 1);
            --cursor;
        }
        *position = value;
        ++count;
        return position;
    }
}

NameObj* NameObjHolder::find(const char* name) {
    NameObj** found = std::find_if(mCache.begin(), mCache.end(), equal_fullname(name));
    if (found != mCache.end()) {
        NameObj* object = *found;
        if (mCache.end() - found - 1 > 0) {
            while (found + 1 != mCache.end()) {
                *found = *(found + 1);
                ++found;
            }
        }
        --mCache.count;
        mCache.insert(mCache.begin(), object);
        return object;
    }
    found = std::find_if(mObjs, mObjs + mObjCount, equal_fullname(name));
    if (found == mObjs + mObjCount) return nullptr;
    NameObj* object = *found;
    if (mCache.isFull()) mCache.pop_back();
    mCache.insert(mCache.begin(), object);
    return object;
}
