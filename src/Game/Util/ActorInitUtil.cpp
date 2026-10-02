#include "Util/ActorInitUtil.hpp"
#include "LiveActor/ActorActionKeeper.hpp"
#include "LiveActor/Binder.hpp"
#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/HitSensorInfo.hpp"
#include "LiveActor/ActorLightCtrl.hpp"
#include "LiveActor/LiveActor.hpp"
#include "Util.hpp"
#include "Util/JMapInfo.hpp"
#include "Util/ActorSwitchUtil.hpp"
#include "Util/MtxUtil.hpp"
#include <cstdio>

namespace MR {
    bool isDataEnable(JMapInfo *pInfo, const char *pName) {
        if (!MR::isExistElement(pInfo, "InitFunction", pName)) {
            return false;
        }

        const char* str = nullptr;
        MR::getCsvDataStrByElement(&str, pInfo, "InitFunction", pName, "Data");
        return str[0] == 'o';
    }

}

namespace {
    const MR::ObjConnection cConnections[] = {
        { "MapObj", 33, 5, 9, -1 },
        { "MapObjStrongLight", 33, 5, 11, -1 },
        { "MapObjNoShadow", 33, 5, 13, -1 },
        { "MapObjNoSilhouetted", 33, 5, 16, -1 },
        { "MapObjDecoration", 34, 11, 11, -1 },
        { "MapObjNoCalcAnim", 33, -1, 9, -1 },
        { "MapObjMovement", 33, -1, -1, -1 },
        { "MapObjNoMovement", -1, 5, 9, -1 },
        { "MapObjIndirect", 33, 5, 26, -1 },
        { "MapObjIndirectStrongLight", 33, 5, 27, -1 },
        { "MapObjNoMovementNoCalcAnimIndirectStrongLight", -1, -1, 27, -1 },
        { "ClippedMapParts", 27, 0, 0, -1 },
        { "CollisionMapObj", 29, 2, 9, -1 },
        { "CollisionMapObjWeakLight", 29, 2, 10, -1 },
        { "CollisionMapObjNoShadow", 29, 5, 12, -1 },
        { "CollisionMapObjNoShadowNoCalcAnim", 29, -1, 13, -1 },
        { "CollisionMapObjIndirectNoCalcAnim", 29, -1, 27, -1 },
        { "Enemy", 41, 8, 19, -1 },
        { "EnemyDecoration", 42, 11, 20, -1 },
        { "EnemyIndirect", 41, 8, 29, -1 },
        { "EnemySilhouette", 41, 8, 19, 44 },
        { "EnemyNoShadow", 41, 8, 13, -1 },
        { "EnemyNoMovement", -1, 8, 19, -1 },
        { "Boss", 41, 8, 19, -1 },
        { "Npc", 39, 6, 17, -1 },
        { "NpcNoShadow", 39, 6, 13, -1 },
        { "NpcNoCalcAnim", 39, -1, 17, -1 },
        { "Ride", 40, 7, 18, -1 },
        { "RideSilhouette", 40, 7, 18, 44 },
        { "Planet", 28, 1, 5, -1 },
        { "PlanetIndirect", 28, 1, 30, -1 },
        { "DynamicMapObj", 33, 5, -1, 35 },
        { "PlayerDecoration", 37, 10, 22, -1 },
        { "Item", 43, 15, 14, -1 },
        { "Bloom", 34, 11, 31, -1 },
        { "BossBussun", 41, 8, 1, -1 },
        { "CrystalItem", 34, 11, 34, -1 },
        { "FireBarBall", 33, 5, 12, -1 },
        { "GliBird", 41, 7, 18, -1 },
        { "HipDropStarMove", 33, 5, 9, 34 },
        { "StoryBook", 39, 6, 38, -1 },
        { "StoryBookFilter", 39, -1, 9, -1 },
        { "WorldMapMiniObj", 47, 20, 39, -1 },
        { "GhostMazeMask", 33, 5, 23, -1 },
        { "Crystal", 33, 5, 33, -1 },
        { "Tamakoro", 40, 7, 27, -1 },
        { "SuperDreamer", 45, 6, 17, -1 },
        { "Ghost2DWater", 41, 8, 19, -1 },
        { "WoodLogBridge", 33, -1, -1, 33 },
    };

