#include "Game/LiveActor/ActionBgmCtrl.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/Util/BgmUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include <JSystem/J3DGraphAnimator/J3DAnimation.hpp>

namespace {
    const char* sFileName = "ActionBgmCtrl";
};  // namespacea

ActionBgmInfo::ActionBgmInfo()
    : mBckName(), mBckStartFrame(), mBgmName(), mBgmStateNo(-1), mIsBgmStopped(), mBgmFadeStep(60), mStageName(), mStageScenarioNo(-1), mIsPlaying(),
      mIsUpdated() {
}

ActionBgmCtrl* ActionBgmCtrl::tryCreate(const ModelManager* pManager) {
    if (MR::isExistFileInArc(pManager->getResourceHolder(), "%s.bcsv", ::sFileName)) {
        return new ActionBgmCtrl(pManager);
    }

    return nullptr;
}

namespace {
    bool isCurrentStageScenario(const char* pStageName, s32 scenario) {
        if (pStageName != nullptr && !MR::isEqualStageName(pStageName)) {
            return false;
        }

        if (scenario > 0 && scenario != MR::getCurrentScenarioNo()) {
            return false;
        }

        return true;
    }
};  // namespace

void ActionBgmCtrl::update() {
    if (mPlayingBckName != mModelManager->getPlayingBckName()) {
        mPlayingBckName = mModelManager->getPlayingBckName();
        findAndUpdateBgm();
    }

    ActionBgmInfo* pInfo;
    J3DFrameCtrl* pBckCtrl = mModelManager->getBckCtrl();

    for (s32 i = 0; i < mBgmInfoCount; i++) {
        pInfo = &mBgmInfos[i];

        if (!pInfo->mIsPlaying) {
            continue;
        }

        if (pInfo->mIsUpdated) {
            continue;
        }

        if (!pBckCtrl->checkPass(pInfo->mBckStartFrame)) {
            continue;
        }

        if (!isCurrentStageScenario(pInfo->mStageName, pInfo->mStageScenarioNo)) {
            continue;
        }

        updateBgm(pInfo);
    }
}

ActionBgmCtrl::ActionBgmCtrl(const ModelManager* pManager) : mModelManager(pManager), mPlayingBckName(), mBgmInfoCount(), mBgmInfos() {
    const JMapInfo* pInfo = MR::tryCreateCsvParser(mModelManager->getResourceHolder(), "%s.bcsv", ::sFileName);

    if (pInfo == nullptr) {
        return;
    }

    mBgmInfoCount = MR::getCsvDataElementNum(pInfo);
    mBgmInfos = new ActionBgmInfo[mBgmInfoCount];

    for (s32 i = 0; i < mBgmInfoCount; i++) {
        ActionBgmInfo* pBgmInfo = &mBgmInfos[i];
        MR::getCsvDataStrOrNULL(&pBgmInfo->mBckName, pInfo, "BckName", i);
        MR::getCsvDataF32(&pBgmInfo->mBckStartFrame, pInfo, "BckStartFrame", i);
        MR::getCsvDataStrOrNULL(&pBgmInfo->mBgmName, pInfo, "BgmName", i);
        MR::getCsvDataS32(&pBgmInfo->mBgmStateNo, pInfo, "BgmStateNo", i);

        const char* pIsBgmStop = nullptr;
        MR::getCsvDataStr(&pIsBgmStop, pInfo, "IsBgmStop", i);

        if (pIsBgmStop != nullptr && pIsBgmStop[0] == 'o') {
            pBgmInfo->mIsBgmStopped = true;
        }

        MR::getCsvDataS32(&pBgmInfo->mBgmFadeStep, pInfo, "BgmFadeStep", i);
        MR::getCsvDataStrOrNULL(&pBgmInfo->mStageName, pInfo, "StageName", i);
        MR::getCsvDataS32(&pBgmInfo->mStageScenarioNo, pInfo, "StageScenarioNo", i);
    }
}

void ActionBgmCtrl::findAndUpdateBgm() {
    if (mPlayingBckName == nullptr) {
        return;
    }

    ActionBgmInfo* pInfo;

    for (s32 i = 0; i < mBgmInfoCount; i++) {
        pInfo = &mBgmInfos[i];

        if (pInfo->mBckName == nullptr) {
            continue;
        }

        if (MR::isEqualStringCase(mPlayingBckName, pInfo->mBckName)) {
            pInfo->mIsPlaying = true;
            continue;
        }

        if (pInfo->mIsPlaying && !pInfo->mIsUpdated && isCurrentStageScenario(pInfo->mStageName, pInfo->mStageScenarioNo)) {
            updateBgm(pInfo);
        }

        pInfo->mIsPlaying = false;
        pInfo->mIsUpdated = false;
    }
}

void ActionBgmCtrl::updateBgm(ActionBgmInfo* pInfo) {
    if (pInfo->mBgmName != nullptr) {
        MR::startStageBGM(pInfo->mBgmName, false);
    }

    if (pInfo->mBgmStateNo >= 0) {
        MR::setStageBGMState(pInfo->mBgmStateNo, pInfo->mBgmFadeStep);
    }

    if (pInfo->mIsBgmStopped) {
        MR::stopStageBGM(pInfo->mBgmFadeStep);
    }

    pInfo->mIsUpdated = true;
}
