#include "LiveActor/ModelObj.hpp"
#include "Util/ActorInitUtil.hpp"

namespace MR {
    void connectToScene(LiveActor*, int, int, int, int);
    void setBaseTRMtx(LiveActor*, MtxPtr);
}

// Shared structure follows CC0 Petari; Galaxy 2 initialization order and
// initActor fallback behavior are reconstructed from the retail instructions.
ModelObj::ModelObj(const char* name, const char* modelName, MtxPtr matrix,
                   int drawBuffer, int movement, int calcAnim, bool flag)
    : LiveActor(name), mBaseMtx(matrix) {
    if (mBaseMtx) {
        mPosition.set<f32>(mBaseMtx[0][3], mBaseMtx[1][3], mBaseMtx[2][3]);
    }
    if (!MR::initActor(this, modelName, flag) && mModelManager) {
        if (drawBuffer < -1) drawBuffer = 9;
        if (movement < -1) movement = 0x22;
        if (calcAnim < -1) calcAnim = 0xB;
        MR::connectToScene(this, movement, calcAnim, drawBuffer, -1);
        initSound(4, nullptr, nullptr, TVec3f(0.0f));
        initEffectKeeper(8, nullptr, false);
    }
}

void ModelObj::init(const JMapInfoIter&) {
    makeActorAppeared();
}

void ModelObj::calcAndSetBaseMtx() {
    if (mBaseMtx) {
        mPosition.set<f32>(mBaseMtx[0][3], mBaseMtx[1][3], mBaseMtx[2][3]);
        MR::setBaseTRMtx(this, mBaseMtx);
    } else {
        LiveActor::calcAndSetBaseMtx();
    }
}

inline ModelObj::~ModelObj() {}