    const MR::ObjLight cLightTable[] = {
        { "プレイヤー", "Player", 0 },
        { "目立たせ", "Strong", 1 },
        { "なじませ", "Weak", 2 },
        { "惑星", "Planet", 3 },
    };


    struct SensorType {
        const char* mName;
        u32 mType;
    };

    const SensorType cSensorTypes[] = {
        { "Binder", 91 },
        { "Enemy", 24 },
        { "EnemyAttack", 26 },
        { "EnemySimple", 25 },
        { "MapObj", 64 },
        { "MapObjPress", 113 },
        { "MapObjSimple", 65 },
        { "Message", 126 },
        { "Npc", 8 },
        { "Ride", 12 },
        { "Eye", 122 },
        { "Pukupuku", 39 },
        { "KillerTargetMapObj", 78 },
        { "PriorBinder", 93 },
        { "Switch", 73 },
        { "Push", 123 },
        { "BellyDragonHead", 55 },
        { "BellyDragonBody", 56 },
        { "BellyDragonWeakPoint", 57 },
        { "KoopaJrRobot", 51 },
        { "KoopaJrCastle", 53 },
        { "KoopaJrCastleTire", 54 },
        { "BossBussunShotCollision", 85 },
        { "Ghost", 21 },
        { "HipDropStar", 60 },
        { "JumpHole", 116 },
        { "Karikari", 32 },
        { "KinokoOneUp", 71 },
        { "Kuribo", 31 },
        { "LeafBoard", 52 },
        { "PunchBox", 79 },
        { "SandBird", 83 },
        { "SnowStep", 82 },
        { "SpherePlayer", 13 },
        { "SpherePlayerBind", 96 },
        { "SpherePlayerHit", 14 },
        { "SpinCloudBlock", 86 },
        { "SupportTico", 61 },
    };

    inline u32 getSensorType(const char* pName) ALWAYS_INLINE {
        for (u32 i = 0; i < 38; i++) {
            const SensorType* type = &cSensorTypes[i];
            if (MR::isEqualString(pName, type->mName)) {
                return type->mType;
            }
        }
        return 0x40;
    }

    inline JMapInfoIter getInitFunction(const char** value, const JMapInfo* info, const char* name) ALWAYS_INLINE {
        JMapInfoIter iter = MR::getCsvDataStrByElement(value, info, "InitFunction", name, "Data");
        return iter;
    }

    inline s32 getConnectionIdx(const char *pName) ALWAYS_INLINE {
        for (u32 i = 0; i < 0x31; i++) {
            const MR::ObjConnection* c = &cConnections[i];
            if (MR::isEqualString(pName, c->mObjType)) {
                return i;
            }
        }

        return -1;
    }

    inline s32 getLightIDIdx(const char *pLight) ALWAYS_INLINE {
        for (u32 i = 0; i < 4; i++) {
            const MR::ObjLight* c = &cLightTable[i];
            if (MR::isEqualString(pLight, c->mTypeStr)) {
                return i;
            }
        }

        return 3;
    }
};

namespace MR {
    bool getInitSwitchType(const char **pSwitchType, const JMapInfo *pInfo, const char *pName) {
        MR::getCsvDataStrByElement(pSwitchType, pInfo, "SwitchName", pName, "UseType");
        return *pSwitchType[0] != 'x';
    }

    bool initActor(LiveActor *pActor, const JMapInfoIter &rIter, bool a3) {
        const char* objName = nullptr;
        MR::getObjectName(&objName, rIter);
        return initActor(pActor, rIter, objName, nullptr, nullptr, a3);
    }

    bool initActor(LiveActor *pActor, const JMapInfoIter &rIter, const char *pObjName, bool a4) {
        return initActor(pActor, rIter, pObjName, nullptr, nullptr, a4);
    }

    bool initActor(LiveActor *pActor, const JMapInfoIter &rIter, const char *pObjName, const char *a4, bool a5) {
        return initActor(pActor, rIter, pObjName, nullptr, a4, a5);
    }

    bool initActor(LiveActor *pActor, const char *pObjName, bool a3) {
        JMapInfoIter iter(0, -1);
        return initActor(pActor, iter, pObjName, nullptr, nullptr, a3);
    }

