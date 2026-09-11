// Emit this unit's array destructors after its ordinary functions.
#define MR_ASSIGNABLE_ARRAY_DEFER_DESTRUCTOR
#include "NameObj/NameObjCategoryList.hpp"
#include "NameObj/NameObj.hpp"

namespace {
    ALWAYS_INLINE inline NameObj** findObject(NameObj** first, NameObj** last, NameObj* object) {
        while (first != last && *first != object)
            ++first;
        return first;
    }
}

NameObjCategoryList::NameObjCategoryList(u32 count, const CategoryListInitialTable* table, func callback, bool deferred, const char*) {
    const func callbackCopy = callback;
    mDelegator = new NameObjRealDelegator<func>(callbackCopy);
    _D = deferred;
    _C = 0;
    initTable(count, table);
}

NameObjCategoryList::NameObjCategoryList(u32 count, const CategoryListInitialTable* table, func_const callback, bool deferred, const char*) {
    const func_const callbackCopy = callback;
    mDelegatorConst = new NameObjRealDelegator<func_const>(callbackCopy);
    _D = deferred;
    _C = 0;
    initTable(count, table);
}

NameObjCategoryList::~NameObjCategoryList() {
    delete mDelegator;
}

void NameObjCategoryList::execute(int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[idx];

    if (inf->mList.count == 0) {
        return;
    }

    if (inf->mFunc) {
        (*inf->mFunc)();
    }

    NameObj** arr = inf->mList.array.mArray;

    while (arr != &inf->mList.array.mArray[inf->mList.count]) {
        (*mDelegator)(*arr);
        arr++;
    }
}

void NameObjCategoryList::incrementCheck(NameObj */*unused*/, int index) {
    mInfoTable.mArray[index].mCheck++;
}

void NameObjCategoryList::allocateBuffer() {
    if (_D) {
        for (s32 i = 0; i < mInfoTable.mMaxItems; i++) {
            NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[i];
            u32 size = inf->mCheck;
            NameObj** nameObjArr = new NameObj*[size];
            MR::AssignableArray<NameObj*>* arr = &mInfoTable.mArray[i].mList.array;
            arr->mArray = nameObjArr;
            arr->mMaxItems = size;
        }

        _C = 1;
    }
}

void NameObjCategoryList::add(NameObj *pObj, int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[idx];
    s32 cnt = inf->mList.count++;
    inf->mList.array.mArray[cnt] = pObj;
}
void NameObjCategoryList::remove(NameObj* object, int index) {
    CategoryInfo& info = mInfoTable.mArray[index];
    s32 count = info.mList.count;
    NameObj** begin = info.mList.array.mArray;
    NameObj** current = findObject(begin, begin + count, object);
    const s32 found = current - begin;
    begin[found] = begin[static_cast<u32>(count - 1)];
    --info.mList.count;
}

void NameObjCategoryList::registerExecuteBeforeFunction(const MR::FunctorBase& callback, int index) {
    CategoryInfo& info = mInfoTable.mArray[index];
    info.mFunc = callback.clone(nullptr);
}

bool NameObjCategoryList::fn_80339F80(int index) {
    return mInfoTable.mArray[index].mFunc != nullptr;
}

void NameObjCategoryList::initTable(u32 count, const CategoryListInitialTable *pTable) {
    mInfoTable.mArray = new CategoryInfo[count];
    mInfoTable.mMaxItems = count;

    NameObjCategoryList::CategoryInfo* curInf = &mInfoTable.mArray[0];

    while ((curInf != &mInfoTable.mArray[mInfoTable.mMaxItems])) {
        curInf->mFunc = nullptr;
        curInf++;
    }

    const CategoryListInitialTable* ent = &pTable[0];

    while(ent->mIndex != -1) {
        if (!_D) {
            u32 size = ent->mCount;
            NameObj** arr = new NameObj*[size];
            NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[ent->mIndex];
            inf->mList.array.mArray = arr;
            inf->mList.array.mMaxItems = size;
            _C = 1;
        }

        mInfoTable.mArray[ent->mIndex].mCheck = 0;

        ent++;
    }
}

NameObjCategoryList::CategoryInfo::CategoryInfo() {}

NameObjCategoryList::CategoryInfo::~CategoryInfo() {}

namespace {
    template<typename T>
    void NameObjRealDelegator<T>::operator()(NameObj* pNameObj) {
        (pNameObj->*mNameObjFunc)();
    }
    template void NameObjRealDelegator<func_const>::operator()(NameObj*);
    template void NameObjRealDelegator<func>::operator()(NameObj*);
}

namespace MR {
    template<class T>
    AssignableArray<T>::~AssignableArray() {
        if (mArray != nullptr) {
            delete[] mArray;
        }
    }
}
