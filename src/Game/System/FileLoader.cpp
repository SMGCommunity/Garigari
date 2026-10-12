#include "Game/System/FileLoader.hpp"
#include "Game/System/FileLoaderThread.hpp"
#include "Game/Util/MemoryUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <cstdio>

FileLoader::FileLoader() {
    mLoaderThread = nullptr;
    mRequestFileInfos = nullptr;
    mRequestedFileCount = 0;
    mFileHolder = nullptr;
    mArchiveHolder = nullptr;
    mLoaderThread = new FileLoaderThread(13, 360, MR::getStationedHeapNapa());
    OSResumeThread(mLoaderThread->mThread);
    OSInitMutex(&mMutex);
    mRequestFileInfos = new RequestFileInfo[360];
    mFileHolder = new FileHolder();
    mArchiveHolder = new ArchiveHolder();
    mRequestedFileCount = 0;
}

void FileLoader::requestLoadToMainRAM(const char* pName, u8* pData, JKRHeap* pHeap, JKRDvdRipper::EAllocDirection direction, bool jam) {
    if (pHeap == nullptr) {
        pHeap = MR::getCurrentHeap();
    }

    if (isNeedToLoad(pName)) {
        RequestFileInfo* info = addRequest(pName);
        info->mType = RequestFileInfo::REQUEST_LOAD;
        info->mAllocDirection = direction;
        info->mFileEntry = mFileHolder->add(pName, pHeap, pData);

        if (jam) {
            OSJamMessage(&mLoaderThread->mQueue, info, OS_MESSAGE_NOBLOCK);
        } else {
            OSSendMessage(&mLoaderThread->mQueue, info, OS_MESSAGE_NOBLOCK);
        }
    }
}

void FileLoader::requestMountArchive(const char* pName, JKRHeap* pHeap, JKRDvdRipper::EAllocDirection direction, bool jam) {
    if (pHeap == nullptr) {
        pHeap = MR::getCurrentHeap();
    }

    if (isNeedToLoad(pName)) {
        RequestFileInfo* info = addRequest(pName);
        info->mType = RequestFileInfo::REQUEST_MOUNT;
        info->mAllocDirection = direction;
        info->mFileEntry = mFileHolder->add(pName, pHeap, nullptr);

        if (jam) {
            OSJamMessage(&mLoaderThread->mQueue, info, OS_MESSAGE_NOBLOCK);
        } else {
            OSSendMessage(&mLoaderThread->mQueue, info, OS_MESSAGE_NOBLOCK);
        }
    }
}

void* FileLoader::receiveFile(const char* pName) {
    const RequestFileInfo* info = getRequestFileInfoConst(pName);
    if (info != nullptr) {
        info->mFileEntry->waitReadDone();
    }

    return mFileHolder->getContext(pName);
}

JKRMemArchive* FileLoader::receiveArchive(const char* pName) {
    const RequestFileInfo* info = getRequestFileInfoConst(pName);
    if (info != nullptr) {
        info->mFileEntry->waitReadDone();
    }

    return mArchiveHolder->getArchive(pName);
}

void FileLoader::receiveAllRequestedFile() {
    for (u32 i = 0; i < mRequestedFileCount; i++) {
        mRequestFileInfos[i].mFileEntry->waitReadDone();
    }
}

JKRMemArchive* FileLoader::createAndAddArchive(void* pData, JKRHeap* pHeap, const char* pName) {
    return mArchiveHolder->createAndAdd(pData, pHeap, pName)->mArchive;
}

void FileLoader::getMountedArchiveAndHeap(const char* pName, JKRArchive** pArchive, JKRHeap** pHeap) const {
    mArchiveHolder->getArchiveAndHeap(pName, pArchive, pHeap);
}

void FileLoader::clearRequestFileInfo(bool) {
    mRequestedFileCount = nullptr;
}

void FileLoader::removeHolderIfIsEqualHeap(JKRHeap* pHeap) {
    mFileHolder->removeIfIsEqualHeap(pHeap);
    mArchiveHolder->removeIfIsEqualHeap(pHeap);
}

void FileLoader::removeFile(const char* pName) {
    mFileHolder->removeFile(pName);
    mArchiveHolder->removeArchive(pName);
}

bool FileLoader::isNeedToLoad(const char* pName) const {
    if (getRequestFileInfoConst(pName) != nullptr) {
        return false;
    }

    return !mFileHolder->isExist(pName);
}

const RequestFileInfo* FileLoader::getRequestFileInfoConst(const char* pName) const {
    for (u32 i = 0; i < mRequestedFileCount; i++) {
        RequestFileInfo* info = &mRequestFileInfos[i];

        if (MR::isEqualStringCase(info->mFileName, pName)) {
            return info;
        }
    }

    return nullptr;
}

RequestFileInfo* FileLoader::addRequest(const char* pName) {
    OSMutex* mutex = &mMutex;
    OSLockMutex(mutex);

    RequestFileInfo* info = &mRequestFileInfos[mRequestedFileCount];
    mRequestedFileCount++;
    info->mFileEntry = nullptr;
    info->_88 = 0;
    snprintf(info->mFileName, sizeof(info->mFileName), "%s", pName);

    OSUnlockMutex(mutex);

    return info;
}