    bool initActor(LiveActor *pActor, const char *pObjName, const char *a3, bool a4) {
        JMapInfoIter iter(0, -1);
        return initActor(pActor, iter, pObjName, nullptr, a3, a4);
    }

    JMapInfo* makeInitActorCsvParser(const char *a1, const char *pSubFile) {
        const char* csv = "InitActor.bcsv";

        if (pSubFile != nullptr) {
            char buf[64];
            snprintf(buf, sizeof(buf), "InitActor%s.bcsv", pSubFile);
            csv = buf;
        }

        return createCsvParserFromFile(a1, csv);
    }

    bool isValidInitActorCsvParser(const char *a1, const char *pSubFile) {
        return makeInitActorCsvParser(a1, pSubFile) != nullptr;
    }

    /* https://decomp.me/scratch/xGEnY */
    bool initActor(LiveActor *pActor, const JMapInfoIter &rIter, const char *pArchiveName, const char* a4, const char *a5, bool a6) {
        bool flag = false;
        char archiveName[0x80];
        snprintf(archiveName, sizeof(archiveName), "%s.arc", pArchiveName);

        const char* name = pArchiveName;

        if (a4) {
            name = a4;
        }

        JMapInfo* info = MR::makeInitActorCsvParser(name, a5);

        if (info != nullptr) {
            if (MR::isExistElement(info, "InitFunction", "Rail")) {
                const char* railUse = nullptr;
                const JMapInfoIter railIter = MR::getCsvDataStrByElement(&railUse, info, "InitFunction", "Rail", "Data");

                if (MR::isEqualString(railUse, "Need")) {
                    pActor->initRailRider(rIter);
                }
                else {
                    if (MR::isEqualString(railUse, "Use") && MR::isConnectedWithRail(rIter)) {
                        pActor->initRailRider(rIter);
                    }
                }
            }

            if (MR::isDataEnable(info, "DefaultPos")) {
                MR::initDefaultPos(pActor, rIter);
            }

            if (MR::isExistElement(info, "InitFunction", "UseScaleForParam")) {
                if (MR::isDataEnable(info, "UseScaleForParam")) {
                    flag = true;
                }
            }

            const char* modelName = nullptr;
            const JMapInfoIter modelIter = MR::getCsvDataStrByElement(&modelName, info, "InitFunction", "Model", "Data");

            if (*modelName) {
                pActor->initModelManagerWithAnm(modelName, a4, a5, a6);
            }

            const char* executor = nullptr;
            const JMapInfoIter executorIter = MR::getCsvDataStrByElement(&executor, info, "InitFunction", "Executor", "Data");
            int connectionIdx = getConnectionIdx(executor);
            const ObjConnection* connection;
            if (connectionIdx >= 0) {
                connection = &cConnections[connectionIdx];
            }
            else {
                connection = nullptr;
            }

            if (connection != nullptr) {
                MR::connectToScene(pActor, connection->_4, connection->_8, connection->_C, connection->_10);
            }

            if (MR::isExistElement(info, "InitFunction", "Light")) {
                const char* light = nullptr;
                const JMapInfoIter lightIter = MR::getCsvDataStrByElement(&light, info, "InitFunction", "Light", "Data");

                if (*light) {
                    MR::initLightCtrl(pActor);
                    int idx = getLightIDIdx(light);
                    pActor->mLightCtrl->setLightType(idx);
                }
            }

            if (MR::isDataEnable(info, "Binder\0")) {
                const char* binder = nullptr;
                const JMapInfoIter& iter = getInitFunction(&binder, info, "Binder");
                f32 param00 = 0.0f;
                iter.getValue<f32>("Param00F32", &param00);
                f32 param01 = 0.0f;
                iter.getValue<f32>("Param01F32", &param01);
                u32 paramInt = 0;
                const JMapInfo* binderInfo = iter.mInfo;
                s32 binderRow = iter.mIndex;
                int paramIntInfo = binderInfo->searchItemInfo("Param00Int");
                if (paramIntInfo >= 0) {
                    binderInfo->getValueFast(binderRow, paramIntInfo, &paramInt);
                }

                pActor->initBinder(param00, param01, paramInt);
            }

            const char* effect = nullptr;
            const JMapInfoIter& effectIter = getInitFunction(&effect, info, "Effect");
            if (*effect) {
                s32 count = 0;
                effectIter.getValue<s32>("Param00Int", &count);
                pActor->initEffectKeeper(count, effect, false);
            }

            const char* sound = nullptr;
            const JMapInfoIter& soundIter = getInitFunction(&sound, info, "Sound");
            if (*sound && *sound != 'x') {
                const char* soundName = nullptr;
                if (*sound != 'o') {
                    soundName = sound;
                }
                s32 count = 0;
                soundIter.getValue<s32>("Param00Int", &count);
                if (count <= 0) {
                    count = 4;
                }
                TVec3f offset(0.0f);
                soundIter.getValue<f32>("Param00VecX", &offset.x);
                soundIter.getValue<f32>("Param00VecY", &offset.y);
                soundIter.getValue<f32>("Param00VecZ", &offset.z);
                pActor->initSound(count, soundName, nullptr, offset);
            }

            if (a5) {
                char shadowName[0x80];
                snprintf(shadowName, sizeof(shadowName), "Shadow%s", a5);
                MR::initShadowFromCSVWithoutInitShadowVolumeSphere(pActor, shadowName);
            }
            else {
                MR::initShadowFromCSVWithoutInitShadowVolumeSphere(pActor, "Shadow");
            }

            const char* clipping = nullptr;
            const JMapInfoIter& clippingIter = getInitFunction(&clipping, info, "Clipping");
            f32 clippingRadius = 0.0f;
            clippingIter.getValue<f32>("Param00F32", &clippingRadius);
            if (clippingRadius > 0.0f) {
                MR::setClippingTypeSphere(pActor, clippingRadius);
                if (MR::isEqualString(clipping, "FarMax")) {
                    MR::setClippingFarMax(pActor);
                }
            }

            if (MR::isDataEnable(info, "GroupClipping")) {
                const char* groupClipping = nullptr;
                const JMapInfoIter& groupIter = getInitFunction(&groupClipping, info, "GroupClipping");
                s32 param00Int = 0;
                groupIter.getValue<s32>("Param00Int", &param00Int);

                if (param00Int <= 0) {
                    param00Int = 0x10;
                }

                MR::setGroupClipping(pActor, rIter, param00Int);
            }

            if (MR::isDataEnable(info, "DemoSimpleCastAll")) {
                MR::registerDemoSimpleCastAll(pActor);
            }

            if (MR::isDataEnable(info, "StarPointer")) {
                const char* starPointer = nullptr;
                const JMapInfoIter& iter = getInitFunction(&starPointer, info, "StarPointer");
                f32 param00 = 0.0f;
                iter.getValue<f32>("Param00F32", &param00);
                TVec3f vec(0.0f);
                iter.getValue<f32>("Param00VecX", &vec.x);
                iter.getValue<f32>("Param00VecY", &vec.y);
                iter.getValue<f32>("Param00VecZ", &vec.z);

                const char* param = nullptr;
                const JMapInfo* pointerInfo = iter.mInfo;
                s32 pointerRow = iter.mIndex;
                int index = pointerInfo->searchItemInfo("Param00Str");

                if (index >= 0) {
                    pointerInfo->getValueFast(pointerRow, index, &param);
                }

                if (!MR::isNullOrEmptyString(param)) {
                    MR::initStarPointerTargetAtJoint(pActor, param, param00, vec);
                }
                else {
                    MR::initStarPointerTarget(pActor, param00, vec);
                }
            }
        }
        else {
            pActor->initModelManagerWithAnm(pArchiveName, a4, a5, a6);
        }

        char buf[0x80];
        snprintf(buf, sizeof(buf), "%s.arc", name);
        MR::initSensors(pActor, buf, a5);
        JMapInfo* colInfo = MR::createCsvParserFromFile(buf, "InitCollision%s.bcsv", a5);

        if (colInfo != nullptr) {
            ResourceHolder* holder = MR::createAndAddResourceHolder(buf);
            s32 elementNum = MR::getCsvDataElementNum(colInfo);

            for (s32 i = 0; i < elementNum; i++) {
                const char* colName = nullptr;
                MR::getCsvDataStrOrNULL(&colName, colInfo, "CollisionName", i);
                const char* sensorName = nullptr;
                MR::getCsvDataStrOrNULL(&sensorName, colInfo, "SensorName", i);
                const char* jointName = nullptr;
                MR::getCsvDataStrOrNULL(&jointName, colInfo, "JointName", i);

                if (jointName != nullptr) {
                    MR::initCollisionPartsFromResourceHolder(pActor, colName, pActor->getSensor(sensorName), holder, MR::getJointMtx(pActor, jointName));
                }
                else {
                    MR::initCollisionPartsFromResourceHolder(pActor, colName, pActor->getSensor(sensorName), holder, nullptr);
                }
            }
        }

        MR::initSwitches(pActor, rIter, buf, a5);
        JMapInfo* scaleInfo = MR::createCsvParserFromFile(buf, "InitScale%s.bcsv", a5);

        if (scaleInfo != nullptr) {
            TVec3f actorScale(pActor->mScale);
            TVec3f scale(1.0f);
            MR::getCsvDataVec(&scale, scaleInfo, "Scale", 0);
            MR::setScale(pActor, actorScale.x * scale.x, actorScale.y * scale.y, actorScale.z * scale.z);
        }

        if (flag) {
            f32 y = pActor->mScale.y;
            if (pActor->mSensorKeeper != nullptr) {
                MR::scaleAllSensorRadius(pActor, pActor->mScale.y);
                s32 sensorNum = MR::getSensorNum(pActor);

                for (s32 i = 0; i < sensorNum; i++) {
                    HitSensorInfo* sensorInfo = pActor->mSensorKeeper->getNthSensorInfo(i);
                    TVec3f sensorScale(sensorInfo->_C);
                    sensorScale.x *= y;
                    sensorScale.y *= y;
                    sensorScale.z *= y;
                    sensorInfo->_C.setPS(sensorScale);
                }
            }

            if (pActor->mBinder != nullptr) {
                MR::scaleBinderRadius(pActor, y);
                pActor->mBinder->mOffsetY = y * pActor->mBinder->mOffsetY;
            }
        }

        if (pActor->mActionKeeper != nullptr) {
            pActor->mActionKeeper->initFlagCtrl();
        }

        if (!a6 && pActor->mModelManager != nullptr) {
            MR::tryStartAllAnim(pActor, pArchiveName);
        }

        return info != nullptr;
    }

