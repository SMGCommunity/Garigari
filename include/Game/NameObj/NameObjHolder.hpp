#pragma once
#include <revolution.h>

class NameObj;

typedef void (NameObj::*func)(void);
typedef void (NameObj::*func_const)(void) const;

namespace MR {
    template<class T, int N> struct FixedArray {
        typedef T value_type;
        T elements[N];
        enum { capacity = N };
    };
    template<class Storage> struct Vector : public Storage {
        typedef typename Storage::value_type value_type;
        s32 count;
        Vector() : count(0) {}
        bool isFull() const { return count >= this->capacity; }
        void pop_back() { --count; }
        value_type* begin() { return this->elements; }
        value_type* end() { return begin() + count; }
        value_type* insert(value_type*, const value_type&) NO_INLINE;
    };
}

class NameObjHolder {
public:
    NameObjHolder(int);

    void add(NameObj *);
    void suspendAllObj();
    void resumeAllObj();
    void syncWithFlags();
    void callMethodAllObj(func);
    void clearArray();

    NameObj* find(const char *);

    NameObj** mObjs;    // 0x00
    u32 mMaxObjs;       // 0x04
    s32 mObjCount;      // 0x08
    MR::Vector<MR::FixedArray<NameObj*, 16> > mCache; // 0xC, count at 0x4C
};
