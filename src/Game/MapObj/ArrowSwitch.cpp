#include "Game/MapObj/ArrowSwitch.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/AreaObjUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

namespace {
    static const s32 sFreqRotY = 4;
    static const f32 sPunchVelocity = 6.0f;
    static const f32 sRotYTargetList[] = {0.0f, 90.0f, 180.0f, -90.0f};
}  // namespace

namespace NrvArrowSwitch {
    NEW_NERVE(ArrowSwitchNrvWait, ArrowSwitch, Wait);
    NEW_NERVE(ArrowSwitchNrvRotate, ArrowSwitch, Rotate);
    NEW_NERVE(ArrowSwitchNrvLock, ArrowSwitch, Lock);
    NEW_NERVE(ArrowSwitchNrvStop, ArrowSwitch, Stop);
};  // namespace NrvArrowSwitch

ArrowSwitch::ArrowSwitch(const char* pName)
    : LiveActor(pName), mRotAngle(), mRotYTargetIndex(), mRotSpeed(), mSwitchType(-1), mActionAfterRotate(-1), mIsRotPlus(true), _A5(), mIsPunch() {
}

void ArrowSwitch::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::initActor(this, rIter, "ArrowSwitch", false);
    MR::connectToSceneNoSilhouettedMapObjStrongLight(this);

    TVec3f upVec;
    MR::calcUpVec(&upVec, this);
    mGravity.set(-upVec);

    MR::initShadowFromCSVWithInitShadowVolumeSphere(this, "Shadow");
    MR::onCalcShadow(this, nullptr);
    MR::onCalcGravity(this);

    if (MR::isInPlaneModeCube(mPosition)) {
        initHitSensor(1);
        MR::addHitSensorMapObj(this, "Body", 8, 100.0f * mScale.x, TVec3f(0.0f, 50.0f * mScale.x, 250.0f * mScale.x));
    } else {
        initHitSensor(2);
        MR::addHitSensorMapObj(this, "Body", 8, 100.0f * mScale.x, TVec3f(0.0f, 50.0f * mScale.x, 250.0f * mScale.x));

        MR::addHitSensorMapObjMoveCollision(this, "collision", 8, 0.0f, TVec3f(0.0f, 0.0f, 0.0f));

        MR::initCollisionParts(this, "ArrowSwitch", getSensor("collision"), nullptr);
    }

    initSound(4, "ArrowSwitch");
    initNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvWait));

    MR::getJMapInfoArg0WithInit(rIter, &mSwitchType);
    MR::getJMapInfoArg1WithInit(rIter, &mActionAfterRotate);

    s32 shadowDropLength = -1;
    MR::getJMapInfoArg2WithInit(rIter, &shadowDropLength);

    if (shadowDropLength >= 0) {
        MR::setShadowDropLength(this, nullptr, shadowDropLength);
    }

    MR::needStageSwitchWriteA(this, rIter);

    if (mActionAfterRotate == -1) {
        MR::listenStageSwitchOnOffA(this, MR::Functor(this, &ArrowSwitch::listenOnSwitch), MR::Functor(this, &ArrowSwitch::listenOffSwitch));
    }

    MR::useStageSwitchSyncAppear(this, rIter);
}

void ArrowSwitch::control() {
}

void ArrowSwitch::calcAndSetBaseMtx() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/QQkLH
    // Something is wrong with the inlined function TPos3f::setEulerY. It sets the right members of the matrix to the right values, but it does it in
    // the wrong order for whatever reason.
    LiveActor::calcAndSetBaseMtx();
    TPos3f pos;
    pos.set(getBaseMtx());
    TPos3f rot;
    rot.identity();
    rot.setEulerY(MR::toRadian(mRotAngle));
    pos.concat(pos, rot);
    MR::setBaseTRMtx(this, pos);
}

void ArrowSwitch::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!MR::isSensorPlayer(pReceiver) && !MR::isSensorYoshi(pReceiver)) {
        return;
    }

    MR::sendMsgPush(pReceiver, pSender);
}

bool ArrowSwitch::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgPlayerSpinAttack(msg)) {
        return requestPunch(pSender, pReceiver);
    } else {
        return false;
    }
}

bool ArrowSwitch::receiveMsgPush(HitSensor* pSender, HitSensor* pReceiver) {
    return false;
}

bool ArrowSwitch::requestPunch(HitSensor* pSender, HitSensor* pReceiver) {
    if (getSensor("Body") != pReceiver) {
        return false;
    }

    if (!isNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvWait))) {
        return false;
    }

    TVec3f sideVec;
    MR::calcSideVec(&sideVec, this);
    TVec3f sensorDir;
    MR::calcSensorDirection(&sensorDir, pSender, pReceiver);

    if (isPlusLimit()) {
        mIsRotPlus = false;
    } else if (isMinusLimit()) {
        mIsRotPlus = true;
    } else if (sideVec.dot(sensorDir) > 0.0f) {
        mIsRotPlus = true;
    } else {
        mIsRotPlus = false;
    }

    mRotYTargetIndex += mIsRotPlus ? getOneStep() : -getOneStep();
    mRotYTargetIndex = (mRotYTargetIndex + ::sFreqRotY) % ::sFreqRotY;
    mRotSpeed = mIsRotPlus ? ::sPunchVelocity : -::sPunchVelocity;
    mIsPunch = true;

    MR::invalidateClipping(this);
    setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvRotate));

    return true;
}

