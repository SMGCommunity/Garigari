#include "Game/NameObj/NameObjCategoryList.hpp"
#include "Game/NameObj/NameObj.hpp"

void NameObjCategoryList::execute(int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArr[idx];

    if (inf->_8 == 0) {
        return;
    }

    if (inf->mFunc) {
        (*inf->mFunc)();
    }

    NameObj** arr = inf->mList.mArr;

    while (arr != &inf->mList.mArr[inf->_8]) {
        (*mDelegator)(*arr);
        arr++;
    }
}

void NameObjCategoryList::incrementCheck(NameObj* /*unused*/, int index) {
    mInfoTable.mArr[index].mCheck++;
}

void NameObjCategoryList::allocateBuffer() {
    if (_D) {
        for (s32 i = 0; i < mInfoTable.size(); i++) {
            NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArr[i];
            u32 size = inf->mCheck;
            NameObj** nameObjArr = new NameObj*[size];
            MR::AssignableArray< NameObj* >* arr = &mInfoTable.mArr[i].mList;
            arr->mArr = nameObjArr;
            arr->mMaxSize = size;
        }

        _C = 1;
    }
}

void NameObjCategoryList::add(NameObj* pObj, int idx) {
    NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArr[idx];
    s32 cnt = inf->_8++;
    inf->mList.mArr[cnt] = pObj;
}
void NameObjCategoryList::initTable(u32 count, const CategoryListInitialTable* pTable) {
    mInfoTable.mArr = new CategoryInfo[count];
    mInfoTable.mMaxSize = count;

    NameObjCategoryList::CategoryInfo* curInf = &mInfoTable.mArr[0];

    while ((curInf != &mInfoTable.mArr[mInfoTable.mMaxSize])) {
        curInf->mFunc = nullptr;
        curInf++;
    }

    const CategoryListInitialTable* ent = &pTable[0];

    while (ent->mIndex != -1) {
        if (!_D) {
            u32 size = ent->mCount;
            NameObj** arr = new NameObj*[size];
            NameObjCategoryList::CategoryInfo* inf = &mInfoTable.mArr[ent->mIndex];
            inf->mList.mArr = arr;
            inf->mList.mMaxSize = size;
            _C = 1;
        }

        mInfoTable.mArr[ent->mIndex].mCheck = 0;

        ent++;
    }
}

NameObjCategoryList::CategoryInfo::CategoryInfo() {
    _8 = 0;
}

NameObjCategoryList::CategoryInfo::~CategoryInfo() {
}
