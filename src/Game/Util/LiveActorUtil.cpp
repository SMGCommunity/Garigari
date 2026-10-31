#include "Game/Util/LiveActorUtil.hpp"
#include "Game/LiveActor/Binder.hpp"
#include "Game/LiveActor/ClippingActorHolder.hpp"
#include "Game/LiveActor/ClippingDirector.hpp"
#include "Game/LiveActor/DisplayListMaker.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"
#include "Game/LiveActor/LiveActorGroupArray.hpp"
#include "Game/LiveActor/LodCtrl.hpp"
#include "Game/LiveActor/MirrorCamera.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "Game/LiveActor/PartsModel.hpp"
#include "Game/Map/CollisionParts.hpp"
#include "Game/NameObj/NameObjExecuteHolder.hpp"
#include "Game/NameObj/NameObjFinder.hpp"
#include "Game/Player/GroupChecker.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/System/ResourceHolder.hpp"
#include "Game/System/ResourceInfo.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/CollisionPartsFilter.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/FurMulti.hpp"
#include "Game/Util/GravityUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/MapUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "Game/Util/TriangleFilter.hpp"
#include <JSystem/J3DGraphAnimator/J3DModel.hpp>
#include <JSystem/JGeometry/TMatrix.hpp>
#include <JSystem/JGeometry/TVec.hpp>
#include <cstdio>
#include <revolution/mtx.h>
#include <revolution/types.h>

namespace {
    CollisionParts* createCollisionParts(ResourceHolder* pResHolder, const char* pName, HitSensor* pSensor, const TPos3f& rMtx,
                                         MR::CollisionScaleType scaleType, s32 unk) {
        CollisionParts* parts = new CollisionParts();
        char kcl[0x80];
        snprintf(kcl, sizeof(kcl), "%s.kcl", pName);
        char pa[0x80];
        snprintf(pa, sizeof(pa), "%s.pa", pName);
        void* kclRes;
        void* paRes = nullptr;
        kclRes = pResHolder->mFileInfoTable->getRes(kcl);

        if (pResHolder->mFileInfoTable->isExistRes(pa)) {
            paRes = pResHolder->mFileInfoTable->getRes(pa);
        }

        switch (scaleType) {
        case MR::CollisionScaleType_AutoEqualScale:
            parts->initWithAutoEqualScale(rMtx, pSensor, kclRes, paRes, unk, false);
            break;
        case MR::CollisionScaleType_NotUsingScale:
            parts->initWithNotUsingScale(rMtx, pSensor, kclRes, paRes, unk, false);
            break;
        case MR::CollisionScaleType_Default:
            parts->init(rMtx, pSensor, kclRes, paRes, unk, false);
            break;
        }

        return parts;
    }

    void calcCollisionMtx(TPos3f* pMtx, const LiveActor* pActor, bool b) {
        pMtx->set(pActor->getBaseMtx());

        pMtx->scaleInline(pActor->mScale.x);
    }

    bool isShowModel(LiveActor* pActor) {
        return !pActor->mFlags.mIsNoEntryDrawBuffer;
    }

    void callFuncAllGroupMember(const NameObj* pActor, void (*pFunc)(NameObj*)) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        LiveActorGroup* pGroup = pGroupArray->getLiveActorGroup(static_cast< const LiveActor* >(pActor));

        if (pGroup == nullptr) {
            return;
        }

        for (s32 i = 0; i < pGroup->getObjectCount(); i++) {
            LiveActor* pMember = pGroup->getActor(i);

            if (pMember == pActor) {
                continue;
            }

            pFunc(pMember);
        }
    }

    void callFuncAllGroupMember(const LiveActor* pActor, void (*pFunc)(LiveActor*)) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        LiveActorGroup* pGroup = pGroupArray->getLiveActorGroup(pActor);

        if (pGroup == nullptr) {
            return;
        }

        for (s32 i = 0; i < pGroup->getObjectCount(); i++) {
            LiveActor* pMember = pGroup->getActor(i);

            if (pMember == pActor) {
                continue;
            }

            pFunc(pMember);
        }
    }

    void callMethodAllGroupMember(const LiveActor* pActor, void (LiveActor::*pMethod)()) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        LiveActorGroup* pGroup = pGroupArray->getLiveActorGroup(pActor);

        if (pGroup == nullptr) {
            return;
        }

        for (s32 i = 0; i < pGroup->getObjectCount(); i++) {
            LiveActor* pMember = pGroup->getActor(i);

            if (pMember == pActor) {
                continue;
            }

            (pMember->*pMethod)();
        }
    }

    template < typename T >
    s32 countGroupMember(const LiveActor* pActor, T pPred);

    template <>
    s32 countGroupMember< bool (*)(LiveActor*) >(const LiveActor* pActor, bool (*pPred)(LiveActor*)) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        LiveActorGroup* pGroup = pGroupArray->getLiveActorGroup(pActor);
        s32 count = 0;

        if (pGroup == nullptr) {
            return 0;
        }

        for (s32 i = 0; i < pGroup->getObjectCount(); i++) {
            LiveActor* pMember = pGroup->getActor(i);

            if (pMember == pActor) {
                continue;
            }

            if (pPred(pMember)) {
                count++;
            }
        }

        return count;
    }

    template <>
    s32 countGroupMember< bool (*)(const LiveActor*) >(const LiveActor* pActor, bool (*pPred)(const LiveActor*)) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        LiveActorGroup* pGroup = pGroupArray->getLiveActorGroup(pActor);
        s32 count = 0;

        if (pGroup == nullptr) {
            return 0;
        }

        for (s32 i = 0; i < pGroup->getObjectCount(); i++) {
            LiveActor* pMember = pGroup->getActor(i);

            if (pMember == pActor) {
                continue;
            }

            if (pPred(pMember)) {
                count++;
            }
        }

        return count;
    }
};  // namespace

namespace MR {
    void setPosition(LiveActor* pActor, const TVec3f& rPosition) {
        pActor->mPosition.set(rPosition);
    }

    void setPosition(LiveActor* pActor, f32 x, f32 y, f32 z) {
        pActor->mPosition.set(x, y, z);
    }

    void setRotation(LiveActor* pActor, const TVec3f& rRotation) {
        pActor->mRotation.set(rRotation);
    }

    void setRotation(LiveActor* pActor, f32 x, f32 y, f32 z) {
        pActor->mRotation.set(x, y, z);
    }

    void setRotation(LiveActor* pActor, f32 rRotation) {
        pActor->mRotation.x = rRotation;
        pActor->mRotation.y = rRotation;
        pActor->mRotation.z = rRotation;
    }

    void setScale(LiveActor* pActor, const TVec3f& rScale) {
        pActor->mScale.set(rScale);
    }

    void setScale(LiveActor* pActor, f32 x, f32 y, f32 z) {
        pActor->mScale.set(x, y, z);
    }

    void setScale(LiveActor* pActor, f32 rScale) {
        pActor->mScale.x = rScale;
        pActor->mScale.y = rScale;
        pActor->mScale.z = rScale;
    }

    void copyTransRotateScale(LiveActor* pToActor, LiveActor* pFromActor) {
        pFromActor->mPosition.set(pToActor->mPosition);
        pFromActor->mRotation.set(pToActor->mRotation);
        pFromActor->mScale.set(pToActor->mScale);
    }

    void copyTransRotate(LiveActor* pToActor, LiveActor* pFromActor) {
        pFromActor->mPosition.set(pToActor->mPosition);
        pFromActor->mRotation.set(pToActor->mRotation);
    }

