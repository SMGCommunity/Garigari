#include "Game/LiveActor/ActorAnimKeeper.hpp"
#include "Game/System/ResourceHolder.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include <cstdio>

namespace {
    const char* sFileName = "ActorAnimCtrl";
};  // namespace

ActorAnimDataInfo::ActorAnimDataInfo() : mName(), mStartFrame(-1.0f), mIsKeepAnim() {
}

ActorAnimKeeperInfo::ActorAnimKeeperInfo() : mName() {
}

ActorAnimKeeper* ActorAnimKeeper::tryCreate(LiveActor* pActor) {
    const ResourceHolder* pResourceHolder = MR::getResourceHolder(pActor);

    if (pResourceHolder->mMotionResTable->mCount == 0 && pResourceHolder->mBtkResTable->mCount == 0 && pResourceHolder->mBrkResTable->mCount == 0 &&
        pResourceHolder->mBpkResTable->mCount == 0 && pResourceHolder->mBtpResTable->mCount == 0 && pResourceHolder->mBvaResTable->mCount == 0) {
        return nullptr;
    }

    if (MR::isExistFileInArc(pResourceHolder, "%s.bcsv", ::sFileName)) {
        return new ActorAnimKeeper(pActor);
    }

    return nullptr;
}

namespace {
    const char* getAnimName(const ActorAnimKeeperInfo* pKeeperInfo, const ActorAnimDataInfo& rDataInfo) {
        const char* name = rDataInfo.mName;
        if (name == nullptr) {
            name = pKeeperInfo->mName;
        }
        return name;
    };
};  // namespace

bool ActorAnimKeeper::start(const char* pName) {
    ActorAnimKeeperInfo* info = findAnimInfo(pName);

    mCurrentInfo = info;
    if (mCurrentInfo == nullptr) {
        return false;
    }

    const char* BckName = ::getAnimName(info, info->mBckInfo);
    const char* BtkName = ::getAnimName(info, info->mBtkInfo);
    const char* BrkName = ::getAnimName(info, info->mBrkInfo);
    const char* BpkName = ::getAnimName(info, info->mBpkInfo);
    const char* BtpName = ::getAnimName(info, info->mBtpInfo);
    const char* BvaName = ::getAnimName(info, info->mBvaInfo);

    if (MR::isExistBck(mActor, BckName) && (!info->mBckInfo.mIsKeepAnim || !MR::isBckPlaying(mActor, BckName))) {
        if (MR::isEqualStringCase(BckName, info->mName)) {
            MR::startBck(mActor, BckName, nullptr);
        } else {
            MR::startBck(mActor, BckName, info->mName);
        }
    }

    if (MR::isExistBtk(mActor, BtkName) && (!info->mBtkInfo.mIsKeepAnim || !MR::isBtkPlaying(mActor, BtkName))) {
        MR::startBtk(mActor, BtkName);
    }

    if (MR::isExistBrk(mActor, BrkName) && (!info->mBrkInfo.mIsKeepAnim || !MR::isBrkPlaying(mActor, BrkName))) {
        MR::startBrk(mActor, BrkName);
    }

    if (MR::isExistBpk(mActor, BpkName) && (!info->mBpkInfo.mIsKeepAnim || !MR::isBpkPlaying(mActor, BpkName))) {
        MR::startBpk(mActor, BpkName);
    }

    if (MR::isExistBtp(mActor, BtpName) && (!info->mBtpInfo.mIsKeepAnim || !MR::isBtpPlaying(mActor, BtpName))) {
        MR::startBtp(mActor, BtpName);
    }

    if (MR::isExistBva(mActor, BvaName) && (!info->mBvaInfo.mIsKeepAnim || !MR::isBvaPlaying(mActor, BvaName))) {
        MR::startBva(mActor, BvaName);
    }

    return true;
}

void ActorAnimKeeper::update() {
}

bool ActorAnimKeeper::trySetAllFrame(f32 frame) {
    if (mCurrentInfo == nullptr) {
        return false;
    }

    if (MR::isBckPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBckInfo))) {
        MR::setBckFrame(mActor, frame);
    }

    if (MR::isBtkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBtkInfo))) {
        MR::setBtkFrame(mActor, frame);
    }

    if (MR::isBrkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBrkInfo))) {
        MR::setBrkFrame(mActor, frame);
    }

    if (MR::isBpkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBpkInfo))) {
        MR::setBpkFrame(mActor, frame);
    }

    if (MR::isBtpPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBtpInfo))) {
        MR::setBtpFrame(mActor, frame);
    }

    if (MR::isBvaPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBvaInfo))) {
        MR::setBvaFrame(mActor, frame);
    }

    return true;
}

