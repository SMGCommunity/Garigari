#include "Game/MapObj/BigFan.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

namespace {
    static const f32 sBaseWindWidth = 400.0f;
};  // namespace

namespace NrvBigFan {
    NEW_NERVE(BigFanNrvStop, BigFan, Stop);
    NEW_NERVE(BigFanNrvStart, BigFan, Start);
    NEW_NERVE(BigFanNrvWait, BigFan, Wait);
}  // namespace NrvBigFan

BigFan::BigFan(const char* pName)
    : LiveActor(pName), mWindModel(), mClippingCenter(0.0f, 0.0f, 0.0f), mWindLength(4000.0f), mWindSpeed(100.0f), mIsTeresaGalaxy() {
    BigFanFunction::createBigFanHolder();
    BigFanFunction::registerBigFan(this);
}

void BigFan::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);

    const char* objName;
    MR::getObjectName(&objName, rIter);
    MR::initActor(this, rIter, objName, false);
    MR::connectToSceneNoSilhouettedMapObj(this);

    if (MR::isExistCollisionResource(this, objName)) {
        initHitSensor(1);
        MR::addBodyMessageSensorReceiver(this);
        MR::initCollisionParts(this, objName, getSensor(nullptr), nullptr);
    }

    MR::getJMapInfoArg0NoInit(rIter, &mWindLength);
    MR::getJMapInfoArg1NoInit(rIter, &mWindSpeed);

    initWindModel();

    TVec3f frontVec;
    MR::calcFrontVec(&frontVec, this);
    mClippingCenter.scaleAdd(0.5f * mWindLength, frontVec, mPosition);
    MR::setClippingTypeSphere(this, 400.0f + mWindLength, &mClippingCenter);

    initSound(4, "BigFan");

    if (MR::isEqualStageName("TeresaMario2DGalaxy")) {
        mIsTeresaGalaxy = true;
    } else {
        mIsTeresaGalaxy = false;
    }

    initNerve(GET_NERVE(BigFan, BigFanNrvWait));

    if (MR::initUseStageSwitchReadAppear(this, rIter)) {
        MR::listenStageSwitchOnAppear(this, MR::Functor(this, &BigFan::start));
        setNerve(GET_NERVE(BigFan, BigFanNrvStop));
        mWindModel->kill();
    }

    MR::registerDemoSimpleCastAll(this);
    makeActorAppeared();
}

void BigFan::initWindModel() {
    mWindModel = MR::createModelObjMapObj("風モデル", "BigFanWind", getBaseMtx());
    mWindModel->initWithoutIter();
    MR::invalidateClipping(mWindModel);
    MR::startBtk(mWindModel, "BigFanWind");
    MR::registerDemoSimpleCastAll(mWindModel);
    mWindModel->mScale.z = mWindLength / 2000.0f;
}

void BigFan::calcWindInfo(TVec3f* pWindInfo, const TVec3f& rPos) {
    if (MR::isDead(this) || !isStartOrWait()) {
        pWindInfo->zero();
        return;
    }

    if (mWindLength <= 0.0f) {
        pWindInfo->zero();
        return;
    }

    TVec3f front;
    MR::calcFrontVec(&front, this);
    MR::normalize(&front);
    TVec3f diff = rPos - mPosition;
    f32 dot = front.dot(diff);

    if (dot < 0.0f) {
        pWindInfo->zero();
        return;
    }

    TVec3f ortho;
    ortho = diff - front * dot;
    if (ortho.length() >= ::sBaseWindWidth * mScale.x) {
        pWindInfo->zero();
        return;
    }

    f32 scalar = 1.0f - (dot / mWindLength);
    if (scalar < 0.0f) {
        pWindInfo->zero();
        return;
    }

    pWindInfo->set(front * scalar);
}

void BigFan::control() {
}

void BigFan::start() {
    if (isNerve(GET_NERVE(BigFan, BigFanNrvStop))) {
        setNerve(GET_NERVE(BigFan, BigFanNrvStart));
    }
}

void BigFan::exeStart() {
    if (MR::isFirstStep(this)) {
        mWindModel->appear();

        MR::startAction(this, "Appear");
        MR::startAction(mWindModel, "Appear");

        if (mIsTeresaGalaxy) {
            MR::startActionSound(this, "OjBigFanStartFar");
        } else {
            MR::startActionSound(this, "OjBigFanStart");
        }
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BigFan, BigFanNrvWait));
    }
}

void BigFan::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::startAction(mWindModel, "Wait");
    }

    if (mIsTeresaGalaxy) {
        MR::startActionSound(this, "OjLvBigFanFar");
    } else {
        MR::startActionSound(this, "OjLvBigFan");
    }
}

void BigFan::exeStop() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Appear");
        MR::stopBck(this);
    }
}

inline bool BigFan::isStartOrWait() {
    bool flag = false;
    if (isNerve(GET_NERVE(BigFan, BigFanNrvStart)) || isNerve(GET_NERVE(BigFan, BigFanNrvWait))) {
        flag = true;
    }

    return flag;
}
