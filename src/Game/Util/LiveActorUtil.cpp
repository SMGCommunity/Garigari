#include "Game/Util/LiveActorUtil.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/LodCtrl.hpp"
#include "Game/LiveActor/PartsModel.hpp"
#include "Game/Util/EffectUtil.hpp"

namespace MR {
    LodCtrl* createLodCtrlNPC(LiveActor* pActor, const JMapInfoIter& rIter) {
        LodCtrl* ctrl = new LodCtrl(pActor, rIter);
        ctrl->createLodModel(0x11, 0x27, -1);
        ctrl->syncMaterialAnimation();
        ctrl->syncJointAnimation();
        ctrl->initLightCtrl();
        ctrl->offSyncShadowHost();
        ctrl->mDistCameraCalc = true;
        return ctrl;
    }

    LodCtrl* createLodCtrlPlanet(LiveActor* pActor, const JMapInfoIter& rIter, f32 farClip, s32 calcAnim) {
        LodCtrl* ctrl = new LodCtrl(pActor, rIter);
        ctrl->createLodModel(6, calcAnim, 1);
        ctrl->setDistanceToMiddleAndLow(5000.0f, 10000.0f);
        ctrl->setFarClipping(farClip);
        return ctrl;
    }

    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius);
    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius, const TVec3f* pClippingPos);
    void setClippingTypeSphereContainsModelBoundingBox(LiveActor* pActor, f32 radiusExtension);
    void setClippingFar50m(LiveActor* pActor);
    void setClippingFar100m(LiveActor* pActor);
    void setClippingFar200m(LiveActor* pActor);
    void setClippingFar300m(LiveActor* pActor);
    void setClippingFarMax(LiveActor* pActor);
    void setClippingFar(LiveActor* pActor, f32 farDistance);

    PartsModel* createPartsModel(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx, u32 drawBufferType) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, drawBufferType, false);

        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelMapObj2(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_MapObj2);
    }

    PartsModel* createPartsModelMapObj(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_MapOnj);
    }

    PartsModel* createPartsModelMapObjStrongLight(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_MapObjStrongLight);
    }

    PartsModel* createPartsModelNoSilhouettedMapObj(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_NoSilhouettedMapObjStrongLight);
    }

    PartsModel* createPartsModelEnemy(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_Enemy);
    }

    PartsModel* createPartsModelNpc(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_NPC, false);

        partsModel->initWithoutIter();

        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    PartsModel* createPartsModelIndirectNpc(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_IndirectNpc, false);

        partsModel->initWithoutIter();

        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    PartsModel* createPartsModelEnemyAndFix(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_EnemyAndFix, false);

        partsModel->initFixedPosition(pHost->mPosition, pHost->mRotation, nullptr);

        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelEnemyAndFix(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx,
                                            const JGeometry::TVec3< float >& rOffset, const JGeometry::TVec3< float >& rRotate,
                                            const char* pJointName) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferDistance_EnemyAndFix, false);

        partsModel->initFixedPosition(rOffset, rRotate, pJointName);

        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelNpcAndFix(LiveActor* pHost, const char* pName, const char* pModelName, const char* pJointName) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, nullptr, DrawBufferDistance_NpcAndFix, false);

        partsModel->initFixedPosition(pJointName);

        partsModel->initWithoutIter();

        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    bool tryKillAndForceDeleteEffectAll(LiveActor* pActor) {
        if (!pActor->mFlags.mIsDead) {
            pActor->makeActorDead();
        }

        return tryForceDeleteEffectAll(pActor);
    }

    HitSensor* getBodySensor(LiveActor* pActor) {
        return pActor->getSensor("Body");
    }

    void setBodySensorType(LiveActor* pActor, u32 sensorType) {
        getBodySensor(pActor)->setType(sensorType);
    }
};  // namespace MR
