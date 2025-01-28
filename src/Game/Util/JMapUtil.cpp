#include "Util/JMapUtil.hpp"
#include "Util/JMapInfo.hpp"
#include "Util/StringUtil.hpp"
#include "Util/SceneUtil.hpp"

namespace MR {
    bool isValidInfo(const JMapInfoIter &rIter) {
        return rIter.isValid();
    }

    bool getObjectName(const char **pOut, const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }
    
        if (rIter.getValue<const char*>("type", pOut)) {
            return true;
        }
        
        return rIter.getValue<const char*>("name", pOut);
    }

    bool isObjectName(const JMapInfoIter &rIter, const char *pName) {
        const char* name = nullptr;
        if (MR::getObjectName(&name, rIter)) {
            return MR::isEqualString(pName, name);
        }

        return false;
    }
};

namespace {
    bool getJMapInfoArgNoInit(const JMapInfoIter &rIter, const char *pKey, s32 *pOut) {
        s32 val;
        if (!rIter.getValue<s32>(pKey, &val)) {
            return false;
        }

        if (val != -1) {
            *pOut = val;
            return true;
        }

        return false;
    }

    bool getJMapInfoArgNoInit(const JMapInfoIter &rIter, const char *pKey, f32 *pOut) {
        s32 val;
        if (!::getJMapInfoArgNoInit(rIter, pKey, &val)) {
            return false;
        }

        *pOut = val;
        return true;
    }

    bool getJMapInfoArgNoInit(const JMapInfoIter &rIter, const char *pKey, bool *pOut) {
        s32 val;
        if (!::getJMapInfoArgNoInit(rIter, pKey, &val)) {
            return false;
        }

        if (val != -1) {
            *pOut = true;
        }
        else {
            *pOut = false;
        }

        return true;
    }

    bool getJMapInfoArg(const JMapInfoIter &rIter, const char *pKey, s32 *pOut) {
        *pOut = -1;
        return getJMapInfoArgNoInit(rIter, pKey, pOut);
    }

    bool getJMapInfoArg(const JMapInfoIter &rIter, const char *pKey, f32 *pOut) {
        *pOut = -1.0f;
        return getJMapInfoArgNoInit(rIter, pKey, pOut);
    }

    bool getJMapInfoArg(const JMapInfoIter &rIter, const char *pKey, bool *pOut) {
        *pOut = false;
        return getJMapInfoArgNoInit(rIter, pKey, pOut);
    }
};

namespace MR {
    bool isExistJMapInfoArg0(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 temp;
        return rIter.getValue<s32>("Obj_arg0", &temp);
    }

    bool getJMapInfoShapeIdWithInit(const JMapInfoIter &rIter, s32 *pId) {
        *pId = -1;
        return rIter.getValue<s32>("ShapeModelNo", pId);
    }

    bool getJMapInfoAreaIdWithInit(const JMapInfoIter &rIter, s32 *pId) {
        *pId = -1;
        return rIter.getValue<s32>("AreaShapeNo", pId);
    }

    bool getJMapInfoTransLocal(const JMapInfoIter &rIter, TVec3f *pVec) {
        if (!rIter.getValue<f32>("pos_x", &pVec->x)) {
            return false;
        }

        if (!rIter.getValue<f32>("pos_y", &pVec->y)) {
            return false;
        }

        if (!rIter.getValue<f32>("pos_z", &pVec->z)) {
            return false;
        }

        return true;
    }

    bool getJMapInfoTrans(const JMapInfoIter &rIter, TVec3f *pVec) {
        if (!MR::getJMapInfoTransLocal(rIter, pVec)) {
            return false;
        }

        if (MR::isPlacementLocalStage()) {
            MR::getZonePlacementMtx(rIter).mult(*pVec, *pVec);
        }

        return true;
    }

    bool getJMapInfoRotateLocal(const JMapInfoIter &rIter, TVec3f *pVec) {
        if (!rIter.getValue<f32>("dir_x", &pVec->x)) {
            return false;
        }

        if (!rIter.getValue<f32>("dir_y", &pVec->y)) {
            return false;
        }

        if (!rIter.getValue<f32>("dir_z", &pVec->z)) {
            return false;
        }

        return true;
    }

    // MR::getJMapInfoRotate

    bool getJMapInfoScale(const JMapInfoIter &rIter, TVec3f *pVec) {
        if (!rIter.getValue<f32>("scale_x", &pVec->x)) {
            return false;
        }

        if (!rIter.getValue<f32>("scale_y", &pVec->y)) {
            return false;
        }

        if (!rIter.getValue<f32>("scale_z", &pVec->z)) {
            return false;
        }

        return true;
    }

    // MR::getJMapInfoMatrixFromRT
    // MR::getJMapInfoV3f

