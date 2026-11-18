#include "Game/MapObj/ExterminationCheckerWoodBox.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/WoodBox.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

namespace NrvExterminationCheckerWoodBox {
    NEW_NERVE(ExterminationCheckerWoodBoxNrvMove, ExterminationCheckerWoodBox, Move);
};  // namespace NrvExterminationCheckerWoodBox

ExterminationCheckerWoodBox::ExterminationCheckerWoodBox(const char* pName) : LiveActor(pName), mWoodBoxList(), mNumWoodBoxes() {
}

void ExterminationCheckerWoodBox::init(const JMapInfoIter& rIter) {
    MR::connectToSceneMapObjMovement(this);
    mNumWoodBoxes = MR::getChildObjNum(rIter);
    mWoodBoxList = new WoodBox*[mNumWoodBoxes];

    for (s32 i = 0; i < mNumWoodBoxes; i++) {
        mWoodBoxList[i] = new WoodBox("タイムアタック用木箱");
        MR::initChildObj(mWoodBoxList[i], rIter, i);
        mWoodBoxList[i]->registerBreakModelDemoCast();
        MR::registerDemoSimpleCastAll(mWoodBoxList[i]);
    }

    MR::invalidateClipping(this);
    MR::needStageSwitchWriteA(this, rIter);
    MR::needStageSwitchWriteB(this, rIter);
    MR::registerDemoSimpleCastAll(this);
    initNerve(GET_NERVE(ExterminationCheckerWoodBox, ExterminationCheckerWoodBoxNrvMove));
    makeActorAppeared();
}

void ExterminationCheckerWoodBox::exeMove() {
    if (MR::isOnSwitchB(this)) {
        for (int i = 0; i < mNumWoodBoxes; i++) {
            mWoodBoxList[i]->forceReappear();
        }

        MR::offSwitchA(this);
        MR::offSwitchB(this);
        return;
    } else if (!MR::isOnSwitchA(this) && checkAllDestroyed()) {
        MR::onSwitchA(this);
    }
}

bool ExterminationCheckerWoodBox::checkAllDestroyed() {
    for (int i = 0; i < mNumWoodBoxes; i++) {
        if (mWoodBoxList[i]->mHP != 0) {
            return false;
        }
    }

    return true;
}
