#pragma once

#include <JSystem/JGeometry/TBox.hpp>

class AreaObj;
class AreaObjContainer;
class AreaObjMgr;
class AreaCubeBoundingBox;
class WaterInfo;

namespace MR {
    bool isAreaFormCube(const AreaObj* pArea);
    bool isAreaFormCylinder(const AreaObj* pArea);
    AreaObjMgr* getAreaObjManager(const char* pManagerName);
    AreaObj* getAreaObj(const char* pManagerName, const TVec3f& rPosition);
    AreaObj* getAreaObjAtPlayerPos(const char* pManagerName);
    bool isInAreaObj(const char* pManagerName, const TVec3f& rPosition);
    bool isExistAreaObj(const char* pManagerName);
    s32 getAreaObjArg(const AreaObj* pArea, s32 argno);
    void tryToUpdatePlayerRestartIdInfo(const TVec3f&); // feels like it doesn't belong here...
    void requestMovementOnAreas(const char* pManagerName);
    void requestMovementOnSoundAreas();
    bool getWaterAreaObj(WaterInfo* pInfo, const TVec3f& rPosition);
    bool getWaterAreaInfo(WaterInfo* pInfo, const TVec3f& rPos, const TVec3f& rGravity, bool skipConnectedArea);
    bool calcWhirlPoolAccelInfo(const TVec3f& rPosition, TVec3f* pOut);
    bool intersectsWaterAreaInfo(const WaterInfo*, const WaterInfo*);
    bool hasNoWaterAreaCube(const WaterInfo* pInfo);
    bool func_80062020(const WaterInfo*, const TVec3f&, const TVec3f&);
    bool func_800621A0(const WaterInfo*, const TVec3f&, const TVec3f&);
    bool func_80062320(const WaterInfo*, const TVec3f&, const TVec3f&);
    bool func_80062480(const WaterInfo*, const TVec3f&, const TVec3f&);
    bool calcAreaMoveVelocity(TVec3f* pVelocity, const TVec3f& rPosition);
    void calcCubePos(const AreaObj* pArea, TVec3f* pOut);
    void calcCubeRotate(const AreaObj* pArea, TVec3f* pOut);
    void calcCubeAxisZ(const AreaObj* pArea, TVec3f* pOut);
    void calcCubeWorldBox(TDirBox3f* pBox, const AreaObj* pArea);
    TBox3f* getCubeLocalBox(const AreaObj* pArea);
    void calcCubeLocalPos(TVec3f* pOut, const AreaObj* pArea, const TVec3f& rPosition);
    void calcSpherePos(TVec3f* pOut, const AreaObj* pArea);
    f32 getSphereRadius(const AreaObj* pArea);
    void calcSphereFrontVec(TVec3f* pOut, const AreaObj* pArea, const TVec3f&);
    void calcCylinderPos(TVec3f* pOut, const AreaObj* pArea);
    void calcCylinderCenterPos(TVec3f* pOut, const AreaObj* pArea);
    void calcCylinderUpVec(TVec3f* pOut, const AreaObj* pArea);
    void calcCylinderFrontVec(TVec3f* pOut, const AreaObj* pArea, const TVec3f&);
    f32 getCylinderRadius(const AreaObj* pArea);
    void calcHemisphereFrontVec(TVec3f* pOut, const AreaObj* pArea, const TVec3f&);
    bool isInPlaneModeCube(const TVec3f& rPos);
    bool isInTowerModeCylinder(const TVec3f& rPos, TVec3f* pOutCenter, TVec3f* pOutUp, f32* pOutRadius);
    void getAreaFrontVec(TVec3f* pOut, const AreaObj* pArea, const TVec3f&);
    void getAreaCenterPos(TVec3f* pOut, const AreaObj* pArea);
};  // namespace MR
