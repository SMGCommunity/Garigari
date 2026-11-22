#include "Game/MapObj/ExterminationCheckerWoodBox.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/WoodBox.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

namespace NrvExterminationCheckerWoodBox {
    NEW_NERVE(ExterminationCheckerWoodBoxNrvWatching, ExterminationCheckerWoodBox, Watching);
};  // namespace NrvExterminationCheckerWoodBox

ExterminationCheckerWoodBox::ExterminationCheckerWoodBox(const char* pName) : LiveActor(pName), mWoodBoxes(), mWoodBoxNum() {
}

void ExterminationCheckerWoodBox::init(const JMapInfoIter& rIter) {
    MR::connectToSceneMapObjMovement(this);
    mWoodBoxNum = MR::getChildObjNum(rIter);
    mWoodBoxes = new WoodBox*[mWoodBoxNum];

    for (s32 i = 0; i < mWoodBoxNum; i++) {
        mWoodBoxes[i] = new WoodBox("タイムアタック用木箱");
        MR::initChildObj(mWoodBoxes[i], rIter, i);
        mWoodBoxes[i]->registerBreakModelDemoCast();
        MR::registerDemoSimpleCastAll(mWoodBoxes[i]);
    }

    MR::invalidateClipping(this);
    MR::needStageSwitchWriteA(this, rIter);
    MR::needStageSwitchWriteB(this, rIter);
    MR::registerDemoSimpleCastAll(this);
    initNerve(GET_NERVE(ExterminationCheckerWoodBox, ExterminationCheckerWoodBoxNrvWatching));
    makeActorAppeared();
}

void ExterminationCheckerWoodBox::exeWatching() {
    if (MR::isOnSwitchB(this)) {
        for (s32 i = 0; i < mWoodBoxNum; i++) {
            mWoodBoxes[i]->forceReappear();
        }

        MR::offSwitchA(this);
        MR::offSwitchB(this);
    } else if (!MR::isOnSwitchA(this) && checkAllDestroyed()) {
        MR::onSwitchA(this);
    }
}

bool ExterminationCheckerWoodBox::checkAllDestroyed() {
    for (s32 i = 0; i < mWoodBoxNum; i++) {
        if (mWoodBoxes[i]->mHP != 0) {
            return false;
        }
    }

    return true;
}
