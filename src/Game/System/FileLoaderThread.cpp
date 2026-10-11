#include "Game/System/FileLoaderThread.hpp"
#include "Game/System/FileRipper.hpp"
#include "Game/Util/FileUtil.hpp"

namespace {
    void* loadFileUsingRipper(RequestFileInfo* pInfo) {
        FileRipper::AllocDirection val = FileRipper::ALLOC_DIRECTION_FORWARD;

        if (pInfo->mAllocDirection != JKRDvdRipper::ALLOC_DIRECTION_FORWARD) {
            val = FileRipper::ALLOC_DIRECTION_BACKWARD;
        }

        return FileRipper::loadToMainRAM(pInfo->mFileName, static_cast< u8* >(pInfo->mFileEntry->mContext), true, pInfo->mFileEntry->mHeap, val);
    }
};  // namespace

FileLoaderThread::FileLoaderThread(int priority, int msgCount, JKRHeap* pHeap) : OSThreadWrapper(0x8000, msgCount, priority, pHeap) {
}

void* FileLoaderThread::run() {
    OSInitFastCast();

    while (true) {
        OSMessage msg;
        OSReceiveMessage(&mQueue, &msg, OS_MESSAGE_BLOCK);
        RequestFileInfo* info = (RequestFileInfo*)msg;

        switch (info->mType) {
        case RequestFileInfo::REQUEST_LOAD:
            loadToMainRAM(info);
            break;
        case RequestFileInfo::REQUEST_MOUNT:
            mountArchiveAndStartCreateResource(info);
            break;
        }
    }
}

void FileLoaderThread::loadToMainRAM(RequestFileInfo* pInfo) {
    pInfo->_88 = 1;
    void* data = ::loadFileUsingRipper(pInfo);
    pInfo->mFileEntry->setContext(data, pInfo->mFileEntry->mHeap);
    pInfo->_88 = 2;
}

void FileLoaderThread::mountArchiveAndStartCreateResource(RequestFileInfo* pInfo) {
    pInfo->_88 = 1;
    void* data = ::loadFileUsingRipper(pInfo);
    MR::createAndAddArchive(data, pInfo->mFileEntry->mHeap, pInfo->mFileName);
    pInfo->mFileEntry->setContext(data, pInfo->mFileEntry->mHeap);
    pInfo->_88 = 2;
}