    void rotateAroundActor(TVec3f& rRotated, const TVec3f& rRotateOffset, const LiveActor* pActor) {
        TPos3f mtx;
        MR::makeMtxRotate(mtx, pActor->mRotation);

        mtx.mult(rRotateOffset, rRotated);
    }

    bool isValidMovement(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped) {
            return false;
        }

        return true;
    }

    bool isValidCalcAnim(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped || pActor->mFlags.mIsOnCalcAnim) {
            return false;
        }

        return true;
    }

    bool isValidCalcViewAndEntry(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped) {
            return false;
        }

        return true;
    }

    bool isValidDraw(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped || pActor->mFlags.mIsNoEntryDrawBuffer) {
            return false;
        }

        return true;
    }

    void calcAnimDirect(LiveActor* pActor) {
        bool originalState = pActor->mFlags.mIsOnCalcAnim;

        pActor->mFlags.mIsOnCalcAnim = false;

        pActor->calcAnim();

        if (originalState) {
            pActor->mFlags.mIsOnCalcAnim = true;
        }
    }

    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius) {
        MR::getClippingDirector()->mActorHolder->setTypeToSphere(pActor, clippingRadius, nullptr);
    }

    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius, const TVec3f* pClippingPos) {
        MR::getClippingDirector()->mActorHolder->setTypeToSphere(pActor, clippingRadius, pClippingPos);
    }

    void setClippingTypeSphereContainsModelBoundingBox(LiveActor* pActor, f32 radiusExtension) {
        f32 modelBoundingRadius = 0.0f;
        MR::calcModelBoundingRadius(&modelBoundingRadius, pActor);

        f32 expandedRadius = modelBoundingRadius + radiusExtension;

        MR::getClippingDirector()->mActorHolder->setTypeToSphere(pActor, expandedRadius, nullptr);
    }

    void setClippingFar50m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_50m);
    }

    void setClippingFar100m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_100m);
    }

    void setClippingFar200m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_200m);
    }

    void setClippingFar300m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_300m);
    }

    void setClippingFar400m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_400m);
    }

    void setClippingFar500m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_500m);
    }

    void setClippingFar600m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_600m);
    }

    void setClippingFarMax(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, ClippingDistance_Max);
    }

    void setClippingFar(LiveActor* pActor, f32 farDistance) {
        switch (static_cast< int >(farDistance)) {
        case 50:
            setClippingFar50m(pActor);
            break;
        case 100:
            setClippingFar100m(pActor);
            break;
        case 200:
            setClippingFar200m(pActor);
            break;
        case 300:
            setClippingFar300m(pActor);
            break;
        case 400:
            setClippingFar400m(pActor);
            break;
        case 500:
            setClippingFar500m(pActor);
            break;
        case 600:
            setClippingFar600m(pActor);
            break;
        case -1:
            setClippingFarMax(pActor);
            break;
        }
    }

    void setGroupClipping(LiveActor* pActor, const JMapInfoIter& rIter, int size) {
        MR::getClippingDirector()->joinToGroupClipping(pActor, rIter, size);
    }

    void validateClipping(LiveActor* pActor) {
        if (pActor->mFlags.mIsClippingInvalid) {
            MR::getClippingDirector()->mActorHolder->validateClipping(pActor);
        }
    }

    void invalidateClipping(LiveActor* pActor) {
        if (pActor->mFlags.mIsClippingInvalid) {
            if (pActor->mFlags.mIsClipped) {
                pActor->endClipped();
            }
            return;
        }

        MR::getClippingDirector()->mActorHolder->invalidateClipping(pActor);
    }

    bool changeShowModelFlagSyncNearClipping(LiveActor* pActor, f32 nearDistance) {
        if (MR::isJudgedToNearClip(pActor->mPosition, nearDistance)) {
            MR::hideModelAndOnCalcAnimIfShown(pActor);
            return false;
        }

        MR::showModelIfHidden(pActor);

        return true;
    }

    bool isClipped(const LiveActor* pActor) {
        return pActor->mFlags.mIsClipped;
    }

    bool isInvalidClipping(const LiveActor* pActor) {
        return pActor->mFlags.mIsClippingInvalid;
    }

    void setBaseTRMtx(LiveActor* pActor, MtxPtr pMtx) {
        PSMTXCopy(pMtx, (MtxPtr)&getJ3DModel(pActor)->mBaseTransformMtx);
    }

    void setBaseTRMtx(LiveActor* pActor, const TPos3f& rMtx) {
        PSMTXCopy((MtxPtr)rMtx.mMtx, (MtxPtr)&getJ3DModel(pActor)->mBaseTransformMtx);
    }

    void setBaseTRMtx(LiveActor* pActor, const TQuat4f& rQuat) {
        TPos3f mtx;
        mtx.setQT(rQuat, pActor->mPosition);

        PSMTXCopy((MtxPtr)mtx.mMtx, (MtxPtr)&getJ3DModel(pActor)->mBaseTransformMtx);
    }

    void setBaseScale(LiveActor* pActor, const TVec3f& rScale) {
        getJ3DModel(pActor)->setBaseScale(rScale);
    }

    ResourceHolder* getResourceHolder(const LiveActor* pActor) {
        if (pActor->mModelManager != nullptr) {
            return pActor->mModelManager->getResourceHolder();
        }

        return nullptr;
    }

    ResourceHolder* getModelResourceHolder(const LiveActor* pActor) {
        if (pActor->mModelManager != nullptr) {
            return pActor->mModelManager->getModelResourceHolder();
        }

        return nullptr;
    }

    void initMirrorReflection(LiveActor* pActor) {
        initDLMakerChangeTex(pActor, "MirrorTex");
        pActor->mModelManager->newDifferedDLBuffer();
        changeModelDataTexAll(pActor, "MirrorTex", *MR::getScreenResTIMG());
        pActor->mModelManager->mDisplayListMaker->addMirrorReflectionMtxSetter();
    }

    void setMirrorReflectionInfoFromMtxYUp(const TPos3f& rMtx) {
        TVec3f up;
        TVec3f pos;
        rMtx.getYDir(up);
        rMtx.getTrans(pos);
        MR::getMirrorCamera()->setMirrorMapInfo(up, pos);
    }

    void initJointTransform(const LiveActor* pActor) {
        pActor->mModelManager->initJointTransform();
    }

    XjointTransform* getJointTransform(const LiveActor* pActor, const char* pName) {
        return pActor->mModelManager->getJointTransform(pName);
    }

    bool isExistAnim(const LiveActor* pActor, const char* pName) {
        if (isExistBck(pActor, pName)) {
            return true;
        }

        if (isExistBtk(pActor, pName)) {
            return true;
        }

        if (isExistBrk(pActor, pName)) {
            return true;
        }

        if (isExistBtp(pActor, pName)) {
            return true;
        }

        if (isExistBpk(pActor, pName)) {
            return true;
        }

        return isExistBva(pActor, pName);
    }

    void startAllAnim(const LiveActor* pActor, const char* pName) {
        tryStartAllAnim(pActor, pName);
    }

    bool tryStartAllAnim(const LiveActor* pActor, const char* pName) {
        bool started = false;

        if (startBckIfExist(pActor, pName)) {
            started = true;
        }

        if (startBtkIfExist(pActor, pName)) {
            started = true;
        }

        if (startBrkIfExist(pActor, pName)) {
            started = true;
        }

        if (startBpkIfExist(pActor, pName)) {
            started = true;
        }

        if (startBtpIfExist(pActor, pName)) {
            started = true;
        }

        if (startBvaIfExist(pActor, pName)) {
            started = true;
        }

        return started;
    }

    bool tryStartBckAndBtp(const LiveActor* pActor, const char* pBckName, const char* pBtpName) {
        if (tryStartBck(pActor, pBckName, pBtpName)) {
            if (isExistBtp(pActor, pBckName)) {
                pActor->mModelManager->startBtp(pBckName);
            }

            return true;
        }

        return false;
    }

    void setAllAnimFrameAndStop(const LiveActor* pActor, const char* pName, f32 frame) {
        if (isExistBck(pActor, pName)) {
            setBckFrameAndStop(pActor, frame);
        }

        if (isExistBtk(pActor, pName)) {
            setBtkFrameAndStop(pActor, frame);
        }

        if (isExistBpk(pActor, pName)) {
            setBpkFrameAndStop(pActor, frame);
        }

        if (isExistBtp(pActor, pName)) {
            setBtpFrameAndStop(pActor, frame);
        }

        if (isExistBrk(pActor, pName)) {
            setBrkFrameAndStop(pActor, frame);
        }

        if (isExistBva(pActor, pName)) {
            setBvaFrameAndStop(pActor, frame);
        }
    }

    bool isAnyAnimStopped(const LiveActor* pActor, const char* pName) {
        if (isExistBck(pActor, pName) && isBckStopped(pActor)) {
            return true;
        }

        if (isExistBtk(pActor, pName) && isBtkStopped(pActor)) {
            return true;
        }

        if (isExistBpk(pActor, pName) && isBpkStopped(pActor)) {
            return true;
        }

        if (isExistBtp(pActor, pName) && isBtpStopped(pActor)) {
            return true;
        }

        if (isExistBrk(pActor, pName) && isBrkStopped(pActor)) {
            return true;
        }

        if (isExistBva(pActor, pName) && isBvaStopped(pActor)) {
            return true;
        }

        return false;
    }

    bool isAnyAnimOneTimeAndStopped(const LiveActor* pActor, const char* pName) {
        if (isExistBck(pActor, pName) && isBckStopped(pActor)) {
            return true;
        }

        if (isExistBtk(pActor, pName) && isBtkStopped(pActor)) {
            return true;
        }

        if (isExistBpk(pActor, pName) && isBpkStopped(pActor)) {
            return true;
        }

        if (isExistBtp(pActor, pName) && isBtpStopped(pActor)) {
            return true;
        }

        if (isExistBrk(pActor, pName) && isBrkStopped(pActor)) {
            return true;
        }

        if (isExistBva(pActor, pName) && isBvaStopped(pActor)) {
            return true;
        }

        return false;
    }

    const char* getPlayingBckName(const LiveActor* pActor) {
        return pActor->mModelManager->getPlayingBckName();
    }

    bool isBckStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBckStopped();
    }

    bool isBtkStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBtkStopped();
    }

    bool isBrkStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBrkStopped();
    }

    bool isBtpStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBtpStopped();
    }

    bool isBpkStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBpkStopped();
    }

    bool isBvaStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBvaStopped();
    }

    bool isBckOneTimeAndStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBckStopped();
    }

    bool isBrkOneTimeAndStopped(const LiveActor* pActor) {
        return pActor->mModelManager->isBrkStopped();
    }

    void startBtkAndSetFrameAndStop(const LiveActor* pActor, const char* pBtkName, f32 frame) {
        startBtk(pActor, pBtkName);
        setBtkFrameAndStop(pActor, frame);
    }

    void startBrkAndSetFrameAndStop(const LiveActor* pActor, const char* pBrkName, f32 frame) {
        startBrk(pActor, pBrkName);
        setBrkFrameAndStop(pActor, frame);
    }

    void startBtpAndSetFrameAndStop(const LiveActor* pActor, const char* pBtpName, f32 frame) {
        startBtp(pActor, pBtpName);
        setBtpFrameAndStop(pActor, frame);
    }

    void startBtk(const LiveActor* pActor, const char* pBtkName) {
        pActor->mModelManager->startBtk(pBtkName);
    }

    void startBrk(const LiveActor* pActor, const char* pBrkName) {
        pActor->mModelManager->startBrk(pBrkName);
    }

    void startBtp(const LiveActor* pActor, const char* pBtpName) {
        pActor->mModelManager->startBtp(pBtpName);
    }

    void startBpk(const LiveActor* pActor, const char* pBpkName) {
        pActor->mModelManager->startBpk(pBpkName);
    }

    void startBva(const LiveActor* pActor, const char* pBvaName) {
        pActor->mModelManager->startBva(pBvaName);
    }

    bool isBtkPlaying(const LiveActor* pActor, const char* pBtkName) {
        return pActor->mModelManager->isBtkPlaying(pBtkName);
    }

    bool isBrkPlaying(const LiveActor* pActor, const char* pBrkName) {
        return pActor->mModelManager->isBrkPlaying(pBrkName);
    }

    bool isBtpPlaying(const LiveActor* pActor, const char* pBtpName) {
        return pActor->mModelManager->isBtpPlaying(pBtpName);
    }

    bool isBpkPlaying(const LiveActor* pActor, const char* pBpkName) {
        return pActor->mModelManager->isBpkPlaying(pBpkName);
    }

    bool isBvaPlaying(const LiveActor* pActor, const char* pBvaName) {
        return pActor->mModelManager->isBvaPlaying(pBvaName);
    }

    void stopBtk(const LiveActor* pActor) {
        pActor->mModelManager->stopBtk();
    }

    void stopBrk(const LiveActor* pActor) {
        pActor->mModelManager->stopBrk();
    }

    void stopBtp(const LiveActor* pActor) {
        pActor->mModelManager->stopBtp();
    }

    void stopBva(const LiveActor* pActor) {
        pActor->mModelManager->stopBva();
    }

    void updateMaterial(LiveActor* pActor) {
        pActor->mModelManager->updateDL(true);
    }

    bool isStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() == step;
    }

    bool isFirstStep(const LiveActor* pActor) {
        return MR::isStep(pActor, 0);
    }

    bool isLessStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() < step;
    }

    bool isLessEqualStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() <= step;
    }

    bool isGreaterStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() > step;
    }

    bool isGreaterEqualStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() >= step;
    }

    bool isIntervalStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() % step == 0;
    }

    bool isNewNerve(const LiveActor* pActor) {
        return pActor->getNerveStep() < 0;
    }

    f32 calcNerveRate(const LiveActor* pActor, s32 stepMax) {
        return stepMax <= 0 ? 1.0f : clamp(static_cast< f32 >(pActor->getNerveStep()) / stepMax, 0.0f, 1.0f);
    }

    f32 calcNerveRate(const LiveActor* pActor, s32 stepMin, s32 stepMax) {
        return clamp(normalize(pActor->getNerveStep(), stepMin, stepMax), 0.0f, 1.0f);
    }

    f32 calcNerveEaseInRate(const LiveActor* pActor, s32 stepMax) {
        return getEaseInValue(calcNerveRate(pActor, stepMax), 0.0f, 1.0f, 1.0f);
    }

    f32 calcNerveEaseOutRate(const LiveActor* pActor, s32 stepMax) {
        return getEaseOutValue(calcNerveRate(pActor, stepMax), 0.0f, 1.0f, 1.0f);
    }

    f32 calcNerveEaseOutRate(const LiveActor* pActor, s32 stepMin, s32 stepMax) {
        return getEaseOutValue(calcNerveRate(pActor, stepMin, stepMax), 0.0f, 1.0f, 1.0f);
    }

    f32 calcNerveEaseInOutRate(const LiveActor* pActor, s32 stepMax) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMax), 0.0f, 1.0f, 1.0f);
    }

    f32 calcNerveEaseInOutRate(const LiveActor* pActor, s32 stepMin, s32 stepMax) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMin, stepMax), 0.0f, 1.0f, 1.0f);
    }

    f32 calcNerveValue(const LiveActor* pActor, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getLinerValue(calcNerveRate(pActor, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveValue(const LiveActor* pActor, s32 stepMin, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getLinerValue(calcNerveRate(pActor, stepMin, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseInValue(const LiveActor* pActor, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInValue(calcNerveRate(pActor, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseInValue(const LiveActor* pActor, s32 stepMin, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInValue(calcNerveRate(pActor, stepMin, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseOutValue(const LiveActor* pActor, s32 maxValue, f32 min, f32 max) {
        return getEaseOutValue(calcNerveRate(pActor, maxValue), min, max, 1.0f);
    }

    f32 calcNerveEaseOutValue(const LiveActor* pActor, s32 minStep, s32 maxValue, f32 min, f32 max) {
        f32 nerveStep = pActor->getNerveStep();

        f32 normalizedNerveStep = normalize(nerveStep, minStep, maxValue);

        f32 clampedNerveStep = clamp(normalizedNerveStep, 0.0f, 1.0f);

        return getEaseOutValue(clampedNerveStep, min, max, 1.0f);
    }

    f32 calcNerveEaseInOutValue(const LiveActor* pActor, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseInOutValue(const LiveActor* pActor, s32 stepMin, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMin, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveParabolaValue(const LiveActor* pActor, s32 step) {
        f32 nerveStep = pActor->getNerveStep();

        f32 parabolaValue = getParabolaValue(nerveStep, step);

        return clamp(parabolaValue, 0.0f, 1.0f);
    }

    void setNerveAtStep(LiveActor* pActor, const Nerve* pNerve, s32 step) {
        if (pActor->getNerveStep() == step) {
            pActor->setNerve(pNerve);
        }
    }

    void setNerveAtBckStopped(LiveActor* pActor, const Nerve* pNerve) {
        if (isBckStopped(pActor)) {
            pActor->setNerve(pNerve);
        }
    }

    bool trySetNerve(LiveActor* pActor, const Nerve* pNerve) {
        if (pActor->isNerve(pNerve)) {
            return false;
        }

        pActor->setNerve(pNerve);

        return true;
    }

    bool isOnGround(const LiveActor* pActor) {
        Binder* binder = pActor->mBinder;

        if (binder == nullptr) {
            return false;
        }

        if (!binder->isBindedGround()) {
            return false;
        }

        const TVec3f* normal = binder->mGroundInfo.mParentTriangle.getNormal(0);
        return !(0.0f < pActor->mVelocity.dot(*normal));
    }

    bool isOnGroundCos(const LiveActor* pActor, f32 cos) {
        bool isGround = false;

        if (isOnGround(pActor)) {
            const TVec3f* normal = pActor->mBinder->mGroundInfo.mParentTriangle.getNormal(0);

            if (MR::isFloorPolygonCos(*normal, pActor->mGravity, cos)) {
                isGround = true;
            }
        }

        return isGround;
    }

    bool isBindedGround(const LiveActor* pActor) {
        Binder* binder = pActor->mBinder;

        if (binder == nullptr) {
            return false;
        }

        return binder->isBindedGround();
    }

    bool isBindedGround(const LiveActor* pActor, HitSensor* pSensor) {
        if (isBindedGround(pActor)) {
            return pSensor == MR::getGroundSensor(pActor);
        }

        return false;
    }

    bool isBindedWall(const LiveActor* pActor) {
        Binder* binder = pActor->mBinder;

        if (binder == nullptr) {
            return false;
        }

        return binder->isBindedWall();
    }

    bool isBindedWall(const LiveActor* pActor, HitSensor* pSensor) {
        if (isBindedWall(pActor)) {
            return pSensor == MR::getWallSensor(pActor);
        }

        return false;
    }

    bool isBindedWallOfMap(const LiveActor* pActor) {
        bool isMap = false;

        if (isBindedWall(pActor)) {
            const CollisionParts* parts = pActor->mBinder->mWallInfo.mParentTriangle.mParts;

            if (parts->mKeeperIndex == 0) {
                isMap = true;
            }
        }

        return isMap;
    }

    bool isBindedWallOfMoveLimit(const LiveActor* pActor) {
        bool isMoveLimit = false;

        if (isBindedWall(pActor)) {
            const CollisionParts* parts = pActor->mBinder->mWallInfo.mParentTriangle.mParts;

            if (parts->mKeeperIndex == 3) {
                isMoveLimit = true;
            }
        }

        return isMoveLimit;
    }

    bool isBindedRoof(const LiveActor* pActor) {
        if (pActor->mBinder == nullptr) {
            return false;
        }

        return pActor->mBinder->isBindedRoof();
    }

    bool isBinded(const LiveActor* pActor) {
        if (isBindedGround(pActor) || isBindedRoof(pActor) || isBindedWall(pActor)) {
            return true;
        }

        return false;
    }

    bool isPressedRoofAndGround(const LiveActor* pActor) {
        if (!isBindedRoof(pActor) || !isBindedGround(pActor)) {
            return false;
        }

        if (MR::isSensorPressObj(MR::getGroundSensor(pActor)) || MR::isSensorPressObj(MR::getRoofSensor(pActor))) {
            const Binder* binder = pActor->mBinder;
            const HitInfo* pRoofInfo = &binder->mRoofInfo;
            const HitInfo* pGroundInfo = &binder->mGroundInfo;

            TVec3f roofPower;
            TVec3f groundPower;
            pRoofInfo->mParentTriangle.calcForceMovePower(&roofPower, pRoofInfo->mHitPos);
            pGroundInfo->mParentTriangle.calcForceMovePower(&groundPower, pGroundInfo->mHitPos);

            if (0.0f < (roofPower - groundPower).dot(pActor->mGravity)) {
                return true;
            }
        }

        return false;
    }

    bool isPressedBetweenWalls(const LiveActor* pActor) {
        if (!isBindedWall(pActor)) {
            return false;
        }

        s32 planeNum = pActor->mBinder->mPlaneNum;

        for (s32 i = 0; i < planeNum - 1; i++) {
            const HitInfo* plane1 = pActor->mBinder->getPlane(i);

            if (!MR::isWallPolygon(*plane1->mParentTriangle.getFaceNormal(), pActor->mGravity)) {
                continue;
            }

            TVec3f power1;
            plane1->mParentTriangle.calcForceMovePower(&power1, plane1->mHitPos);

            for (s32 j = i + 1; j < planeNum; j++) {
                const HitInfo* plane2 = pActor->mBinder->getPlane(j);

                if (!MR::isWallPolygon(*plane2->mParentTriangle.getFaceNormal(), pActor->mGravity)) {
                    continue;
                }

                if (0.0f <= plane1->mParentTriangle.getFaceNormal()->dot(*plane2->mParentTriangle.getFaceNormal())) {
                    continue;
                }

                TVec3f power2;
                plane2->mParentTriangle.calcForceMovePower(&power2, plane2->mHitPos);

                TVec3f diffHit(plane1->mHitPos);
                diffHit.sub(plane2->mHitPos);

                TVec3f diffPower(power2);
                diffPower.sub(power1);

                if (0.0f < diffPower.dot(diffHit)) {
                    return true;
                }
            }
        }

        return false;
    }

    const TVec3f& getGroundNormal(const LiveActor* pActor) {
        return *pActor->mBinder->mGroundInfo.mParentTriangle.getNormal(0);
    }

    const TVec3f& getWallNormal(const LiveActor* pActor) {
        return *pActor->mBinder->mWallInfo.mParentTriangle.getNormal(0);
    }

    const TVec3f& getRoofNormal(const LiveActor* pActor) {
        return *pActor->mBinder->mRoofInfo.mParentTriangle.getNormal(0);
    }

    const TVec3f& getBindedNormal(const LiveActor* pActor) {
        if (isBindedGround(pActor)) {
            return getGroundNormal(pActor);
        }

        if (isBindedWall(pActor)) {
            return getWallNormal(pActor);
        }

        if (isBindedRoof(pActor)) {
            return getRoofNormal(pActor);
        }

        return getGroundNormal(pActor);
    }

    const TVec3f& getBindedHitPos(const LiveActor* pActor) {
        if (isBindedGround(pActor)) {
            return getGroundHitPos(pActor);
        }

        if (isBindedWall(pActor)) {
            return getWallHitPos(pActor);
        }

        if (isBindedRoof(pActor)) {
            return getRoofHitPos(pActor);
        }

        return getGroundHitPos(pActor);
    }

    const TVec3f& getGroundHitPos(const LiveActor* pActor) {
        return pActor->mBinder->mGroundInfo.mHitPos;
    }

    const TVec3f& getWallHitPos(const LiveActor* pActor) {
        return pActor->mBinder->mWallInfo.mHitPos;
    }

    const TVec3f& getRoofHitPos(const LiveActor* pActor) {
        return pActor->mBinder->mRoofInfo.mHitPos;
    }

    void calcWallNormalHorizontal(TVec3f* pVec, const LiveActor* pActor) {
        const TVec3f normal = getWallNormal(pActor);
        const TVec3f* grav = &pActor->mGravity;
        pVec->killElement(normal, *grav);
    }

    f32 calcHitPowerToGround(const LiveActor* pActor) {
        if (!isBindedGround(pActor)) {
            return 0.0f;
        }

        f32 dot = pActor->mVelocity.dot(getGroundNormal(pActor));

        if (-dot > 0.0f) {
            return -dot;
        }

        return 0.0f;
    }

    f32 calcHitPowerToWall(const LiveActor* pActor) {
        if (!isBindedWall(pActor)) {
            return 0.0f;
        }

        f32 dot = pActor->mVelocity.dot(getWallNormal(pActor));

        if (-dot > 0.0f) {
            return -dot;
        }

        return 0.0f;
    }

    u32 getBindedPlaneNum(const LiveActor* pActor) {
        return pActor->mBinder->mPlaneNum;
    }

    const TVec3f* getBindedPlaneNormal(const LiveActor* pActor, int planeIndex) {
        return pActor->mBinder->getPlane(planeIndex)->mParentTriangle.getNormal(0);
    }

    HitSensor* getBindedPlaneSensor(const LiveActor* pActor, int planeIndex) {
        return pActor->mBinder->getPlane(planeIndex)->mParentTriangle.mSensor;
    }

    const TVec3f& getBindedFixReactionVector(const LiveActor* pActor) {
        return pActor->mBinder->mFixReactionVector;
    }

    void setBinderOffsetVec(LiveActor* pActor, const TVec3f* pVec, bool b) {
        Binder* binder = pActor->mBinder;
        binder->mOffsetVec = pVec;
        binder->_1EC._4 = b;
    }

    void setBinderRadius(LiveActor* pActor, f32 radius) {
        pActor->mBinder->mRadius = radius;
    }

    void scaleBinderRadius(LiveActor* pActor, f32 scale) {
        pActor->mBinder->mRadius = scale * pActor->mBinder->mRadius;
    }

    f32 getBinderRadius(const LiveActor* pActor) {
        return pActor->mBinder->mRadius;
    }

    void setBinderIgnoreMovingCollision(LiveActor* pActor) {
        s8* pFlags = (s8*)&pActor->mBinder->_1EC;
        s32 flags = *pFlags;
        flags &= 0xFFFFFF7F;
        *pFlags = flags;
    }

    void validateExCollisionParts(LiveActor* pActor) {
        *(u8*)&pActor->mBinder->_1EC |= 0x20;
    }

    void invalidateExCollisionParts(LiveActor* pActor) {
        *(u8*)&pActor->mBinder->_1EC &= ~0x20;
    }

    void setBinderCollisionPartsFilter(LiveActor* pActor, CollisionPartsFilterBase* pFilter) {
        pActor->mBinder->setCollisionPartsFilter(pFilter);
    }

    void setBinderExceptSensorType(LiveActor* pActor, u32 exceptSensorType) {
        CollisionPartsFilterSensorType* pFilter = new CollisionPartsFilterSensorType(exceptSensorType);
        pActor->mBinder->setCollisionPartsFilter(pFilter);
    }

    void setBinderExceptActor(LiveActor* pActor, const LiveActor* pExcept) {
        CollisionPartsFilterActor* pFilter = new CollisionPartsFilterActor(pExcept);
        pActor->mBinder->setCollisionPartsFilter(pFilter);
    }

    void setBindTriangleFilter(LiveActor* pActor, TriangleFilterBase* pTriangleFilter) {
        pActor->mBinder->setTriangleFilter(pTriangleFilter);
    }

    bool isExistBinder(const LiveActor* pActor) {
        return pActor->mBinder != nullptr;
    }

    void onEntryDrawBuffer(LiveActor* pActor) {
        if (!isNoEntryDrawBuffer(pActor)) {
            return;
        }

        if (!isDead(pActor) && !pActor->mFlags.mIsClipped) {
            connectToDrawTemporarily(pActor);
        }

        pActor->mFlags.mIsNoEntryDrawBuffer = false;
    }

    void offEntryDrawBuffer(LiveActor* pActor) {
        if (isNoEntryDrawBuffer(pActor)) {
            return;
        }

        if (!isDead(pActor) && !pActor->mFlags.mIsClipped) {
            disconnectToDrawTemporarily(pActor);
        }

        pActor->mFlags.mIsNoEntryDrawBuffer = true;
    }

    bool isDead(const LiveActor* pActor) {
        return pActor->mFlags.mIsDead;
    }

    bool isHiddenModel(const LiveActor* pActor) {
        return pActor->mFlags.mIsNoEntryDrawBuffer;
    }

    void showModel(LiveActor* pActor) {
        if (isNoCalcAnim(pActor)) {
            onCalcAnim(pActor);
        }

        if (isNoCalcView(pActor)) {
            pActor->mFlags.mIsNoCalcView = false;
        }

        if (isNoEntryDrawBuffer(pActor)) {
            onEntryDrawBuffer(pActor);
        }
    }

    void showModelAndEffects(LiveActor* pActor) {
        if (!pActor->mFlags.mIsNoEntryDrawBuffer) {
            return;
        }

        showModel(pActor);
        onCalcEmitter(pActor);
        onDrawEffect(pActor);
    }

    void hideModel(LiveActor* pActor) {
        if (!isNoCalcAnim(pActor)) {
            offCalcAnim(pActor);
        }

        if (!isNoCalcView(pActor)) {
            pActor->mFlags.mIsNoCalcView = true;
        }

        if (!isNoEntryDrawBuffer(pActor)) {
            offEntryDrawBuffer(pActor);
        }
    }

    void hideModelAndEffects(LiveActor* pActor) {
        if (pActor->mFlags.mIsNoEntryDrawBuffer) {
            return;
        }

        hideModel(pActor);
        offCalcEmitter(pActor);
        offDrawEffect(pActor);
    }

    void hideModelAndOnCalcAnim(LiveActor* pActor) {
        hideModel(pActor);
        onCalcAnim(pActor);
    }

    void showModelIfHidden(LiveActor* pActor) {
        if (isHiddenModel(pActor)) {
            showModel(pActor);
        }
    }

    void hideModelIfShown(LiveActor* pActor) {
        if (isHiddenModel(pActor)) {
            return;
        }

        hideModel(pActor);
    }

    void hideModelAndOnCalcAnimIfShown(LiveActor* pActor) {
        if (isHiddenModel(pActor)) {
            return;
        }

        hideModel(pActor);
        onCalcAnim(pActor);
    }

    bool isStopAnimFrame(LiveActor* pActor) {
        return pActor->mFlags.mIsNotReleasedAnimFrame;
    }

    void stopAnimFrame(LiveActor* pActor) {
        pActor->mFlags.mIsNotReleasedAnimFrame = true;
    }

    void releaseAnimFrame(LiveActor* pActor) {
        pActor->mFlags.mIsNotReleasedAnimFrame = false;
    }

    bool isNoCalcAnim(const LiveActor* pActor) {
        return pActor->mFlags.mIsOnCalcAnim;
    }

    void onCalcAnim(LiveActor* pActor) {
        pActor->mFlags.mIsOnCalcAnim = false;
    }

    void offCalcAnim(LiveActor* pActor) {
        pActor->mFlags.mIsOnCalcAnim = true;
    }

    bool isNoCalcView(const LiveActor* pActor) {
        return pActor->mFlags.mIsNoCalcView;
    }

    bool isNoEntryDrawBuffer(const LiveActor* pActor) {
        return pActor->mFlags.mIsNoEntryDrawBuffer;
    }

    bool isNoBind(const LiveActor* pActor) {
        return pActor->mFlags.mIsOnBind;
    }

    void onBind(LiveActor* pActor) {
        pActor->mFlags.mIsOnBind = false;
    }

    void offBind(LiveActor* pActor) {
        pActor->mFlags.mIsOnBind = true;
    }

    bool isCalcGravity(const LiveActor* pActor) {
        return pActor->mFlags.mIsCalcGravity;
    }

    void onCalcGravity(LiveActor* pActor) {
        if (!pActor->mFlags.mIsDead)
            calcGravity(pActor);
        pActor->mFlags.mIsCalcGravity = true;
    }

    void offCalcGravity(LiveActor* pActor) {
        pActor->mFlags.mIsCalcGravity = false;
    }

    LiveActorGroup* joinToGroup(LiveActor* pActor, const char* pGroupName) {
        LiveActorGroup* pGroup = static_cast< LiveActorGroup* >(NameObjFinder::find(pGroupName));
        pGroup->registerActor(pActor);
        return pGroup;
    }

    LiveActorGroup* joinToGroupArray(LiveActor* pActor, const JMapInfoIter& rIter, const char* pName, s32 maxCount) {
        if (!rIter.isValid()) {
            return nullptr;
        }

        s32 groupId;

        if (getJMapInfoGroupID(rIter, &groupId)) {
            LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
            return (MsgSharedGroup*)pGroupArray->tryCreateGroupForLiveActor(pActor, rIter, pName, maxCount);
        }

        return nullptr;
    }

    LiveActorGroup* getGroupFromArray(const LiveActor* pActor) {
        LiveActorGroupArray* pGroupArray = MR::getSceneObj< LiveActorGroupArray >(SceneObj_LiveActorGroupArray);
        return pGroupArray->getLiveActorGroup(pActor);
    }

    void callMakeActorDeadAllGroupMember(const LiveActor* pActor) {
        callMethodAllGroupMember(pActor, &LiveActor::makeActorDead);
    }

    void callKillAllGroupMember(const LiveActor* pActor) {
        callMethodAllGroupMember(pActor, &LiveActor::kill);
    }

    void callMakeActorAppearedAllGroupMember(const LiveActor* pActor) {
        callMethodAllGroupMember(pActor, &LiveActor::makeActorAppeared);
    }

    void callAppearAllGroupMember(const LiveActor* pActor) {
        callMethodAllGroupMember(pActor, &LiveActor::appear);
    }

    void callRequestMovementOnAllGroupMember(const LiveActor* pActor) {
        callFuncAllGroupMember(static_cast< const NameObj* >(pActor), requestMovementOn);
    }

    void callInvalidateClippingAllGroupMember(const LiveActor* pActor) {
        callFuncAllGroupMember(pActor, invalidateClipping);
    }

    void callValidateClippingAllGroupMember(const LiveActor* pActor) {
        ::callFuncAllGroupMember(pActor, validateClipping);
    }

    void addToAttributeGroupSearchTurtle(const LiveActor* pActor) {
        GroupCheckManager* pGroup = MR::getSceneObj< GroupCheckManager >(SceneObj_GroupCheckManager);
        pGroup->add(pActor, 0);
    }

    bool isExistInAttributeGroupSearchTurtle(const LiveActor* pActor) {
        GroupCheckManager* pGroup = MR::getSceneObj< GroupCheckManager >(SceneObj_GroupCheckManager);
        return pGroup->isExist(pActor, 0);
    }

    bool isExistInAttributeGroupReflectSpinningBox(const LiveActor* pActor) {
        GroupCheckManager* pGroup = MR::getSceneObj< GroupCheckManager >(SceneObj_GroupCheckManager);
        return pGroup->isExist(pActor, 1);
    }

    void calcGravity(LiveActor* pActor) {
        TVec3f gravity;
        calcGravityVector(pActor, pActor->mPosition, &gravity, nullptr, 0);

        if (!isNearZero(gravity)) {
            pActor->mGravity.set(gravity);
        }
    }

    void calcGravity(LiveActor* pActor, const TVec3f& rPos) {
        TVec3f gravity;
        calcGravityVector(pActor, rPos, &gravity, nullptr, 0);

        if (!isNearZero(gravity)) {
            pActor->mGravity.set(gravity);
        }
    }

    void calcGravityOrZero(LiveActor* pActor) {
        calcGravityOrZero(pActor, pActor->mPosition);
    }

    void calcGravityOrZero(LiveActor* pActor, const TVec3f& rPos) {
        TVec3f gravity;
        calcGravityVectorOrZero(pActor, rPos, &gravity, nullptr, 0);

        if (!isNearZero(gravity)) {
            pActor->mGravity.set(gravity);
            return;
        }

        if (isBindedGround(pActor)) {
            const TVec3f* normal = pActor->mBinder->mGroundInfo.mParentTriangle.getNormal(0);
            pActor->mGravity.set(-*normal);
        }
    }

    FurMulti* initFur(LiveActor* pActor) {
        return initMultiFur(pActor, -1);
    }

    FurMulti* initFurEnemy(LiveActor* pActor) {
        return initMultiFur(pActor, 1);
    }

    FurMulti* initFurPlanet(LiveActor* pActor) {
        return initMultiFur(pActor, 3);
    }

    FurMulti* initFurPlayer(LiveActor* pActor) {
        return initMultiFur(pActor, 0);
    }

    void initCollisionParts(LiveActor* pActor, const char* pName, HitSensor* pSensor, MtxPtr pMtx) {
        pActor->initActorCollisionParts(pName, pSensor, nullptr, pMtx, false, false);
    }

    void initCollisionPartsAutoEqualScale(LiveActor* pActor, const char* pName, HitSensor* pSensor, MtxPtr pMtx) {
        pActor->initActorCollisionParts(pName, pSensor, nullptr, pMtx, true, false);
    }

    void initCollisionPartsAutoEqualScaleOne(LiveActor* pActor, const char* pName, HitSensor* pSensor, MtxPtr pMtx) {
        pActor->initActorCollisionParts(pName, pSensor, nullptr, pMtx, true, true);
    }

    void initCollisionPartsFromResourceHolder(LiveActor* pActor, const char* pName, HitSensor* pSensor, ResourceHolder* pResHolder, MtxPtr pMtx) {
        pActor->initActorCollisionParts(pName, pSensor, pResHolder, pMtx, false, false);
    }

    CollisionParts* createCollisionPartsFromLiveActor(LiveActor* pActor, const char* pName, HitSensor* pSensor, CollisionScaleType scaleType) {
        TPos3f mtx;
        makeMtxTRS(mtx, pActor);
        return ::createCollisionParts(getResourceHolder(pActor), pName, pSensor, mtx, scaleType, 0);
    }

    CollisionParts* createCollisionPartsFromLiveActor(LiveActor* pActor, const char* pName, HitSensor* pSensor, MtxPtr pMtx,
                                                      CollisionScaleType scaleType) {
        TPos3f mtx;
        mtx.set(pMtx);
        CollisionParts* pParts = ::createCollisionParts(getResourceHolder(pActor), pName, pSensor, mtx, scaleType, 0);
        pParts->_0 = reinterpret_cast< TPos3f* >(pMtx);
        return pParts;
    }

    CollisionParts* createCollisionPartsFromResourceHolder(ResourceHolder* pResHolder, const char* pName, HitSensor* pSensor, const TPos3f& rMtx,
                                                           TPos3f* pMatrix, CollisionScaleType scaleType) {
        CollisionParts* collisionParts = ::createCollisionParts(pResHolder, pName, pSensor, rMtx, scaleType, 0);

        if (pMatrix != nullptr) {
            collisionParts->_0 = pMatrix;
        }

        return collisionParts;
    }

    CollisionParts* createDashYoshiStepCollisionPartsFromResourceHolder(ResourceHolder* pResHolder, const char* pName, HitSensor* pSensor,
                                                                        MtxPtr pMtx, CollisionScaleType scaleType) {
        TPos3f mtx;
        mtx.set(pMtx);

        CollisionParts* pParts = ::createCollisionParts(pResHolder, pName, pSensor, mtx, scaleType, 4);
        pParts->_0 = reinterpret_cast< TPos3f* >(pMtx);
        return pParts;
    }

    CollisionParts* tryCreateCollisionMoveLimit(LiveActor* pActor, HitSensor* pBodySensor) {
        const char* pName = "MoveLimit";
        char kcl[0x80];

        snprintf(kcl, sizeof(kcl), "%s.kcl", pName);

        if (!getResourceHolder(pActor)->mFileInfoTable->isExistRes(kcl)) {
            return nullptr;
        }

        const char* pCollisionName = "MoveLimit";

        TPos3f mtx;
        makeMtxTRS(mtx, pActor);

        CollisionParts* pParts = ::createCollisionParts(getResourceHolder(pActor), pCollisionName, pBodySensor, mtx, CollisionScaleType_Default, 3);

        if (pParts != nullptr) {
            validateCollisionParts(pParts);
        }

        return pParts;
    }

    CollisionParts* tryCreateCollisionWaterSurface(LiveActor* pActor, HitSensor* pBodySensor) {
        const char* pName = "WaterSurface";
        char kcl[0x80];

        snprintf(kcl, sizeof(kcl), "%s.kcl", pName);

        if (!getResourceHolder(pActor)->mFileInfoTable->isExistRes(kcl)) {
            return nullptr;
        }

        const char* pCollisionName = "WaterSurface";

        TPos3f mtx;
        makeMtxTRS(mtx, pActor);

        CollisionParts* pParts = ::createCollisionParts(getResourceHolder(pActor), pCollisionName, pBodySensor, mtx, CollisionScaleType_Default, 2);

        if (pParts != nullptr) {
            validateCollisionParts(pParts);
        }

        return pParts;
    }

    f32 getCollisionBoundingSphereRange(LiveActor* pActor) {
        return pActor->mCollisionParts->_D8;
    }

    bool isValidCollisionParts(LiveActor* pActor) {
        return pActor->mCollisionParts->_CC;
    }

    void validateCollisionParts(LiveActor* pActor) {
        validateCollisionParts(pActor->mCollisionParts);
        CollisionParts* pParts = pActor->mCollisionParts;

        if (pParts->_0 != nullptr) {
            pParts->updateBoundingSphereRange();
        } else {
            pParts->updateBoundingSphereRange(pActor->mScale);
        }

        resetAllCollisionMtx(pActor);
    }

    void validateCollisionParts(CollisionParts* pParts) {
        if (!pParts->_CC) {
            pParts->addToBelongZone();
        }

        pParts->_CC = true;
        pParts->_CD = true;
    }

    void invalidateCollisionParts(LiveActor* pActor) {
        invalidateCollisionParts(pActor->mCollisionParts);
    }

    void invalidateCollisionParts(CollisionParts* pParts) {
        if (pParts->_CC) {
            pParts->removeFromBelongZone();
        }

        pParts->_CC = false;
    }

    void onUpdateCollisionParts(LiveActor* pActor) {
        CollisionParts* pParts = pActor->mCollisionParts;

        if (!pParts->_CC) {
            validateCollisionParts(pActor);
        }

        pActor->mCollisionParts->_CE = true;
    }

    void onUpdateCollisionPartsOnetimeImmediately(LiveActor* pActor) {
        CollisionParts* pParts = pActor->mCollisionParts;

        if (!pParts->_CC) {
            validateCollisionParts(pActor);
        }

        pParts = pActor->mCollisionParts;
        pParts->_CF = true;
        makeMtxTR(pActor->getBaseMtx(), pActor);
        setCollisionMtx(pActor, pActor->mCollisionParts);
        pParts->updateMtx();
    }

    void offUpdateCollisionParts(LiveActor* pActor) {
        CollisionParts* pParts = pActor->mCollisionParts;

        if (!pParts->_CC) {
            validateCollisionParts(pActor);
        }

        pActor->mCollisionParts->_CE = false;
    }

    void resetAllCollisionMtx(LiveActor* pActor) {
        CollisionParts* pParts = pActor->mCollisionParts;

        if (pParts->_0 != nullptr) {
            pParts->resetAllMtx();
            return;
        }

        TPos3f mtx;
        ::calcCollisionMtx(&mtx, pActor, false);
        pParts->resetAllMtx(mtx);
    }

    void setCollisionMtx(LiveActor* pActor) {
        setCollisionMtx(pActor, getCollisionParts(pActor));
    }

    void setCollisionMtx(LiveActor* pActor, CollisionParts* pParts) {
        if (!pParts->_CC) {
            return;
        }

        if (pParts->_0 != nullptr) {
            pParts->setMtx();
            return;
        }

        TPos3f mtx;
        ::calcCollisionMtx(&mtx, pActor, false);
        pParts->setMtx(mtx);
    }

    bool isExistCollisionParts(const LiveActor* pActor) {
        return pActor->mCollisionParts != nullptr;
    }

    u32 getCollisionSensorType(const CollisionParts* pCollisionParts) {
        return pCollisionParts->mHitSensor->mType;
    }

    ModelObj* createModelObj(const char* pName, const char* pModelName, MtxPtr pMtx, int drawBufferType, int movementType) {
        ModelObj* modelObj = new ModelObj(pName, pModelName, pMtx, drawBufferType, movementType, -2, false);

        modelObj->initWithoutIter();

        return modelObj;
    }

    DemoObj* createDemoObj(const char* pName, const char* pModelName, MtxPtr pMtx) {
        DemoObj* demoObj = new DemoObj(pName, pMtx);

        initActor(demoObj, pModelName, false);
        demoObj->initWithoutIter();

        return demoObj;
    }

    DemoObj* createDemoObjWithAnimArc(const char* pName, const char* pModelName, const char* pAnimArcName, MtxPtr pMtx) {
        DemoObj* demoObj = new DemoObj(pName, pMtx);

        initActorNoIter(demoObj, pModelName, pAnimArcName, false);
        demoObj->initWithoutIter();

        return demoObj;
    }

    DemoObj* createDemoObj(const char* pName, const char* pModelName, const char* pFuncName, MtxPtr pMtx) {
        DemoObj* demoObj = new DemoObj(pName, pMtx);

        initActor(demoObj, pModelName, pFuncName, false);
        demoObj->initWithoutIter();

        return demoObj;
    }

    DemoObj* createDemoObjWithAnimArc(const char* pName, const char* pModelName, const char* pAnimArcName, const char* pFuncName, MtxPtr pMtx) {
        DemoObj* demoObj = new DemoObj(pName, pMtx);

        initActorNoIter(demoObj, pModelName, pAnimArcName, pFuncName, false);
        demoObj->initWithoutIter();

        return demoObj;
    }

    ModelObj* createModelObjMapObjDecoration(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, -2, -2);
    }

    ModelObj* createModelObjMapObj(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_MapObj, -2);
    }

    ModelObj* createModelObjMapObjStrongLight(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_MapObjStrongLight, -2);
    }

    ModelObj* createModelObjNoSilhouettedMapObj(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_NoSilhouettedMapObj, -2);
    }

    ModelObj* createModelObjNoSilhouettedMapObjStrongLight(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_NoSilhouettedMapObjStrongLight, -2);
    }

    ModelObj* createModelObjIndirectMapObj(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_IndirectMapObj, -2);
    }

    ModelObj* createModelObjPlayerDecoration(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_PlayerDecoration, -2);
    }

    ModelObj* createModelObjEnemy(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_Enemy, MovementType_Enemy);
    }

    ModelObj* createModelObjNpc(const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createModelObj(pName, pModelName, pMtx, DrawBufferType_NPC, -2);
    }

    ModelObj* createModelObjBloomModel(const char* pName, const char* pModelName, MtxPtr pMtx, bool registerDemo) {
        ModelObj* modelObj = new ModelObj(pName, pModelName, pMtx, DrawBufferType_BloomModel, -2, -2, false);

        modelObj->initWithoutIter();

        if (registerDemo) {
            registerDemoSimpleCastAll(modelObj);
        }

        return modelObj;
    }

    PartsModel* createPartsModel(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx, u32 drawBufferType) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, drawBufferType, false);

        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelMapObj2(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_None);
    }

    PartsModel* createPartsModelMapObj(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_MapObj);
    }

    PartsModel* createPartsModelMapObjStrongLight(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_NoSilhouettedMapObjStrongLight);
    }

    PartsModel* createPartsModelNoSilhouettedMapObj(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_NoSilhouettedMapObj);
    }

    PartsModel* createPartsModelEnemy(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        return createPartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_Enemy);
    }

    PartsModel* createPartsModelNpc(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_NPC, false);

        partsModel->initWithoutIter();
        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    PartsModel* createPartsModelIndirectNpc(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_IndirectNpc, false);

        partsModel->initWithoutIter();
        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    PartsModel* createPartsModelEnemyAndFix(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_EnemyDecoration, false);

        partsModel->initFixedPosition(pHost->mPosition, pHost->mRotation, nullptr);
        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelEnemyAndFix(LiveActor* pHost, const char* pName, const char* pModelName, MtxPtr pMtx, const TVec3f& rOffset,
                                            const TVec3f& rRotate, const char* pJointName) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, pMtx, DrawBufferType_Enemy, false);

        partsModel->initFixedPosition(rOffset, rRotate, pJointName);
        partsModel->initWithoutIter();

        return partsModel;
    }

    PartsModel* createPartsModelNpcAndFix(LiveActor* pHost, const char* pName, const char* pModelName, const char* pJointName) {
        PartsModel* partsModel = new PartsModel(pHost, pName, pModelName, nullptr, DrawBufferType_NPC, false);

        partsModel->initFixedPosition(pJointName);
        partsModel->initWithoutIter();
        partsModel->mCheckHiddenHost = true;

        return partsModel;
    }

    void stopSceneAtStep(const LiveActor* pActor, s32 step, s32 sceneStep) {
        if (isStep(pActor, step)) {
            stopScene(sceneStep);
        }
    }

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
    void tryRumblePadAndCameraDistanceVeryStrong(const LiveActor* pActor, f32 near, f32 middle, f32 far) {
        if (isNearPlayerAnyTime(pActor, near)) {
            tryRumblePadVeryStrong(pActor, WPAD_CHAN0);
            shakeCameraStrong();
        } else if (isNearPlayerAnyTime(pActor, middle)) {
            tryRumblePadStrong(pActor, WPAD_CHAN0);
            shakeCameraNormal();
        } else if (isNearPlayerAnyTime(pActor, far)) {
            tryRumblePadMiddle(pActor, WPAD_CHAN0);
            shakeCameraNormalWeak();
        }
    }

    void tryRumblePadAndCameraDistanceStrong(const LiveActor* pActor, f32 near, f32 middle, f32 far) {
        if (isNearPlayerAnyTime(pActor, near)) {
            tryRumblePadStrong(pActor, WPAD_CHAN0);
            shakeCameraNormal();
        } else if (isNearPlayerAnyTime(pActor, middle)) {
            tryRumblePadMiddle(pActor, WPAD_CHAN0);
            shakeCameraNormalWeak();
        } else if (isNearPlayerAnyTime(pActor, far)) {
            tryRumblePadWeak(pActor, WPAD_CHAN0);
            shakeCameraWeak();
        }
    }

    void tryRumblePadAndCameraDistanceMiddle(const LiveActor* pActor, f32 near, f32 middle, f32 far) {
        if (isNearPlayerAnyTime(pActor, near)) {
            tryRumblePadMiddle(pActor, WPAD_CHAN0);
            shakeCameraNormalWeak();
        } else if (isNearPlayerAnyTime(pActor, middle)) {
            tryRumblePadWeak(pActor, WPAD_CHAN0);
            shakeCameraWeak();
        } else if (isNearPlayerAnyTime(pActor, far)) {
            tryRumblePadVeryWeak(pActor, WPAD_CHAN0);
            shakeCameraVeryWeak();
        }
    }

    CollisionParts* getCollisionParts(const LiveActor* pActor) {
        return pActor->mCollisionParts;
    }

};  // namespace MR
