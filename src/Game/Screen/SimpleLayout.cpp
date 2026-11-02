#include "Game/Screen/SimpleLayout.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/NPC/TalkTextFormer.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/MessageUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "decomp.h"

// TODO: Seems to be a function akin to StartActionSound for layouts
EXTERN_UNKNOWN_FUNC(void, 800085E0, LayoutActor*, const char*, s32, s32);

namespace NrvSimpleTalkTextLayout {
    NEW_NERVE(SimpleTalkTextLayoutNrvStart, SimpleTalkTextLayout, Start);
    NEW_NERVE(SimpleTalkTextLayoutNrvUpdate, SimpleTalkTextLayout, Update);
    NEW_NERVE(SimpleTalkTextLayoutNrvEnd, SimpleTalkTextLayout, End);
};  // namespace NrvSimpleTalkTextLayout

SimpleLayout::SimpleLayout(const char* pName, const char* pLayoutName, u32 rootPaneAnimLayerNum, int drawType) : LayoutActor(pName, true) {
    int type = drawType >= 0 ? drawType : MR::DrawType_Layout;

    MR::connectToScene(this, MR::MovementType_Layout, MR::CalcAnimType_Layout, MR::DrawBufferType_None, type);
    initLayoutManager(pLayoutName, rootPaneAnimLayerNum);
    initActionSound(4, nullptr, 0);
}

SimpleEffectLayout::SimpleEffectLayout(const char* pName, const char* pLayoutName, u32 rootPaneAnimLayerNum, int drawType)
    : SimpleLayout(pName, pLayoutName, rootPaneAnimLayerNum, drawType) {
    initEffectKeeper(0, nullptr, nullptr);
}

//CLEAME: DrawType_FileSelect doesn't fit here, should probably one of the Layout drawtypes (DrawType_TalkLayout)
SimpleTalkTextLayout::SimpleTalkTextLayout(const char* pName, const char* pLayoutName, u32 rootPaneAnimLayerNum)
    : SimpleLayout(pName, pLayoutName, rootPaneAnimLayerNum, MR::DrawType_FileSelect), mFormerText() {
    mFormerText = new TalkTextFormer(this, "Text00");
    initNerve(GET_NERVE(SimpleTalkTextLayout, SimpleTalkTextLayoutNrvStart));
    kill();
}

void SimpleTalkTextLayout::startTalk(const char* pMessageId) {
    MR::startAnimAndSetFrameAndStop(this, "Appear", 0.0f, 0);
    MR::hidePane(this, "ShaBeak");
    MR::hidePane(this, "PicBeak");

    if (pMessageId != nullptr) {
        mFormerText->formMessage(MR::getGameMessageDirect(pMessageId), 1);
    }

    LayoutActor::appear();
    setNerve(GET_NERVE(SimpleTalkTextLayout, SimpleTalkTextLayoutNrvStart));
}

void SimpleTalkTextLayout::endTalk() {
    setNerve(GET_NERVE(SimpleTalkTextLayout, SimpleTalkTextLayoutNrvEnd));
}

void SimpleTalkTextLayout::exeStart() {
    if (MR::isFirstStep(this)) {
        MR::startAnim(this, "Appear", 0);
        fn_800085E0(this, "Appear", -1, -1);
    }

    if (MR::isAnimStopped(this, 0)) {
        setNerve(GET_NERVE(SimpleTalkTextLayout, SimpleTalkTextLayoutNrvUpdate));
    }
}

void SimpleTalkTextLayout::exeUpdate() {
    mFormerText->updateTalking();
}

void SimpleTalkTextLayout::exeEnd() {
    if (MR::isFirstStep(this)) {
        MR::startAnim(this, "End", 0);
        fn_800085E0(this, "End", -1, -1);
    }

    if (MR::isAnimStopped(this, 0)) {
        kill();
    }
}
