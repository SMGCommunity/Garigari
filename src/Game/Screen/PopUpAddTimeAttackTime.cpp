#include "Game/Screen/PopUpAddTimeAttackTime.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/StarPointerUtil.hpp"

namespace NrvPopUpAddTimeAttackTime {
    NEW_NERVE(PopUpAddTimeAttackTimeNrvHide, PopUpAddTimeAttackTime, Hide);
    NEW_NERVE(PopUpAddTimeAttackTimeNrvDisplay, PopUpAddTimeAttackTime, Display);
}  // namespace NrvPopUpAddTimeAttackTime

PopUpAddTimeAttackTime::PopUpAddTimeAttackTime(const char* pName, f32 arg2) : LayoutActor(pName, true), _2C(0.0f, 0.0f), _34(arg2) {
}

void PopUpAddTimeAttackTime::appear() {
    if (MR::isDemoActive()) {
        return;
    }

    LayoutActor::appear();
    setNerve(GET_NERVE(PopUpAddTimeAttackTime, PopUpAddTimeAttackTimeNrvDisplay));
    MR::setTextBoxNumberRecursive(this, "CollectCounter", 10);
}

void PopUpAddTimeAttackTime::init(const JMapInfoIter& rIter) {
    MR::connectToSceneLayout(this);
    initLayoutManager("CollectCounter", 1);
    initNerve(GET_NERVE(PopUpAddTimeAttackTime, PopUpAddTimeAttackTimeNrvHide));
    MR::setFollowPos(&_2C, this, nullptr);
    kill();
}

void PopUpAddTimeAttackTime::control() {
    calcPos();
}

void PopUpAddTimeAttackTime::show(const wchar_t* pName) {
    appear();
    MR::setTextBoxMessageRecursive(this, "CollectCounter", pName);
}

void PopUpAddTimeAttackTime::setTextBoxArgNumber(s32 number) {
    MR::setTextBoxArgNumberRecursive(this, "CollectCounter", number, 0);
}

bool PopUpAddTimeAttackTime::tryHide() {
    if (MR::isAnimStopped(this, 0) || MR::isDemoActive()) {
        setNerve(GET_NERVE(PopUpAddTimeAttackTime, PopUpAddTimeAttackTimeNrvHide));
        kill();
        return true;
    }

    return false;
}

void PopUpAddTimeAttackTime::calcPos() {
    f32 pointRadius2D = MR::calcPointRadius2D(*MR::getPlayerCenterPos(), 75.0f + _34);

    TVec2f PlayerCenterScreenPos;
    MR::calcScreenPosition(&PlayerCenterScreenPos, *MR::getPlayerCenterPos());
    PlayerCenterScreenPos.y -= pointRadius2D;
    _2C = PlayerCenterScreenPos;
}

void PopUpAddTimeAttackTime::exeHide() {
}

void PopUpAddTimeAttackTime::exeDisplay() {
    if (MR::isFirstStep(this)) {
        MR::startAnim(this, "Appear", 0);
    }

    tryHide();
}
