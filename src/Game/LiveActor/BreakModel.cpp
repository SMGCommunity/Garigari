#include "Game/LiveActor/BreakModel.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvBreakModel {
    NEW_NERVE(BreakModelNrvWait, BreakModel, Wait);
    NEW_NERVE(BreakModelNrvBreak, BreakModel, Break);
};  // namespace NrvBreakModel

BreakModel::BreakModel(LiveActor* pActor, const char* pName, const char* pModelName, MtxPtr pMtx, const char* pAnimName)
    : LiveActor(pName), mHost(pActor), mAnimName(pAnimName), mMtx(pMtx) {
    if (mMtx != nullptr) {
        MR::setPosition(this, mMtx[0][3], mMtx[1][3], mMtx[2][3]);
    } else {
        MR::copyTransRotateScale(mHost, this);
    }

    MR::initActor(this, pModelName, false);
}

void BreakModel::init(const JMapInfoIter& rIter) {
    MR::invalidateClipping(this);
    initNerve(GET_NERVE(BreakModel, BreakModelNrvWait));
    makeActorDead();
}

void BreakModel::appear() {
    if (mMtx != nullptr) {
        MR::setPosition(this, mMtx[0][3], mMtx[1][3], mMtx[2][3]);
    } else {
        MR::copyTransRotateScale(mHost, this);
    }

    LiveActor::appear();
    setNerve(GET_NERVE(BreakModel, BreakModelNrvBreak));
}

void BreakModel::exeWait() {

}

void BreakModel::exeBreak() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, mAnimName);
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}

void BreakModel::calcAndSetBaseMtx() {
    if (mMtx != nullptr) {
        mPosition.set< f32 >(mMtx[0][3], mMtx[1][3], mMtx[2][3]);
        MR::setBaseTRMtx(this, mMtx);
    } else {
        LiveActor::calcAndSetBaseMtx();
    }
}
