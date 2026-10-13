#include "Game/System/GameSystemDataHolder.hpp"
#include "Game/System/GameSystem.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/SingletonHolder.hpp"

namespace {
    void attachResource(JKRMemArchive* pArchive, JMapInfo* pInfo, const char* pName) {
        void* pResource = pArchive->getResource(pName);
        pInfo->attach(pResource);
    }
}  // namespace

GameSystemDataHolder::GameSystemDataHolder()
    : mHeapSizeExcept(), mGalaxyDataTable(), mMarioFaceShipEventDataTable(), mMarioFaceShipEventCastTable(), mGalaxyWorldOrderList(),
      mWorldMapHeapGalaxy(), mWorldMapHeapResource() {
    mHeapSizeExcept = new JMapInfo();
    mGalaxyDataTable = new JMapInfo();
    mMarioFaceShipEventDataTable = new JMapInfo();
    mMarioFaceShipEventCastTable = new JMapInfo();
    mGalaxyWorldOrderList = new JMapInfo();
    mWorldMapHeapGalaxy = new JMapInfo();
    mWorldMapHeapResource = new JMapInfo();
}

void GameSystemDataHolder::init() {
    JKRMemArchive* archive = MR::receiveArchive("/ObjectData/SystemDataTable.arc");

    ::attachResource(archive, mHeapSizeExcept, "/HeapSizeExcept.bcsv");
    ::attachResource(archive, mGalaxyDataTable, "/GalaxyDataTable.bcsv");
    ::attachResource(archive, mMarioFaceShipEventDataTable, "/MarioFaceShipEventDataTable.bcsv");
    ::attachResource(archive, mMarioFaceShipEventCastTable, "/MarioFaceShipEventCastTable.bcsv");
    ::attachResource(archive, mGalaxyWorldOrderList, "/GalaxyWorldOrderList.bcsv");
    ::attachResource(archive, mWorldMapHeapGalaxy, "/WorldMapHeapGalaxy.bcsv");
    ::attachResource(archive, mWorldMapHeapResource, "/WorldMapHeapResource.bcsv");
}

namespace GameSystemDataFunction {
    const JMapInfo* getHeapSizeExcept() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mHeapSizeExcept;
    }

    const JMapInfo* getMarioFaceShipEventDataTable() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mMarioFaceShipEventDataTable;
    }

    const JMapInfo* getMarioFaceShipEventCastTable() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mMarioFaceShipEventCastTable;
    }

    const JMapInfo* getGalaxyWorldOrderList() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mGalaxyWorldOrderList;
    }

    const JMapInfo* getWorldMapHeapGalaxy() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mWorldMapHeapGalaxy;
    }

    const JMapInfo* getWorldMapHeapResource() {
        return SingletonHolder< GameSystem >::get()->mDataHolder->mWorldMapHeapResource;
    }
}  // namespace GameSystemDataFunction
