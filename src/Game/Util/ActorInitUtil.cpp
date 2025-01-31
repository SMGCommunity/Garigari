#include "Util/ActorInitUtil.hpp"
#include "LiveActor/ActorActionKeeper.hpp"
#include "LiveActor/Binder.hpp"
#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/HitSensorInfo.hpp"
#include "LiveActor/ActorLightCtrl.hpp"
#include "LiveActor/LiveActor.hpp"
#include "Util.hpp"
#include "Util/JMapInfo.hpp"
#include <cstdio>

namespace {
    // todo -- finish these
    const MR::ObjConnection cConnections[] = {
        { "MapObj", 0x21, 0x5, 0x9, 0xFFFFFFFF }
    };

    const MR::ObjLight cLightTable[] = {
        { "プレイヤー", "Player", 0 },
        { "目立たせ", "Strong", 1 },
        { "なじませ", "Weak", 2 },
        { "惑星", "Planet", 3 },
    };

    
    inline s32 getConnectionIdx(const char *pName) __attribute__((always_inline)) {
        for (s32 i = 0; i < 0x31; i++) {
            const MR::ObjConnection* c = &cConnections[i];
            if (MR::isEqualString(pName, c->mObjType)) {
                return i;
            }
        }

        return -1;
    }

    inline s32 getLightIDIdx(const char *pLight) __attribute__((always_inline)) {
        for (s32 i = 0; i < 0x31; i++) {
            const MR::ObjLight* c = &cLightTable[i];
            if (MR::isEqualString(pLight, c->mTypeStr)) {
                return i;
            }
        }

        return 3;
    }
};

namespace MR {
    bool isDataEnable(JMapInfo *pInfo, const char *pName) {
        if (!MR::isExistElement(pInfo, "InitFunction", pName)) {
            return false;
        }

        const char* str = nullptr;
        MR::getCsvDataStrByElement(&str, pInfo, "InitFunction", pName, "Data");
        return str[0] == 'o';
    }

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

            if (connectionIdx > 0) {
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

            if (MR::isDataEnable(info, "Binder")) {
                const char* binder = nullptr;
                const JMapInfoIter iter = MR::getCsvDataStrByElement(&binder, info, "InitFunction", "Binder", "Data");
                f32 param00;
                iter.getValue<f32>("Param00F32", &param00);
                f32 param01;
                iter.getValue<f32>("Param01F32", &param01);
                u32 paramInt = 0;
                int paramIntInfo = info->searchItemInfo("Param00Int");
                if (paramIntInfo >= 0) {
                    info->getValueFast(iter.mIndex, paramIntInfo, &paramInt);
                }

                pActor->initBinder(param00, param01, paramInt);
            }

            if (MR::isDataEnable(info, "GroupClipping")) {
                const char* groupClipping = nullptr;
                const JMapInfoIter groupIter = MR::getCsvDataStrByElement(&groupClipping, info, "InitFunction", "GroupClipping", "Data");
                s32 param00Int;
                groupIter.getValue<s32>("Param00Int", &param00Int);

                if (param00Int < 0) {
                    param00Int = 0x10;
                }

                MR::setGroupClipping(pActor, rIter, param00Int);
            }
            
            if (MR::isDataEnable(info, "DemoSimpleCastAll")) {
                MR::registerDemoSimpleCastAll(pActor);
            }

            if (MR::isDataEnable(info, "StarPointer")) {
                const char* starPointer = nullptr;
                const JMapInfoIter iter = MR::getCsvDataStrByElement(&starPointer, info, "InitFunction", "StarPointer", "Data");
                f32 param00 = 0.0f;
                iter.getValue<f32>("Param00F32", &param00);
                TVec3f vec(0.0f);
                iter.getValue<f32>("Param00VecX", &vec.x);
                iter.getValue<f32>("Param00VecY", &vec.y);
                iter.getValue<f32>("Param00VecZ", &vec.z);

                const char* param = nullptr;
                int index = info->searchItemInfo("Param00Str");

                if (index >= 0) {
                    info->getValueFast(iter.mIndex, index, &param);
                }

                if (MR::isNullOrEmptyString(param)) {
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
        snprintf(buf, sizeof(buf), "%s.arc", pArchiveName);
        MR::initSensors(pActor, buf, a5);
        JMapInfo* colInfo = MR::createCsvParserFromFile(buf, "InitCollision&s.bcsv", a5);

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
        JMapInfo* scaleInfo = MR::createCsvParserFromFile(buf, "InitScale&s.bcsv", a5);

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
                    sensorInfo->_C.set<f32>(sensorScale);
                }
            }

            if (pActor->mBinder != nullptr) {
                MR::scaleBinderRadius(pActor, y);
                pActor->mBinder->mRadius *= y;
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
};
