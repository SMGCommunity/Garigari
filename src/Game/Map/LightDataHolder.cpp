#include "Game/Map/LightDataHolder.hpp"
#include "Game/Map/LightFunction.hpp"
#include "Game/Util.hpp"

namespace {
    static const char* sDefaultAreaLightName = "デフォルト";
};  // namespace

LightDataHolder::LightDataHolder() : mLightCount(), mLights() {
}

void LightDataHolder::initLightData() {
    JMapInfo* data = nullptr;
    mLightCount = LightFunction::createLightDataParser(&data);
    mLights = new AreaLightInfo[mLightCount];

    for (s32 i = 0; i < mLightCount; i++) {
        LightFunction::getAreaLightLightData(data, i, &mLights[i]);
    }
}

AreaLightInfo* LightDataHolder::findAreaLight(const char* pName) const {
    for (s32 i = 0; i < mLightCount; i++) {
        AreaLightInfo* curLightInfo = getLightInfo(i);

        if (MR::isEqualString(pName, curLightInfo->mAreaLightName)) {
            return curLightInfo;
        }
    }

    return mLights;
}

const char* LightDataHolder::getDefaultAreaLightName() const {
    return ::sDefaultAreaLightName;
}

s32 LightDataHolder::getDefaultStepInterpolate() const {
    return 30;
}