void ArrowSwitch::listenOnSwitch() {
    if (mRotYTargetIndex != Direction_Up) {
        return;
    }

    switch (mSwitchType) {
    case -1:
    case SwitchType_HalfPlus:
        mIsRotPlus = 1;
        mRotSpeed = ::sPunchVelocity;
        mRotYTargetIndex = Direction_Down;
        break;
    case SwitchType_HalfMinus:
        mIsRotPlus = false;
        mRotSpeed = -::sPunchVelocity;
        mRotYTargetIndex = Direction_Down;
        break;
    case SwitchType_QuarterPlus:
        mIsRotPlus = true;
        mRotSpeed = ::sPunchVelocity;
        mRotYTargetIndex = Direction_Right;
        break;
    case SwitchType_QuarterMinus:
        mIsRotPlus = false;
        mRotSpeed = -::sPunchVelocity;
        mRotYTargetIndex = Direction_Left;
        break;
    default:
        return;
    }

    MR::invalidateClipping(this);
    setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvRotate));
}

void ArrowSwitch::listenOffSwitch() {
    if (mRotYTargetIndex == Direction_Up) {
        return;
    }

    mRotYTargetIndex = Direction_Up;

    u32 nextSwitchType = mSwitchType + 1;
    if (nextSwitchType <= 1 || mSwitchType == 2) {
        mIsRotPlus = false;
        mRotSpeed = -::sPunchVelocity;
    } else {
        switch (mSwitchType) {
        case SwitchType_HalfPlus:
            mIsRotPlus = false;
            mRotSpeed = -::sPunchVelocity;
            break;
        case SwitchType_HalfMinus:
        case SwitchType_QuarterMinus:
            mIsRotPlus = true;
            mRotSpeed = ::sPunchVelocity;
            break;
        default:
            return;
        }
    }

    MR::invalidateClipping(this);
    setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvRotate));
}

void ArrowSwitch::exeWait() {
    if (!MR::isFirstStep(this)) {
        return;
    }

    if (mRotYTargetIndex == Direction_Up) {
        MR::startBtk(this, "Off");
    } else {
        MR::startBtk(this, "On");
    }

    MR::validateClipping(this);
    MR::onCalcShadow(this, nullptr);
}

void ArrowSwitch::exeRotate() {
    if (MR::isFirstStep(this)) {
        MR::startActionSound(this, "OjArrowSwitchOn");
        MR::onCalcShadow(this, nullptr);
    }

    MR::startActionSound(this, "OjLvArrowSwitchMove");

    mRotAngle += mRotSpeed;
    mRotAngle = MR::repeat(mRotAngle, -180.0f, 360.0f);
    f32 diff = MR::repeat(::sRotYTargetList[mRotYTargetIndex] - mRotAngle, -180.0f, 360.0f);

    if ((mIsRotPlus && diff < 0.0f) || (!mIsRotPlus && diff > 0.0f)) {
        mRotSpeed = 0.0f;
        mRotAngle = ::sRotYTargetList[mRotYTargetIndex];

        if (MR::isValidSwitchA(this) && mIsPunch) {
            if (mRotYTargetIndex != 0) {
                MR::onSwitchA(this);
            } else {
                MR::offSwitchA(this);
            }
        }

        MR::startActionSound(this, "OjArrowSwitchStop");
        mIsPunch = false;

        if (mActionAfterRotate == ActionAfterRotate_LockAfterRotate) {
            setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvLock));
        } else if (mActionAfterRotate == ActionAfterRotate_StopAfterRotate) {
            setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvStop));
            kill();
        } else {
            setNerve(GET_NERVE(ArrowSwitch, ArrowSwitchNrvWait));
        }
    }
}

void ArrowSwitch::exeLock() {
    if (MR::isFirstStep(this)) {
        if (mRotYTargetIndex == Direction_Up) {
            MR::startBtk(this, "Off");
        } else {
            MR::startBtk(this, "On");
        }

        MR::validateClipping(this);
        MR::onCalcShadow(this, nullptr);
    }
}

bool ArrowSwitch::isPlusLimit() const {
    switch (mSwitchType) {
    case SwitchType_HalfPlus:
        return mRotYTargetIndex == Direction_Down;
    case SwitchType_QuarterPlus:
        return mRotYTargetIndex == Direction_Right;
    case SwitchType_QuarterMinus:
        return mRotYTargetIndex == Direction_Up;
    case SwitchType_HalfMinus:
        return mRotYTargetIndex == Direction_Up;
    default:
        return false;
    }
}

bool ArrowSwitch::isMinusLimit() const {
    switch (mSwitchType) {
    case SwitchType_HalfPlus:
        return mRotYTargetIndex == Direction_Up;
    case SwitchType_QuarterPlus:
        return mRotYTargetIndex == Direction_Up;
    case SwitchType_QuarterMinus:
        return mRotYTargetIndex == Direction_Left;
    case SwitchType_HalfMinus:
        return mRotYTargetIndex == Direction_Down;
    default:
        return false;
    }
}

s32 ArrowSwitch::getOneStep() const {
    switch (mSwitchType) {
    case -1:
    case SwitchType_HalfPlus:
    case SwitchType_HalfMinus:
        return 2;
    case SwitchType_QuarterPlus:
    case SwitchType_QuarterMinus:
        return 1;
    default:
        return 0;
    }
}

void ArrowSwitch::exeStop() {
}
