#pragma once

#include "Util/Array.hpp"
#include "NameObj/NameObj.hpp"
#include "Util/Functor.hpp"

typedef void (NameObj::*func)(void);
typedef void (NameObj::*func_const)(void) const;

namespace {
    template<typename T>
    class NameObjRealDelegator {
    public:
        inline NameObjRealDelegator(T in_func) {
            mNameObjFunc = in_func;
        }

        virtual void operator()(NameObj *pNameObj) {
            (pNameObj->*mNameObjFunc)();
        }

        T mNameObjFunc; // 0x4
    };
};

struct CategoryListInitialTable {
    u32 mIndex;     // 0x0
    u32 mCount;     // 0x4
};

class NameObjCategoryList {
public:
    class CategoryInfo {
    public:
        CategoryInfo();
        ~CategoryInfo();

        MR::AssignableArray<NameObj*> mList;                    // 0x00
        s32 _8;
        MR::FunctorBase* mFunc;                                 // 0x0C
        u32 mCheck;                                             // 0x10
    };

    void execute(int);
    void incrementCheck(NameObj *, int);
    void allocateBuffer();
    void add(NameObj *, int);
    void remove(NameObj *, int);
    void registerExecuteBeforeFunction(const MR::FunctorBase &, int);
    bool fn_80339F80(int);
    void initTable(u32, const CategoryListInitialTable *);

    MR::AssignableArray<NameObjCategoryList::CategoryInfo> mInfoTable;      // 0x00

    union {
        NameObjRealDelegator<func>* mDelegator;
        NameObjRealDelegator<func_const>* mDelegatorConst;
    };

    u8 _C;
    u8 _D;
};
