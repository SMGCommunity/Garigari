#include "Game/Util/LiveActorUtil.hpp"
#include "Game/LiveActor/ClippingActorHolder.hpp"
#include "Game/LiveActor/ClippingDirector.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/LodCtrl.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"
#include "JSystem/JGeometry/TVec.hpp"
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
    void setClippingFar50m(LiveActor* pActor);
    void setClippingFar100m(LiveActor* pActor);
    void setClippingFar200m(LiveActor* pActor);
    void setClippingFar300m(LiveActor* pActor);
    void setClippingFarMax(LiveActor* pActor);
    void setClippingFar(LiveActor* pActor, f32 farDistance);

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
};  // namespace MR
