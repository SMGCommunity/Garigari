#pragma once
#include "Game/Util/Array.hpp"
#include <revolution.h>

class NameObj;

typedef void (NameObj::*func)(void);
typedef void (NameObj::*func_const)(void) const;

class NameObjHolder {
public:
    NameObjHolder(s32);

    void add(NameObj*);
    void suspendAllObj();
    void resumeAllObj();
    void syncWithFlags();
    void callMethodAllObj(func);
    void clearArray();
    NameObj* find(const char*);

    /* 0x00 */ MR::Vector< MR::AssignableArray< NameObj* > > mObjArray1;
    /* 0x0C */ MR::Vector< MR::FixedArray< NameObj*, 16 > > mObjArray2;
};
