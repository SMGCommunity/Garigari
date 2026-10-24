#include "Game/World/GrandGalaxyMapIconHolder.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include "Game/World/GrandGalaxyMapIcon.hpp"
#include "decomp.h"

EXTERN_UNKNOWN_FUNC(JMapInfo*, 804E8310, s32, const char*)

namespace {
    static const char* sCsvFileName = "Galaxy";
    static TVec3f sBossRotation = TVec3f(0.0f, 320.f, 0.0f);
};  // namespace

GrandGalaxyMapIconHolder::GrandGalaxyMapIconHolder() : mCount(), mMapIcons() {
}

void GrandGalaxyMapIconHolder::init() {
    // FIXME
    s32 count;
    JMapInfo* infos[8];
    for (s32 i = 0; i < 8; i++) {
        infos[i] = fn_804E8310(i + 1, ::sCsvFileName);
        count += MR::getCsvDataElementNum(infos[i]);
    }

    mCount = count;
    mMapIcons = new GrandGalaxyMapIcon*[mCount];

    for (s32 i = 0; i < 8; i++) {
        for (s32 j = 0; j < MR::getCsvDataElementNum(infos[i]); j++) {
            const char* stageName = nullptr;
            const char* miniatureName = "MiniFlowerHighlandGalaxy";
            const char* stageType = "Galaxy";
            MR::getCsvDataStrOrNULL(&stageName, infos[i], "StageName", j);
            MR::getCsvDataStrOrNULL(&miniatureName, infos[i], "MiniatureName", j);
            MR::getCsvDataStrOrNULL(&miniatureName, infos[i], "StageType", j);

            GrandGalaxyMapIcon* icon = new GrandGalaxyMapIcon(stageName, miniatureName);

            if (MR::isEqualString(stageType, "BossGalaxyLv3")) {
                icon->setRotation(::sBossRotation);
                icon->setScale(6000.0f);
            }

            if (MR::hasCsvItem(infos[i], "IconOffsetX")) {
                f32 offsetX, offsetY;
                MR::getCsvDataF32(&offsetX, infos[i], "IconOffsetX", j);
                MR::getCsvDataF32(&offsetY, infos[i], "IconOffsetY", j);

                icon->mOffsetX = offsetX;
                icon->mOffsetY = offsetY;
            }

            mMapIcons[i] = icon;
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
