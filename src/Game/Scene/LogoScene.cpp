#include "Game/Scene/LogoScene.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/System/MainLoopFramework.hpp"
#include "Game/Util/DrawUtil.hpp"

namespace NrvLogoScene {
    NEW_NERVE(LogoSceneNrvStrapFadein, LogoScene, StrapFadein);
    NEW_NERVE(LogoSceneNrvStrapDisplay, LogoScene, StrapDisplay);
    NEW_NERVE(LogoSceneNrvStrapFadeout, LogoScene, StrapFadeout);
    NEW_NERVE(LogoSceneNrvMountGameData, LogoScene, MountGameData);
    NEW_NERVE(LogoSceneNrvWaitReadDoneSystemArchive, LogoScene, WaitReadDoneSystemArchive);
    NEW_NERVE(LogoSceneNrvDeactive, LogoScene, Deactive);
};  // namespace NrvLogoScene

LogoScene::LogoScene() : Scene("LogoScene"), mStrapLayout(), mLogoFader(), _19() {
    MainLoopFramework::setUseVFilterOff();
    MainLoopFramework::setUseAlphaOff();
}

LogoScene::~LogoScene() {
    MainLoopFramework::setUseVFilterOn();
    MainLoopFramework::setUseAlphaOn();
}

void LogoScene::init() {
    initNerve(GET_NERVE(LogoScene, LogoSceneNrvStrapFadein));

    SceneFunction::createHioBasicNode(this);
    SceneFunction::initForNameObj();

    MR::createSceneObj(SceneObj_18);
    MR::createSceneObj(SceneObj_19);

    initLayout();
}

void LogoScene::update() {
    updateNerve();
    SceneFunction::executeMovementList();
}

void LogoScene::calcAnim() {
    SceneFunction::executeCalcAnimList();
    SceneFunction::executeCalcViewAndEntryList2D();
}

void LogoScene::draw() const {
    MR::drawInit();

    GXColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    MR::fillScreen(color);
    MR::clearZBuffer();
    MR::drawInitFor2DModel();

    CategoryList::drawOpa(MR::DrawBufferType_0x29);
    CategoryList::drawXlu(MR::DrawBufferType_0x29);
    CategoryList::execute(MR::DrawType_Layout);
    CategoryList::execute(MR::DrawType_EffectDraw2D);
    CategoryList::execute(MR::DrawType_EffectDrawFor2DModel);
    CategoryList::execute(MR::DrawType_CometScreenFilter);
    CategoryList::execute(MR::DrawType_WipeLayout);
}

bool LogoScene::isDisplayStrapRemineder() const {
    return isNerve(GET_NERVE(LogoScene, LogoSceneNrvDeactive)) || isNerve(GET_NERVE(LogoScene, LogoSceneNrvStrapFadein)) ||
           isNerve(GET_NERVE(LogoScene, LogoSceneNrvStrapDisplay)) || isNerve(GET_NERVE(LogoScene, LogoSceneNrvStrapFadeout)) ||
           isNerve(GET_NERVE(LogoScene, LogoSceneNrvWaitReadDoneSystemArchive));
}

// void LogoScene::exeStrapFadein() {
// }

// void LogoScene::exeStrapDisplay() {
// }

// void LogoScene::exeMountGameData() {
// }

// void LogoScene::initLayout() {
// }

// bool LogoScene::tryFadeinLayout(LayoutActor* pActor) {
// }

// bool LogoScene::tryFadeoutLayout(LayoutActor* pActor) {
// }
