#include "Game/AreaObj/LightAreaHolder.hpp"
#include "Game/AreaObj/LightArea.hpp"
#include "Game/Map/LightFunction.hpp"
#include "Game/Map/LightZoneDataHolder.hpp"

LightAreaHolder::LightAreaHolder(s32 maxNum, const char* pName) : AreaObjMgr(maxNum, pName) {
    LightFunction::registerLightAreaHolder(this);
}

bool LightAreaHolder::tryFindLightID(const TVec3f& rArea, ZoneLightID* pLightID) const {
    AreaObj* pArea = find_in(rArea);

    if (pArea == nullptr) {
        if (pLightID->isOutOfArea()) {
            pLightID->clear();

            return false;
        } else {
            pLightID->clear();

            return true;
        }
    } else {
        const LightArea* pLightArea = static_cast< LightArea* >(pArea);

        if (pLightID->isTargetArea(pLightArea)) {
            return false;
        } else {
            pLightID->mZoneID = pLightArea->mLinkInfo.mZoneId;
            pLightID->mLightID = pLightArea->mObjArg0;

            return true;
        }
    }
}

void LightAreaHolder::initAfterPlacement() {
}
