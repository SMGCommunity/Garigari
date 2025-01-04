#include "System/ResourceInfo.hpp"
#include "Util.hpp"
#include <cstdio>
#include <cstring>

ResFileInfo::ResFileInfo() {
    mName = nullptr;
    mHash = 0;
    mRes = nullptr;
    _8 = 0;
    _4 = 0;
    _C = 0;
}

void ResFileInfo::setName(const char *pName, bool stripExt) {
    size_t len = strlen(pName) + 1;
    mName = new char[len];
    snprintf(mName, len, "%s", pName);

    if (stripExt) {
        char* out = strrchr(mName, '.');

        if (out != nullptr) {
            out[0] = 0;
        }
    }

    mHash = MR::getHashCodeLower(mName);
}

ResTable::ResTable() {
    mResArray = nullptr;
    mResourceNum = 0;
}

void ResTable::newFileInfoTable(u32 num) {
    mResArray = new ResFileInfo[num];
}

ResFileInfo* ResTable::add(const char *pName, void *pRes, bool stripExt) {
    ResFileInfo* info = &mResArray[mResourceNum];
    info->mRes = pRes;
    info->setName(pName, stripExt);
    mResourceNum++;
    return info;
}

const char* ResTable::getResName(u32 idx) const {
    return mResArray[idx].mName;
}

void* ResTable::getRes(u32 idx) const {
    return mResArray[idx].mRes;
}

void* ResTable::getRes(const char *pName) const {
    return findRes(pName);
}

ResFileInfo* ResTable::findFileInfo(const char *pName) const {
    int idx = getResIndex(pName);

    if (idx != -1) {
        return &mResArray[idx];
    }

    return nullptr;
}

ResFileInfo* ResTable::getFileInfo(u32 idx) const {
    return &mResArray[idx];
}

bool ResTable::isExistRes(const char *pName) const {
    return getResIndex(pName) != -1;
}

void* ResTable::findRes(const char *pName) const {
    int idx = getResIndex(pName);

    if (idx != -1) {
        return mResArray[idx].mRes;
    }

    return nullptr;
}

int ResTable::getResIndex(const char *pName) const {
    u32 hash = MR::getHashCodeLower(pName);

    for (u32 i = 0; i < mResourceNum; i++) {
        u32 curHash = mResArray[i].mHash;

        if (curHash == hash) {
            return i;
        }
    }

    return -1;
}

const char* ResTable::findResName(const void *pRes) const {
    for (u32 i = 0; i < mResourceNum; i++) {
        ResFileInfo* inf = &mResArray[i];
        if (pRes == inf->mRes) {
            return inf->mName;
        }
    }

    return 0;
}

const char* ResTable::getResName(const void *pRes) const {
    return findResName(pRes);
}
