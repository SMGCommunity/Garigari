#include "NameObj/NameObjCategoryList.hpp"
#include "NameObj/NameObj.hpp"

void NameObjCategoryList::execute(int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[idx];

    if (inf->_8 == 0) {
        return;
    }

    if (inf->mFunc) {
        (*inf->mFunc)();
    }

    NameObj** arr = inf->mList.mArray;

    while (arr != &inf->mList.mArray[inf->_8]) {
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
            MR::AssignableArray<NameObj*>* arr = &mInfoTable.mArray[i].mList;
            arr->mArray = nameObjArr;
            arr->mMaxItems = size;
        }

        _C = 1;
    }
}

void NameObjCategoryList::add(NameObj *pObj, int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArray[idx];
    s32 cnt = inf->_8++;
    inf->mList.mArray[cnt] = pObj;
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
            inf->mList.mArray = arr;
            inf->mList.mMaxItems = size;
            _C = 1;
        }

        mInfoTable.mArray[ent->mIndex].mCheck = 0;

        ent++;
    }
}

NameObjCategoryList::CategoryInfo::CategoryInfo() { 
    _8 = 0;
}

NameObjCategoryList::CategoryInfo::~CategoryInfo() {

}
