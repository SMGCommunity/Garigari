#include "LiveActor/LiveActorFlag.hpp"

LiveActorFlag::LiveActorFlag() {
    mIsDead = true;
    mIsNotReleasedAnimFrame = false;
    mIsOnCalcAnim = false;
    mIsNoCalcView = false;
    mIsNoEntryDrawBuffer = false;
    mIsOnBind = true;
    mIsCalcGravity = false;
    mIsClipped = false;
    mIsClippingInvalid = false;
}