    bool initActorNoIter(LiveActor *pActor, const char *pObjName, const char *a3, bool a4) {
        JMapInfoIter iter(0, -1);
        return initActor(pActor, iter, pObjName, a3, nullptr, a4);
    }

    bool initActorNoIter(LiveActor *pActor, const char *pObjName, const char *a3, const char *a4, bool a5) {
        JMapInfoIter iter(0, -1);
        return initActor(pActor, iter, pObjName, a3, a4, a5);
    }

    void initDefaultPos(LiveActor *pActor, const JMapInfoIter &rIter) {
        MR::getDefaultPos(pActor, rIter);
        MR::normalizeVec(&pActor->mRotation, 0.0f);
    }

    void getDefaultPos(LiveActor *pActor, const JMapInfoIter &rIter) {
        if (rIter.isValid()) {
            MR::getJMapInfoTrans(rIter, &pActor->mPosition);
            MR::getJMapInfoRotate(rIter, &pActor->mRotation);
            MR::getJMapInfoScale(rIter, &pActor->mScale);
        }
    }

    bool tryInitFromRestartPos(LiveActor* pActor, const JMapInfoIter& rIter) {
        initDefaultPos(pActor, rIter);
        return getRestartPosData(&pActor->mPosition, &pActor->mRotation, rIter);
    }

