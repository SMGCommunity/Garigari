#pragma once

#include <revolution/types.h>

class JMapInfo;
class LightAreaHolder;
struct PointLightInfo;
class ResourceHolder;
class ActorLightCtrl;
class AreaLightInfo;

class LightFunction {
public:
    static s32 createLightDataParser(JMapInfo**);
    static s32 createZoneDataParser(const char*, JMapInfo**);
    static void getAreaLightLightData(JMapInfo*, int, AreaLightInfo*);
    static const char* getDefaultAreaLightName();
    static void registerLightAreaHolder(LightAreaHolder*);
};
