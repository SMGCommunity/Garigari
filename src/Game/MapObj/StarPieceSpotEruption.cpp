#include "Game/MapObj/StarPieceSpotEruption.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "revolution/wpad.h"

namespace NrvStarPieceSpotEruption {
    NEW_NERVE(StarPieceSpotEruptionNrvRest, StarPieceSpotEruption, Rest);
    NEW_NERVE(StarPieceSpotEruptionNrvEruption, StarPieceSpotEruption, Eruption);
};  // namespace NrvStarPieceSpotEruption

void StarPieceSpotEruption_FORCE_MATCH_SDATA2() {
    (void)0.0f;
    (void)30.0f;
    (void)150.0f;
    (void)3000.0f;
}

StarPieceSpotEruption::StarPieceSpotEruption(const char* pName) : LiveActor(pName), mEruptVelocity(150.0f), mEruptRange(30.0f) {
}

void StarPieceSpotEruption::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);

    s32 numStarPiece = 20;
    MR::getJMapInfoArg0NoInit(rIter, &numStarPiece);
    MR::getJMapInfoArg1NoInit(rIter, &mEruptVelocity);
    MR::getJMapInfoArg2NoInit(rIter, &mEruptRange);

    MR::declareStarPiece(this, numStarPiece);

    initSound(3, "StarPieceSpotEruption");
    initEffectKeeper(2, "StarPieceSpotEruption", false);

    MR::connectToSceneMapObjMovement(this);

    MR::initUseStageSwitchReadA(this, rIter);

    MR::setClippingTypeSphere(this, 3000.0f);
    MR::setClippingFarMax(this);

    initNerve(GET_NERVE(StarPieceSpotEruption, StarPieceSpotEruptionNrvRest));

    makeActorAppeared();
}

void StarPieceSpotEruption::exeEruption() {
    if (MR::isFirstStep(this)) {
        emit();
    }
}

void StarPieceSpotEruption::exeRest() {
    if (MR::isFirstStep(this)) {
        MR::emitEffect(this, "Rest");
    }

    if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(StarPieceSpotEruption, StarPieceSpotEruptionNrvEruption));
    }
}

void StarPieceSpotEruption::emit() {
    MR::shakeCameraStrong();
    MR::tryRumblePadStrong(this, WPAD_CHAN0);

    s32 numStarPiece = MR::getDeclareRemnantStarPieceCount(this);
    MR::appearStarPiece(this, mPosition, numStarPiece, mEruptRange, mEruptVelocity, false);

    MR::deleteEffect(this, "Rest");
    MR::emitEffect(this, "Eruption");

    MR::startActionSound(this, "Eruption");
}
