#include "LiveActor/LodCtrl.hpp"
#include "LiveActor/ActorLightCtrl.hpp"
#include "LiveActor/ModelObj.hpp"
#include "Util/ActorMovementUtil.hpp"
#include "Util/CameraUtil.hpp"
#include "Util/LiveActorUtil.hpp"
#include "Util/ModelUtil.hpp"
#include "Util/FileUtil.hpp"
#include "Util/ActorShadowUtil.hpp"
#include <cstdio>

// LodCtrl::LodCtrl

void LodCtrl::offSyncShadowHost() {
    MR::offShadowVisibleSyncHostAll(mHighModel);
    _1A = false;
}

void LodCtrl::appear() {
    MR::showModel(mHighModel);
    mActorLightCtrl = mHighModel->mLightCtrl;

    if (mMiddleModel != nullptr && !MR::isDead(mMiddleModel)) {
        mMiddleModel->makeActorDead();
    }

    if (mLowModel != nullptr && !MR::isDead(mLowModel)) {
        mLowModel->makeActorDead();
    }

    if (!_1A) {
        MR::offShadowVisibleSyncHostAll(mHighModel);
    }
}

void LodCtrl::kill() {
    MR::showModel(mHighModel);
    if (mMiddleModel != nullptr && !MR::isDead(mMiddleModel)) {
        mMiddleModel->makeActorDead();
    }

    if (mLowModel != nullptr && !MR::isDead(mLowModel)) {
        mLowModel->makeActorDead();
    }

    if (!_1A) {
        MR::onShadowVisibleSyncHostAll(mHighModel);
    }

    mActorLightCtrl = nullptr;
}

void LodCtrl::validate() {
    appear();
    _18 = true;
}

void LodCtrl::invalidate() {
    kill();
    _18 = false;
}

void LodCtrl::update() {
    if (!MR::isDead(mHighModel) && _18) {

        bool v2 = false;
        if (mMiddleModel != nullptr || mLowModel != nullptr) {
            v2 = true;
        }

        if (!v2) {
            if (*_28) {
                hideAllModel();
            } else {
                showHighModel();
            }

            return;
        }

        f32 dist = calcDistanceToCamera();
        float f2 = mDistToLow;
        float f0 = mDistToMiddle;

        if (*_28) {
            hideAllModel();
        } else if (*_1C) {
            showHighModel();
        } else if (mMiddleModel != nullptr && *_20) {
            showMiddleModel();
        } else if (mLowModel != nullptr && *_24) {
            showLowModel();
        } else if (dist < f0) {
            showHighModel();
        } else if (mMiddleModel == nullptr && dist < f2) {
            showHighModel();
        } else if (mMiddleModel != nullptr && dist < f2) {
            showMiddleModel();
        } else if (mLowModel) {
            showLowModel();
        }

        if (mCurActiveModel != nullptr) {
            if (mCurActiveModel != mHighModel) {
                MR::copyTransRotateScale(mHighModel, mCurActiveModel);
            }
        }
    }
}

bool LodCtrl::isShowLowModel() const {
    ModelObj* low = mLowModel;
    bool ret = false;
    if (low != nullptr && low == mCurActiveModel) {
        ret = true; 
    }

    return ret;
}

void LodCtrl::setDistanceToMiddle(f32 middle) {
    mDistToMiddle = middle;
}

f32 LodCtrl::calcDistanceToCamera() const {
    if (mDistCameraCalc) {
        return MR::calcCameraDistanceZ(mHighModel->mPosition);
    }

    return MR::calcDistanceToPlayer(mHighModel);
}

void LodCtrl::setDistanceToLow(f32 low) {
    mDistToLow = low;
}

void LodCtrl::setDistanceToMiddleAndLow(f32 middle, f32 low) {
    mDistToMiddle = middle;
    mDistToLow = low;
}

namespace {
    template<typename T>
    void LodFuntionCall(LodCtrl *pCtrl, void (*pFunc)(LiveActor *, T), T arg) NO_INLINE {
        pFunc(pCtrl->mHighModel, arg);

        if (pCtrl->mMiddleModel) {
            pFunc(pCtrl->mMiddleModel, arg);
        }

        if (pCtrl->mLowModel) {
            pFunc(pCtrl->mLowModel, arg);
        }
    }
};

void LodCtrl::setClippingTypeSphereContainsModelBoundingBox(f32 bounds) {
    LodFuntionCall<f32>(this, MR::setClippingTypeSphereContainsModelBoundingBox, bounds);
}

void LodCtrl::setFarClipping(f32 farClip) {
    LodFuntionCall<f32>(this, MR::setClippingFar, farClip);
}


void LodCtrl::showHighModel() {
    if (MR::isHiddenModel(mHighModel)) {
        if (mActorLightCtrl != nullptr) {
            mHighModel->mLightCtrl->copy(mActorLightCtrl);
        }

        mActorLightCtrl = mHighModel->mLightCtrl;
        MR::showModel(mHighModel);
    }
    else {
        if (mMiddleModel != nullptr && !MR::isDead(mMiddleModel)) {
            mMiddleModel->makeActorDead();
        }

        if (mLowModel && !MR::isDead(mLowModel)) {
            mLowModel->makeActorDead();
        }
    }

    mCurActiveModel = mHighModel;
}

