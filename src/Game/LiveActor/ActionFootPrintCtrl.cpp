#include "Game/LiveActor/ActionFootPrintCtrl.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include "JSystem/J3DGraphAnimator/J3DAnimation.hpp"

// TODO: get them from `FootPrint`
FootPrint* createFootPrintFromArc(const LiveActor*);
void addFootPrint(FootPrint*, const LiveActor*, const char*, bool, f32);
void addFootPrint(FootPrint*, const LiveActor*, const TVec3f&, bool, f32);

namespace {
    const char* sResourceName = "ActionFootPrintCtrl";
};

ActionFootPrintInfo::ActionFootPrintInfo() : mBckName(), mBckStartFrame(), mJointName(), mIsRight(), mIsPlaying() {
}

ActionFootPrintCtrl* ActionFootPrintCtrl::tryCreate(LiveActor* pActor) {
    if (MR::isExistFileInArc(MR::getResourceHolder(pActor), "%s.bcsv", ::sResourceName)) {
        return new ActionFootPrintCtrl(pActor);
    }

    return nullptr;
}

void ActionFootPrintCtrl::update() {
    if (mPlayingBckName != MR::getPlayingBckName(mHost)) {
        mPlayingBckName = MR::getPlayingBckName(mHost);
        findAndUpdateFootPrint();
    }

    ActionFootPrintInfo* pInfo;
    J3DFrameCtrl* pBckCtrl = MR::getBckCtrl(mHost);

    for (s32 i = 0; i < mFootPrintInfoCount; i++) {
        pInfo = &mFootPrintInfos[i];

        if (!pInfo->mIsPlaying) {
            continue;
        }

        if (!pBckCtrl->checkPass(pInfo->mBckStartFrame)) {
            continue;
        }

        if (pInfo->mJointName != nullptr) {
            addFootPrint(mFootPrint, mHost, pInfo->mJointName, pInfo->mIsRight != false, 200.0f);
        } else {
            addFootPrint(mFootPrint, mHost, mHost->mPosition, pInfo->mIsRight != false, 200.0f);
        }
    }
}

ActionFootPrintCtrl::ActionFootPrintCtrl(LiveActor* pActor) : mHost(pActor), mPlayingBckName(), mFootPrint(), mFootPrintInfoCount(), mFootPrintInfos() {
    const JMapInfo* pInfo = MR::tryCreateCsvParser(MR::getResourceHolder(mHost), "%s.bcsv", ::sResourceName);

    if (pInfo == nullptr) {
        return;
    }

    s32 elementCount = MR::getCsvDataElementNum(pInfo);
    mFootPrintInfoCount = elementCount;
    
    if (mFootPrintInfoCount > 0) {
        mFootPrint = createFootPrintFromArc(mHost);
    }

    mFootPrintInfos = new ActionFootPrintInfo[elementCount];

    for (s32 i = 0; i < mFootPrintInfoCount; i++) {
        ActionFootPrintInfo* pFootPrintInfo = &mFootPrintInfos[i];

        MR::getCsvDataStr(&pFootPrintInfo->mBckName, pInfo, "BckName", i);
        MR::getCsvDataF32(&pFootPrintInfo->mBckStartFrame, pInfo, "BckStartFrame", i);
        MR::getCsvDataStrOrNULL(&pFootPrintInfo->mJointName, pInfo, "JointName", i);

        const char* isRight = nullptr;
        MR::getCsvDataStr(&isRight, pInfo, "IsRight", i);

        if (isRight != nullptr && isRight[0] == 'o') {
            pFootPrintInfo->mIsRight = true;
        }
    }
}

void ActionFootPrintCtrl::findAndUpdateFootPrint() {
    if (mPlayingBckName == nullptr) {
        return;
    }

    ActionFootPrintInfo* pInfo;

    for (s32 i = 0; i < mFootPrintInfoCount; i++) {
        pInfo = &mFootPrintInfos[i];

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
