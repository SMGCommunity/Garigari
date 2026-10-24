#include "Game/World/GrandGalaxyMapIconHolder.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include "Game/World/GrandGalaxyMapIcon.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(JMapInfo*, 804E8310, s32, const char*)

namespace {
    static const char* sCsvFileName = "Galaxy";
    static TVec3f sBossRotation = TVec3f(0.0f, 320.0f, 0.0f);
};  // namespace

GrandGalaxyMapIconHolder::GrandGalaxyMapIconHolder() : mCount(), mMapIcons() {
}

void GrandGalaxyMapIconHolder::init() {
    // FIXME
    s32 count = 0;
    JMapInfo* worldInfos[8];

    for (s32 i = 0; i < 8; i++) {
        worldInfos[i] = fn_804E8310(i + 1, ::sCsvFileName);
        count += MR::getCsvDataElementNum(worldInfos[i]);
    }

    s32 mapIdx = 0;

    mCount = count;
    mMapIcons = new GrandGalaxyMapIcon*[mCount];

    for (s32 worldNo = 0; worldNo < 8; worldNo++) {
        for (s32 iconIdx = 0; iconIdx < MR::getCsvDataElementNum(worldInfos[worldNo]); iconIdx++) {
            const char* stageName = nullptr;
            const char* miniatureName = "MiniFlowerHighlandGalaxy";
            const char* stageType = "Galaxy";
            MR::getCsvDataStrOrNULL(&stageName, worldInfos[worldNo], "StageName", iconIdx);
            MR::getCsvDataStrOrNULL(&miniatureName, worldInfos[worldNo], "MiniatureName", iconIdx);
            MR::getCsvDataStrOrNULL(&stageType, worldInfos[worldNo], "StageType", iconIdx);

            GrandGalaxyMapIcon* icon = new GrandGalaxyMapIcon(stageName, miniatureName);

            if (MR::isEqualString(stageType, "BossGalaxyLv3")) {
                icon->setRotation(::sBossRotation);
                icon->setScale(6000.0f);
            }

            if (MR::hasCsvItem(worldInfos[worldNo], "IconOffsetX")) {
                f32 offsetX, offsetY;
                MR::getCsvDataF32(&offsetX, worldInfos[worldNo], "IconOffsetX", iconIdx);
                MR::getCsvDataF32(&offsetY, worldInfos[worldNo], "IconOffsetY", iconIdx);

                icon->mOffsetX = offsetX;
                icon->mOffsetY = offsetY;
            }

            mMapIcons[mapIdx++] = icon;
        }
    }
}

GrandGalaxyMapIcon* GrandGalaxyMapIconHolder::findMapIcon(const char* pName) {
    for (s32 i = 0; i < mCount; i++) {
        if (MR::isEqualString(pName, mMapIcons[i]->mName)) {
            return mMapIcons[i];
        }
    }

    return nullptr;
}