void LodCtrl::showMiddleModel() {
    if (MR::isDead(mMiddleModel)) {
        if (mActorLightCtrl != nullptr) {
            mMiddleModel->mLightCtrl->copy(mActorLightCtrl);
        }

        mActorLightCtrl = mMiddleModel->mLightCtrl;
        mMiddleModel->makeActorAppeared();
        MR::calcAnimDirect(mHighModel);
    }
    else {
        if (!MR::isHiddenModel(mHighModel)) {
            MR::hideModelAndOnCalcAnim(mHighModel);
        }

        if (mLowModel != nullptr && !MR::isDead(mLowModel)) {
            mLowModel->makeActorDead();
        }
    }

    mCurActiveModel = mMiddleModel;
}

void LodCtrl::showLowModel() {
    if (MR::isDead(mLowModel)) {
        if (mActorLightCtrl != nullptr) {
            mLowModel->mLightCtrl->copy(mActorLightCtrl);
        }

        mActorLightCtrl = mLowModel->mLightCtrl;
        mLowModel->makeActorAppeared();
        MR::calcAnimDirect(mHighModel);
    }
    else {
        if (!MR::isHiddenModel(mHighModel)) {
            MR::hideModelAndOnCalcAnim(mHighModel);
        }

        if (mMiddleModel != nullptr && !MR::isDead(mMiddleModel)) {
            mMiddleModel->makeActorDead();
        }
    }

    mCurActiveModel = mLowModel;
}

void LodCtrl::hideAllModel() {
    if (!MR::isHiddenModel(mHighModel)) {
        MR::hideModelAndOnCalcAnim(mHighModel);
    }

    if (mMiddleModel != nullptr && !MR::isDead(mMiddleModel)) {
        mMiddleModel->makeActorDead();
    }

    if (mLowModel != nullptr && !MR::isDead(mLowModel)) {
        mLowModel->makeActorDead();
    }

    mCurActiveModel = nullptr;
}

void LodCtrl::setViewCtrlPtr(const bool *a1, const bool *a2, const bool *a3, const bool *a4) {
    _1C = a1;
    _20 = a2;
    _24 = a3;
    _28 = a4;
}

ModelObj* LodCtrl::initLodModel(int movement, int calcAnim, int drawBuffer, bool isLowModel) const {
    const char* resName = MR::getModelResName(mHighModel);
    const char* type = (isLowModel) ? "Low" : "Middle";
    char nameBuf[256];
    snprintf(nameBuf, sizeof(nameBuf), "/ObjectData/%s%s.arc", resName, type);

    if (!MR::isFileExist(nameBuf, false)) {
        return nullptr;
    }

    const char* objName = (isLowModel) ? MR::createLowModelObjName(mHighModel) : MR::createMiddleModelObjName(mHighModel);
    snprintf(nameBuf, sizeof(nameBuf), "%s%s", resName, type);
    ModelObj* highModel = new ModelObj(objName, nameBuf, mHighModel->getBaseMtx(), movement, calcAnim, drawBuffer, false);
    highModel->initWithoutIter();
    highModel->makeActorDead();
    MR::setClippingTypeSphereContainsModelBoundingBox(highModel, 100.0f);
    MR::copyTransRotateScale(mHighModel, highModel);
    return highModel;
}

void LodCtrl::createLodModel(int movement, int calcAnim, int drawBuffer) {
    mMiddleModel = initLodModel(movement, calcAnim, drawBuffer, false);
    mLowModel = initLodModel(movement, calcAnim, drawBuffer, true);

    if (mMiddleModel != nullptr || mLowModel != nullptr) {
        appear();
        _18 = true;
    }
    else {
        kill();
        _18 = false;
    }
}

void LodCtrl::syncMaterialAnimation() {
    if (mMiddleModel != nullptr) {
        MR::syncMaterialAnimation(mMiddleModel, mHighModel);
    }

    if (mLowModel != nullptr) {
        MR::syncMaterialAnimation(mLowModel, mHighModel);
    }
}

void LodCtrl::syncJointAnimation() {
    if (mMiddleModel != nullptr) {
        MR::syncJointAnimation(mMiddleModel, mHighModel);
    }

    if (mLowModel != nullptr) {
        MR::syncJointAnimation(mLowModel, mHighModel);
    } 
}

void LodCtrl::initLightCtrl() {
    if (mMiddleModel != nullptr && mMiddleModel->mLightCtrl == nullptr) {
        MR::initLightCtrl(mMiddleModel);
    }

    if (mLowModel != nullptr && mLowModel->mLightCtrl == nullptr) {
        MR::initLightCtrl(mLowModel);
    }
}

bool LodCtrlFunction::isExistLodLowModel(const char *pName) {
    char buf[0x100];
    snprintf(buf, sizeof(buf), "/ObjectData/%sLow.arc", pName);
    return MR::isFileExist(buf, false);
}

/* unused but sitting in .data */
static const char* sMiddle = "/ObjectData/%sMiddle.arc";
