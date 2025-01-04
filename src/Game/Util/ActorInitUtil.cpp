#include "Util/ActorInitUtil.hpp"
#include "Util.hpp"
#include "LiveActor/ActorLightCtrl.hpp"
#include "LiveActor/LiveActor.hpp"
#include <cstdio>

namespace MR {
    // todo -- finish these
    const ObjConnection cConnections[] = {
        { "MapObj", 0x21, 0x5, 0x9, 0xFFFFFFFF }
    };

    const ObjLight cLightTable[] = {
        { "プレイヤー", "Player", 0 },
        { "目立たせ", "Strong", 1 },
        { "なじませ", "Weak", 2 },
        { "惑星", "Planet", 3 },
    };

    inline s32 getConnectionIdx(const char *pName) {
        for (s32 i = 0; i < 0x31; i++) {
            const ObjConnection* c = &cConnections[i];
            if (MR::isEqualString(pName, c->mObjType)) {
                return i;
            }
        }

        return -1;
    }

    inline s32 getLightIDIdx(const char *pLight) {
        for (s32 i = 0; i < 0x31; i++) {
            const ObjLight* c = &cLightTable[i];
            if (MR::isEqualString(pLight, c->mTypeStr)) {
                return i;
            }
        }

        return 3;
    }

    bool fn_8000C340(LiveActor *pActor, const JMapInfoIter &rIter, const char *pArchiveName, const char* a4, const char *a5, bool a6) {
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
                MR::getCsvDataStrByElement(&railUse, info, "InitFunction", "Rail", "Data");

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
            MR::getCsvDataStrByElement(&modelName, info, "InitFunction", "Model", "Data");

            if (*modelName) {
                pActor->initModelManagerWithAnm(modelName, a4, a5, a6);
            }

            const char* executor = nullptr;
            MR::getCsvDataStrByElement(&executor, info, "InitFunction", "Executor", "Data");
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
                MR::getCsvDataStrByElement(&light, info, "InitFunction", "Light", "Data");

                if (*light) {
                    MR::initLightCtrl(pActor);
                    int idx = getLightIDIdx(light);
                    pActor->mLightCtrl->setLightType(idx);
                }
            }

            if (MR::isDataEnable(info, "Binder")) {
                const char* binder = nullptr;
                JMapInfoIter iter = MR::getCsvDataStrByElement(&binder, info, "InitFunction", "Binder", "Data");
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
            /* todo -- finish me */
            
        }
        else {
            pActor->initModelManagerWithAnm(pArchiveName, a4, a5, a6);
        }
    }
};