bool ActorAnimKeeper::isExistAnim(const char* pName) {
    if (findAnimInfo(pName)) {
        return true;
    }

    return MR::isExistAnim(mActor, pName);
}

bool ActorAnimKeeper::isAnyAnimPlaying(const char* pName) const {
    if (mCurrentInfo != nullptr) {
        if (!MR::isEqualStringCase(mCurrentInfo->mName, pName)) {
            return false;
        }

        const char* pAnimName = ::getAnimName(mCurrentInfo, mCurrentInfo->mBckInfo);
        if (MR::isExistBck(mActor, pAnimName)) {
            return MR::isBckPlaying(mActor, pAnimName);
        }

        if (MR::isBtkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBtkInfo)) ||
            MR::isBrkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBrkInfo)) ||
            MR::isBpkPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBpkInfo)) ||
            MR::isBtpPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBtpInfo)) ||
            MR::isBvaPlayingIfExist(mActor, ::getAnimName(mCurrentInfo, mCurrentInfo->mBvaInfo))) {
            return true;
        }

        return false;
    }

    return MR::isPlayingAnim(mActor, pName);
}

const char* ActorAnimKeeper::getInfoName() const {
    if (mCurrentInfo != nullptr) {
        return mCurrentInfo->mName;
    }

    return nullptr;
}

namespace {
    void getCsvDataAnimData(ActorAnimDataInfo* pDataInfo, const char* pAnimType, const JMapInfo* pInfo, s32 index) {
        char pOut[128];
        snprintf(pOut, sizeof(pOut), "%sName", pAnimType);
        MR::getCsvDataStrOrNULL(&pDataInfo->mName, pInfo, pOut, index);

        snprintf(pOut, sizeof(pOut), "%sStartFrame", pAnimType);
        MR::getCsvDataF32(&pDataInfo->mStartFrame, pInfo, pOut, index);

        snprintf(pOut, sizeof(pOut), "%sIsKeepAnim", pAnimType);
        MR::getCsvDataU8(&pDataInfo->mIsKeepAnim, pInfo, pOut, index);
    }
};  // namespace

ActorAnimKeeper::ActorAnimKeeper(LiveActor* pActor) : mActor(pActor), mNumInfo(), mInfoArray(), mCurrentInfo() {
    MR::getResourceHolder(mActor);
    initAnimData();
}

bool ActorAnimKeeper::initAnimData() {
    const JMapInfo* csvParser = MR::tryCreateCsvParser(MR::getResourceHolder(mActor), "%s.bcsv", ::sFileName);

    s32 numInfo = 0;
    if (csvParser != nullptr) {
        numInfo = MR::getCsvDataElementNum(csvParser);
    }

    mNumInfo = numInfo;
    mInfoArray = new ActorAnimKeeperInfo[mNumInfo];

    for (int i = 0; i < mNumInfo; i++) {
        ActorAnimKeeperInfo* currentInfo = &mInfoArray[i];
        MR::getCsvDataStr(&currentInfo->mName, csvParser, "ActorAnimName", i);
        ::getCsvDataAnimData(&currentInfo->mBckInfo, "Bck", csvParser, i);
        ::getCsvDataAnimData(&currentInfo->mBtkInfo, "Btk", csvParser, i);
        ::getCsvDataAnimData(&currentInfo->mBrkInfo, "Brk", csvParser, i);
        ::getCsvDataAnimData(&currentInfo->mBpkInfo, "Bpk", csvParser, i);
        ::getCsvDataAnimData(&currentInfo->mBtpInfo, "Btp", csvParser, i);
        ::getCsvDataAnimData(&currentInfo->mBvaInfo, "Bva", csvParser, i);
    }
    return true;
}

ActorAnimKeeperInfo* ActorAnimKeeper::findAnimInfo(const char* pName) const {
    ActorAnimKeeperInfo* currentInfo;
    for (int i = 0; i < mNumInfo; i++) {
        currentInfo = &mInfoArray[i];
        if (MR::isEqualStringCase(currentInfo->mName, pName)) {
            return currentInfo;
        }
    }
    return nullptr;
}