    bool getJMapInfoArg0WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg0", pOut);
    }

    bool getJMapInfoArg0WithInit(const JMapInfoIter &rIter, f32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg0", pOut);
    }

    bool getJMapInfoArg0WithInit(const JMapInfoIter &rIter, bool *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg0", pOut);
    }

    bool getJMapInfoArg1WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg1WithInit(const JMapInfoIter &rIter, f32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg1WithInit(const JMapInfoIter &rIter, bool *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg2WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg2WithInit(const JMapInfoIter &rIter, f32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg2WithInit(const JMapInfoIter &rIter, bool *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg3WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg3", pOut);
    }

    bool getJMapInfoArg3WithInit(const JMapInfoIter &rIter, bool *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg3", pOut);
    }

    bool getJMapInfoArg4WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg4", pOut);
    }

    bool getJMapInfoArg5WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg5", pOut);
    }

    bool getJMapInfoArg6WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg6", pOut);
    }

    bool getJMapInfoArg7WithInit(const JMapInfoIter &rIter, s32 *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg7", pOut);
    }

    bool getJMapInfoArg7WithInit(const JMapInfoIter &rIter, bool *pOut) {
        return ::getJMapInfoArg(rIter, "Obj_arg7", pOut);
    }

    bool getJMapInfoArg0NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg0", pOut);
    }

    bool getJMapInfoArg0NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg0", pOut);
    }

    bool getJMapInfoArg0NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg0", pOut);
    }

        bool getJMapInfoArg1NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg1NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg1NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg1", pOut);
    }

    bool getJMapInfoArg2NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg2NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg2NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg2", pOut);
    }

    bool getJMapInfoArg3NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg3", pOut);
    }

    bool getJMapInfoArg3NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg3", pOut);
    }

    bool getJMapInfoArg3NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg3", pOut);
    }

    bool getJMapInfoArg4NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg4", pOut);
    }

    bool getJMapInfoArg4NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg4", pOut);
    }

    bool getJMapInfoArg4NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg4", pOut);
    }

    bool getJMapInfoArg5NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg5", pOut);
    }

    bool getJMapInfoArg5NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg5", pOut);
    }

    bool getJMapInfoArg5NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg5", pOut);
    }

    bool getJMapInfoArg6NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg6", pOut);
    }

    bool getJMapInfoArg6NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg6", pOut);
    }

    bool getJMapInfoArg6NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg6", pOut);
    }

    bool getJMapInfoArg7NoInit(const JMapInfoIter &rIter, s32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg7", pOut);
    }

    bool getJMapInfoArg7NoInit(const JMapInfoIter &rIter, f32 *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg7", pOut);
    }

    bool getJMapInfoArg7NoInit(const JMapInfoIter &rIter, bool *pOut) { 
        return ::getJMapInfoArgNoInit(rIter, "Obj_arg7", pOut);
    }

    bool getJMapInfoFollowID(const JMapInfoIter &rIter, s32 *pId) {
        return ::getJMapInfoArg(rIter, "FollowId", pId);
    }

    bool getJMapInfoGroupID(const JMapInfoIter &rIter, s32 *pId) {
        if (!::getJMapInfoArg(rIter, "GroupId", pId)) {
            return MR::getJMapInfoClippingGroupID(rIter, pId);
        }

        return true;
    }

    bool getJMapInfoClippingGroupID(const JMapInfoIter &rIter, s32 *pId) {
        return ::getJMapInfoArg(rIter, "ClippingGroupId", pId);
    }

    bool getJMapInfoDemoGroupID(const JMapInfoIter &rIter, s32 *pId) {
        return ::getJMapInfoArg(rIter, "DemoGroupId", pId);
    }

    bool getJMapInfoLinkID(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("l_id", pId);
    }

    bool getJMapInfoPriorityWithInit(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("Priority", pId);
    }

    bool isConnectedWithRail(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        const char* key = "CommonPath_ID";
        s32 pathID = -1;
        return !::getJMapInfoArgNoInit(rIter, key, &pathID) ? false : pathID != -1;
    }

    bool isExistStageSwitchA(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_A", &id);
        return id != -1;
    }
    
    bool isExistStageSwitchB(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_B", &id);
        return id != -1;
    }

    bool isExistStageSwitchAppear(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_APPEAR", &id);
        return id != -1;
    }

    bool isExistStageSwitchDead(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_DEAD", &id);
        return id != -1;
    }

    bool isExistStageSwitchAwake(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_AWAKE", &id);
        return id != -1;
    }

    bool isExistStageSwitchParam(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_PARAM", &id);
        return id != -1;
    }

    bool isExistMessageId(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "MessageId", &id);
        return id != -1;
    }

    bool isEqualObjectName(const JMapInfoIter  &rIter, const char *pName) {
        const char* name;
        MR::getObjectName(&name, rIter);
        return MR::isEqualStringCase(name, pName);
    }

    bool getJMapInfoCameraSetID(const JMapInfoIter &rIter, s32 *pId) {
        *pId = -1;
        if (!rIter.isValid()) {
            return false;
        }

        return ::getJMapInfoArgNoInit(rIter, "CameraSetId", pId);
    }

    bool getJMapInfoViewGroupID(const JMapInfoIter &rIter, s32 *pId) {
        *pId = -1;
        if (!rIter.isValid()) {
            return false;
        }

        return ::getJMapInfoArgNoInit(rIter, "ViewGroupId", pId);
    }

    bool getJMapInfoMessageID(const JMapInfoIter &rIter, s32 *pId) {
        *pId = -1;
        if (!rIter.isValid()) {
            return false;
        }

        return ::getJMapInfoArgNoInit(rIter, "MessageId", pId);
    }

    bool getJMapInfoParamScale(const JMapInfoIter &rIter, f32 *pScale) {
        *pScale = 1.0f;

        if (!rIter.isValid()) {
            return false;
        }

        f32 scale;
        if (!rIter.getValue<f32>("ParamScale", &scale)) {
            return false;
        }

        *pScale = scale;
        return true;
    }

    s32 getJMapInfoDemoCastID(const JMapInfoIter &rIter) {
        s32 id = -1;
        rIter.getValue<s32>("CastId", &id);
        return id;
    }

    const char* getJMapInfoDemoName(const JMapInfoIter &rIter) {
        const char* str = nullptr;
        rIter.getValue<const char*>("DemoName", &str);
        return str;
    }

    const char* getJMapInfoTimeSheetName(const JMapInfoIter &rIter) {
        const char* str = nullptr;
        rIter.getValue<const char*>("TimeSheetName", &str);
        return str;
    }

    s32 getJMapInfoDemoGroupID(const JMapInfoIter &rIter) {
        s32 id = -1;
        rIter.getValue<s32>("DemoGroupId", &id);
        return id;
    }

    s32 getJMapInfoDemoGroupLinkID(const JMapInfoIter &rIter) {
        s32 id = -1;
        rIter.getValue<s32>("l_id", &id);
        return id;
    }

    bool getJMapInfoDemoSkip(const JMapInfoIter &rIter) {
        s32 id = -1;
        if (!rIter.getValue<s32>("DemoSkip", &id)) {
            return false;
        }
        
        if (id > 0) {
            return true;
        }
        return false;
    }

    bool getJMapInfoRailArg(const JMapInfoIter &rIter, const char *pName, s32 *pOut) {
        s32 val;
        if (!rIter.getValue<s32>(pName, &val)) {
            return false;
        }

        if (val != -1) {
            *pOut = val;
            return true;
        }

        return false;
    }

    bool getJMapInfoRailArg0NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg0", pOut);
    }

    bool getJMapInfoRailArg1NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg1", pOut);
    }

    bool getJMapInfoRailArg2NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg2", pOut);
    }

    bool getJMapInfoRailArg3NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg3", pOut);
    }

    bool getJMapInfoRailArg4NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg4", pOut);
    }

    bool getJMapInfoRailArg5NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg5", pOut);
    }

    bool getJMapInfoRailArg6NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg6", pOut);
    }

    bool getJMapInfoRailArg7NoInit(const JMapInfoIter &rIter, s32 *pOut) {
        return MR::getJMapInfoRailArg(rIter, "path_arg7", pOut);
    }

    bool getJMapInfoRailId(const JMapInfoIter &rIter, s32 *pId) {
        return ::getJMapInfoArg(rIter, "CommonPath_ID", pId);
    }

    bool getJMapInfoNextLinkRailID(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("Path_ID", pId);
    }

    bool isEqualRailUsage(const JMapInfoIter &rIter, const char *pUsage) {
        const char* str = nullptr;
        rIter.getValue<const char*>("usage", &str);
        return MR::isEqualStringCase(str, pUsage);
    }

    void getRailPointPos0(const JMapInfoIter &rIter, TVec3f *pVec) {
        rIter.getValue<f32>("pnt0_x", &pVec->x);
        rIter.getValue<f32>("pnt0_y", &pVec->y);
        rIter.getValue<f32>("pnt0_z", &pVec->z);

        if (MR::isPlacementLocalStage()) {
            MR::getZonePlacementMtx(rIter).mult(*pVec, *pVec);
        }
    }

    void getRailPointPos1(const JMapInfoIter &rIter, TVec3f *pVec) {
        rIter.getValue<f32>("pnt1_x", &pVec->x);
        rIter.getValue<f32>("pnt1_y", &pVec->y);
        rIter.getValue<f32>("pnt1_z", &pVec->z);

        if (MR::isPlacementLocalStage()) {
            MR::getZonePlacementMtx(rIter).mult(*pVec, *pVec);
        }
    }

    void getRailPointPos2(const JMapInfoIter &rIter, TVec3f *pVec) {
        rIter.getValue<f32>("pnt2_x", &pVec->x);
        rIter.getValue<f32>("pnt2_y", &pVec->y);
        rIter.getValue<f32>("pnt2_z", &pVec->z);

        if (MR::isPlacementLocalStage()) {
            MR::getZonePlacementMtx(rIter).mult(*pVec, *pVec);
        }
    }

    bool isLoopRailPathIter(const JMapInfoIter &rIter) {
        const char* str = "";
        rIter.getValue<const char*>("closed", &str);
        return MR::isEqualString(str, "CLOSE");
    }

    bool getLinkObjID(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("Obj_ID", pId);
    }

    bool getMapPartsID(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("MapParts_ID", pId);
    }

    bool getGeneratorID(const JMapInfoIter &rIter, s32 *pId) {
        return rIter.getValue<s32>("GeneratorID", pId);
    }
};
