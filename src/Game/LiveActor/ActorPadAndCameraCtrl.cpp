#include "Game/LiveActor/ActorPadAndCameraCtrl.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/System/ResourceHolder.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include <JSystem/J3DGraphAnimator/J3DAnimation.hpp>
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 8022AF90, const void*, const char*)
EXTERN_UNKNOWN_FUNC(void, 8022AFD0, const char*)

namespace {
    const char* sFileName = "PadAndCameraCtrl";
};

ActorPadAndCameraCtrl* ActorPadAndCameraCtrl::tryCreate(const ModelManager* pManager, const TVec3f* pVec) {
    ResourceHolder* pHolder = pManager->getResourceHolder();

    if (pHolder->mMotionResTable->mCount == 0) {
        return nullptr;
    }

    if (MR::isExistFileInArc(pHolder, "%s.bcsv", ::sFileName)) {
        return new ActorPadAndCameraCtrl(pManager, pVec);
    }

    return nullptr;
}

void ActorPadAndCameraCtrl::update() {
    if (mPlayingBckName != mModelManager->getPlayingBckName()) {
        mPlayingBckName = mModelManager->getPlayingBckName();
        updateInfoBck();
    }

    ActorPadAndCameraInfo* pInfo;

    J3DFrameCtrl* pBckCtrl = mModelManager->getBckCtrl();

    for (s32 i = 0; i < mInfoCount; i++) {
        pInfo = &mInfos[i];

        if (!pInfo->mIsPlaying) {
            continue;
        }

        if (pBckCtrl->checkPass(pInfo->mStartFrame)) {
            pInfo->mIsActive = true;
        }

        if (!pInfo->mIsActive) {
            continue;
        }

        updatePadAndCamera(pInfo);

        if (pInfo->mEndFrame < 0.0f || pBckCtrl->mRate <= 0.0f || pBckCtrl->checkPass(pInfo->mEndFrame)) {
            pInfo->mIsActive = false;
        }
    }
}

ActorPadAndCameraCtrl::ActorPadAndCameraCtrl(const ModelManager* pManager, const TVec3f* pVec)
    : mModelManager(pManager), _4(pVec), mResourceHolder(pManager->getResourceHolder()), mPlayingBckName(), mInfoCount(), mInfos() {
    const JMapInfo* pInfo = MR::tryCreateCsvParser(mResourceHolder, "%s.bcsv", ::sFileName);

    if (pInfo == nullptr) {
        return;
    }

    mInfoCount = MR::getCsvDataElementNum(pInfo);
    mInfos = new ActorPadAndCameraInfo[mInfoCount];

    for (s32 i = 0; i < mInfoCount; i++) {
        ActorPadAndCameraInfo* pPadAndCameraInfo = &mInfos[i];

        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mBckName, pInfo, "BckName", i);
        MR::getCsvDataF32(&pPadAndCameraInfo->mStartFrame, pInfo, "StartFrame", i);
        MR::getCsvDataF32(&pPadAndCameraInfo->mEndFrame, pInfo, "EndFrame", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mPadRumbleName, pInfo, "PadRumbleName", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mCameraShakeName, pInfo, "CameraShakeName", i);
        MR::getCsvDataF32(&pPadAndCameraInfo->mDistanceNear, pInfo, "DistanceNear", i);
        MR::getCsvDataF32(&pPadAndCameraInfo->mDistanceFar, pInfo, "DistanceFar", i);
        MR::getCsvDataF32(&pPadAndCameraInfo->mDistanceInvalid, pInfo, "DistanceInvalid", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mPadRumbleNameMiddle, pInfo, "PadRumbleNameMiddle", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mPadRumbleNameFar, pInfo, "PadRumbleNameFar", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mCameraShakeNameMiddle, pInfo, "CameraShakeNameMiddle", i);
        MR::getCsvDataStrOrNULL(&pPadAndCameraInfo->mCameraShakeNameFar, pInfo, "CameraShakeNameFar", i);
        pPadAndCameraInfo->mIsPlaying = false;
        pPadAndCameraInfo->mIsActive = false;
    }
}

void ActorPadAndCameraCtrl::updateInfoBck() {
    if (mPlayingBckName == nullptr) {
        return;
    }

    ActorPadAndCameraInfo* pInfo;

    for (s32 i = 0; i < mInfoCount; i++) {
        pInfo = &mInfos[i];

        if (pInfo->mBckName == nullptr) {
            continue;
        }

        if (MR::isEqualStringCase(mPlayingBckName, pInfo->mBckName)) {
            pInfo->mIsPlaying = true;
        } else {
            pInfo->mIsPlaying = false;
        }
    }
}

namespace {
    bool isDistanceExistAndFar(f32 distance, f32 threshold) {
        if (threshold < 0.0f) {
            return false;
        }

        return distance > threshold;
    }
};  // namespace

void ActorPadAndCameraCtrl::updatePadAndCamera(const ActorPadAndCameraInfo* pInfo) {
    f32 distance = MR::getPlayerPos()->distance(*_4);

    if (::isDistanceExistAndFar(distance, pInfo->mDistanceInvalid)) {
        return;
    }

    if (::isDistanceExistAndFar(distance, pInfo->mDistanceFar)) {
        fn_8022AF90(this, pInfo->mPadRumbleNameFar);
        fn_8022AFD0(pInfo->mCameraShakeNameFar);
    } else if (::isDistanceExistAndFar(distance, pInfo->mDistanceNear)) {
        fn_8022AF90(this, pInfo->mPadRumbleNameMiddle);
        fn_8022AFD0(pInfo->mCameraShakeNameMiddle);
    } else {
        fn_8022AF90(this, pInfo->mPadRumbleName);
        fn_8022AFD0(pInfo->mCameraShakeName);
    }
}
