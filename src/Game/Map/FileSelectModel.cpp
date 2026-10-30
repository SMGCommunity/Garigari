#include "Game/Map/FileSelectModel.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

namespace NrvFileSelectModel {
    NEW_NERVE(FileSelectModelNrvOpen, FileSelectModel, Open);
    NEW_NERVE(FileSelectModelNrvBlinkOnce, FileSelectModel, BlinkOnce);
    NEW_NERVE(FileSelectModelNrvClose, FileSelectModel, Close);
    NEW_NERVE(FileSelectModelNrvBlink, FileSelectModel, Blink);
};  // namespace NrvFileSelectModel

FileSelectModel::FileSelectModel(const char* pObjName, MtxPtr pMtx, const char* pName) : LiveActor(pName), _90(pMtx) {
    MR::initActor(this, pObjName, false);
    MR::connectToSceneNpc(this);
    initEffectKeeper(0, nullptr, false);
    MR::initLightCtrl(this);
    mScale.set(30.0f, 30.0f, 30.0f);
    initNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen));
    MR::invalidateClipping(this);
    makeActorDead();
}

void FileSelectModel::calcAnim() {
    LiveActor::calcAnim();
}

void FileSelectModel::calcAndSetBaseMtx() {
    mPosition.setTrans(_90);
    MR::setBaseTRMtx(this, _90);
}

void FileSelectModel::open() {
    if (!isNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen))) {
        setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen));
    }
}

void FileSelectModel::blinkOnce() {
    setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvBlinkOnce));
}

void FileSelectModel::close() {
    setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvClose));
}

void FileSelectModel::blink() {
    setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvBlink));
}

bool FileSelectModel::isOpen() const {
    return isNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen));
}

void FileSelectModel::emitOpen() {
    MR::emitEffect(this, "Open");
}

void FileSelectModel::emitVanish() {
    MR::emitEffect(this, "Vanish");
}

void FileSelectModel::emitCopy() {
    MR::emitEffect(this, "Copy");
}

void FileSelectModel::emitCompleteEffect() {
    MR::emitEffect(this, "Complete");
}

void FileSelectModel::deleteCompleteEffect() {
    MR::deleteEffect(this, "Complete");
}

void FileSelectModel::exeOpen() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "normal");
    }
}

void FileSelectModel::exeBlinkOnce() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "blink");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen));
    }
}

void FileSelectModel::exeBlink() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "open");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(FileSelectModel, FileSelectModelNrvOpen));
    }
}

void FileSelectModel::exeClose() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "close");
    }
}
