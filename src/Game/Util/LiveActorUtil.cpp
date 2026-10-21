#include "Game/Util/LiveActorUtil.hpp"
#include "Game/LiveActor/ClippingActorHolder.hpp"
#include "Game/LiveActor/ClippingDirector.hpp"
#include "Game/LiveActor/DisplayListMaker.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/MirrorCamera.hpp"
#include "Game/LiveActor/LodCtrl.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/System/ResourceInfo.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "JSystem/J3DGraphAnimator/J3DModel.hpp"
#include "JSystem/J3DGraphBase/J3DStruct.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"
#include "JSystem/JGeometry/TVec.hpp"
#include "revolution/mtx.h"
#include "revolution/types.h"

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

    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius, const TVec3f* pClippingPos);
    void setClippingTypeSphereContainsModelBoundingBox(LiveActor* pActor, f32 radiusExtension);

    void setPosition(LiveActor* pActor, const JGeometry::TVec3< float >& rPosition) {
        pActor->mPosition.set(rPosition);
    }

    void setPosition(LiveActor* pActor, f32 x, f32 y, f32 z) {
        pActor->mPosition.set(x, y, z);
    }

    void setRotation(LiveActor* pActor, const JGeometry::TVec3< float >& rRotation) {
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

    void setScale(LiveActor* pActor, const JGeometry::TVec3< float >& rScale) {
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
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped)
            return false;

        return true;
    }

    bool isValidCalcAnim(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped || pActor->mFlags.mIsOnCalcAnim)
            return false;

        return true;
    }

    bool isValidCalcViewAndEntry(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped)
            return false;

        return true;
    }

    bool isValidDraw(const LiveActor* pActor) {
        if (pActor->mFlags.mIsDead || pActor->mFlags.mIsClipped || pActor->mFlags.mIsNoEntryDrawBuffer)
            return false;

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
        ClippingDirector* clippingDirector = MR::getClippingDirector();

        clippingDirector->mActorHolder->setTypeToSphere(pActor, clippingRadius, nullptr);
    }

    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius, const JGeometry::TVec3< float >* pClippingPos) {
        ClippingDirector* clippingDirector = MR::getClippingDirector();

        clippingDirector->mActorHolder->setTypeToSphere(pActor, clippingRadius, pClippingPos);
    }

    void setClippingTypeSphereContainsModelBoundingBox(LiveActor* pActor, f32 radiusExtension) {
        f32 modelBoundingRadius = 0.0f;
        MR::calcModelBoundingRadius(&modelBoundingRadius, pActor);

        f32 expandedRadius = modelBoundingRadius + radiusExtension;
        ClippingDirector* clippingDirector = MR::getClippingDirector();

        clippingDirector->mActorHolder->setTypeToSphere(pActor, expandedRadius, nullptr);
    }

    void setClippingFar50m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 7);
    }

    void setClippingFar100m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 6);
    }

    void setClippingFar200m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 5);
    }

    void setClippingFar300m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 4);
    }

    void setClippingFar400m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 3);
    }

    void setClippingFar500m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 2);
    }

    void setClippingFar600m(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 1);
    }

    void setClippingFarMax(LiveActor* pActor) {
        MR::getClippingDirector()->mActorHolder->setFarClipLevel(pActor, 0);
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
        if (pActor->mFlags.mIsClippingInvalid)
            MR::getClippingDirector()->mActorHolder->validateClipping(pActor);
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
        bool nearClip = MR::isJudgedToNearClip(pActor->mPosition, nearDistance);

        if (nearClip) {
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

    void initJointTransform(const LiveActor* pActor) {
        pActor->mModelManager->initJointTransform();
    }

    XjointTransform* getJointTransform(const LiveActor* pActor, const char* pName) {
        return pActor->mModelManager->getJointTransform(pName);
    }

    bool isStep(const LiveActor* pActor, s32 step) {
        return pActor->getNerveStep() == step;
    }

    bool isFirstStep(const LiveActor* pActor) {
        return isStep(pActor, 0);
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

    f32 calcNerveEaseOutValue(const LiveActor* pActor, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseOutValue(calcNerveRate(pActor, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseInOutValue(const LiveActor* pActor, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMax), valueStart, valueEnd, 1.0f);
    }

    f32 calcNerveEaseInOutValue(const LiveActor* pActor, s32 stepMin, s32 stepMax, f32 valueStart, f32 valueEnd) {
        return getEaseInOutValue(calcNerveRate(pActor, stepMin, stepMax), valueStart, valueEnd, 1.0f);
    }

    void setNerveAtStep(LiveActor* pActor, const Nerve* pNerve, s32 step) {
        if (pActor->getNerveStep() == step) {
            pActor->setNerve(pNerve);
        }
    }

    void setNerveAtBckStopped(LiveActor* pActor, const Nerve* pNerve) {
        if (pActor->mModelManager->isBckStopped()) {
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

    bool isExistBinder(const LiveActor* pActor) {
        return pActor->mBinder != nullptr;
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

    void invalidateCollisionParts(LiveActor* pActor) {
        invalidateCollisionParts(pActor->mCollisionParts);
    }

    void stopSceneAtStep(const LiveActor* pActor, s32 step, s32 sceneStep) {
        if (isStep(pActor, step)) {
            stopScene(sceneStep);
        }
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

    void setCollisionMtx(LiveActor* pActor) {
        setCollisionMtx(pActor, getCollisionParts(pActor));
    }

    CollisionParts* getCollisionParts(const LiveActor* pActor) {
        return pActor->mCollisionParts;
    }

    bool isExistCollisionParts(const LiveActor* pActor) {
        return pActor->mCollisionParts != nullptr;
    }
};  // namespace MR
