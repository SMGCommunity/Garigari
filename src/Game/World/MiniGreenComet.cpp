#include "Game/World/MiniGreenComet.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC_NO_ARGS(bool, 804D8290);

MiniGreenComet::MiniGreenComet() : LiveActor("グリーンコメット（ワールドマップ）") {
}

void MiniGreenComet::init(const JMapInfoIter& rIter) {
    if (!MR::initActor(this, rIter, "MiniGreenComet", false)) {
        MR::connectToSceneWorldMapMiniObj(this);
        initEffectKeeper(8, nullptr, false);
    }

    MR::invalidateClipping(this);
    MR::registerDemoSimpleCastAll(this);

    if (fn_804D8290()) {
        initSound(4, nullptr);
    }

    makeActorDead();
}

void MiniGreenComet::appear() {
    // FIXME: put this (and other) constants in an anon namespace
    static char* sAppearActionName = "MiniGreenComet";
    MR::startAction(this, sAppearActionName);
    LiveActor::appear();
}

void MiniGreenComet::control() {
    if (MR::isActionEnd(this)) {
        kill();
    }
}

MiniGreenCometShower::MiniGreenCometShower() : LiveActor("降り注ぐグリーンコメット（ワールドマップ）") {
}

void MiniGreenCometShower::init(const JMapInfoIter& rIter) {
    MR::connectToSceneMapObjMovement(this);
    initEffectKeeper(8, "MiniGreenCometShower", false);

    if (fn_804D8290()) {
        initSound(4, "MiniGreenCometShower");
    }

    MR::invalidateClipping(this);
    MR::registerDemoSimpleCastAll(this);
    makeActorDead();
}

void MiniGreenCometShower::appear() {
    LiveActor::appear();
    MR::emitEffect(this, "Shower");
    MR::startActionSound(this, "Shower");
}
