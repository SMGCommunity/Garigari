#pragma once

#include "Game/Map/WaterInfo.hpp"
#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class OceanSphere;
class WaterCameraFilter;
class WaterStream;

class WaterAreaHolder : public NameObj {
public:
    WaterAreaHolder();

    virtual void movement();

    void entryOceanSphere(OceanSphere*);
    void entryWaterStream(WaterStream*);  // NEW to SMG2

    s32 mNumOceanSpheres;
    OceanSphere** mOceanSpheres;
    s32 mNumWaterStreams;
    WaterStream** mWaterStreams;
    bool mCamInWater;
    WaterInfo mWaterInfo;
    WaterCameraFilter* mCameraFilter;
    bool mUseBloom; // Enabled if in HeavenlyBeachGalaxy OR OceanRingGalaxy... Even though neither exist in SMG2
};

namespace WaterAreaFunction {
    void entryOceanSphere(OceanSphere*);
    void entryWaterStream(WaterStream*);  // NEW to SMG2
    void createWaterAreaHolder();
    bool tryInOceanArea(const TVec3f&, WaterInfo*);
    bool isCameraInWaterForCameraUtil();
    f32 getCameraWaterDepth();
    WaterInfo* getCameraWaterInfo();
    void pauseOffWaterArea();
};  // namespace WaterAreaFunction