    void initRotation(TVec3f* pFront, const JMapInfoIter& rIter) {
        if (rIter.isValid()) {
            TVec3f rotation;
            MR::getJMapInfoRotate(rIter, &rotation);
            TPos3f mtx;
            mtx.identity();
            MR::makeMtxRotate(mtx, rotation);
            pFront->set<f32>(mtx[0][2], mtx[1][2], mtx[2][2]);
        }
    }

    void initSensors(LiveActor* pActor, const char* pArchive, const char* pSubFile) {
        JMapInfo* info = createCsvParserFromFile(pArchive, "InitSensor%s.bcsv", pSubFile);
        if (info != nullptr) {
            s32 count = getCsvDataElementNum(info);
            pActor->initHitSensor(count);
            for (s32 i = 0; i < count; i++) {
                const char* sensor = nullptr;
                getCsvDataStrOrNULL(&sensor, info, "SensorName", i);
                const char* typeName = nullptr;
                getCsvDataStrOrNULL(&typeName, info, "SensorType", i);
                u32 type = getSensorType(typeName);
                f32 radius = -1.0f;
                getCsvDataF32(&radius, info, "Radius", i);
                TVec3f offset;
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                getCsvDataVec(&offset, info, "Offset", i);
                s32 max = -1;
                s32 maxCount = 8;
                getCsvDataS32(&max, info, "HitSensorNumMax", i);
                if (max >= 0) {
                    maxCount = max;
                }
                const char* joint = nullptr;
                getCsvDataStrOrNULL(&joint, info, "JointName", i);
                bool callback = false;
                const char* callbackStr = nullptr;
                getCsvDataStr(&callbackStr, info, "Callback", i);
                if (*callbackStr == 'o') {
                    callback = true;
                }
                if (callback) {
                    addHitSensorCallback(pActor, sensor, type, maxCount, radius);
                }
                else if (joint != nullptr) {
                    addHitSensorAtJoint(pActor, sensor, joint, type, maxCount, radius, offset);
                }
                else {
                    addHitSensor(pActor, sensor, type, maxCount, radius, offset);
                }
            }
        }
    }

    void initSwitches(LiveActor* pActor, const JMapInfoIter& rIter, const char* pArchive, const char* pSubFile) {
        JMapInfo* info = createCsvParserFromFile(pArchive, "InitSwitch%s.bcsv", pSubFile);
        if (info != nullptr) {
            const char* type = nullptr;
            if (getInitSwitchType(&type, info, "SW_APPEAR")) {
                if (isEqualString(type, "UseRead")) {
                    initUseStageSwitchReadAppear(pActor, rIter);
                }
                else if (isEqualString(type, "NeedRead")) {
                    needStageSwitchReadAppear(pActor, rIter);
                }
            }
            if (getInitSwitchType(&type, info, "SW_DEAD")) {
                if (isEqualString(type, "UseWrite")) {
                    initUseStageSwitchWriteDead(pActor, rIter);
                }
                else if (isEqualString(type, "NeedWrite")) {
                    needStageSwitchWriteDead(pActor, rIter);
                }
                else if (isEqualString(type, "UseWriteAuto")) {
                    useStageSwitchWriteAutoDead(pActor, rIter);
                }
                else if (isEqualString(type, "NeedWriteAuto")) {
                    needStageSwitchWriteAutoDead(pActor, rIter);
                }
            }
            if (getInitSwitchType(&type, info, "SW_A")) {
                if (isEqualString(type, "UseRead")) {
                    initUseStageSwitchReadA(pActor, rIter);
                }
                else if (isEqualString(type, "UseWrite")) {
                    initUseStageSwitchWriteA(pActor, rIter);
                }
                else if (isEqualString(type, "NeedRead")) {
                    needStageSwitchReadA(pActor, rIter);
                }
                else if (isEqualString(type, "NeedWrite")) {
                    needStageSwitchWriteA(pActor, rIter);
                }
            }
            if (getInitSwitchType(&type, info, "SW_B")) {
                if (isEqualString(type, "UseRead")) {
                    initUseStageSwitchReadB(pActor, rIter);
                }
                else if (isEqualString(type, "UseWrite")) {
                    initUseStageSwitchWriteB(pActor, rIter);
                }
                else if (isEqualString(type, "NeedRead")) {
                    needStageSwitchReadB(pActor, rIter);
                }
                else if (isEqualString(type, "NeedWrite")) {
                    needStageSwitchWriteB(pActor, rIter);
                }
            }
            if (isExistElement(info, "SwitchName", "SW_AWAKE")) {
                if (getInitSwitchType(&type, info, "SW_AWAKE")) {
                    if (isEqualString(type, "UseRead")) {
                        useStageSwitchAwake(pActor, rIter);
                    }
                }
            }
        }
    }
};
