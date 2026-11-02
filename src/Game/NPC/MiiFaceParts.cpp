#include "Game/NPC/MiiFaceParts.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/Util/FixedPosition.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include <JSystem/J3DGraphBase/J3DSys.hpp>

MiiFaceParts::MiiFaceParts(const char* pName, const MiiFaceRecipe& rRecipe)
    : LiveActor(pName), mCharModel(), mBuffer(), mRecipe(), mFixedPosition(), _D4() {
    mRecipe = new MiiFaceRecipe(rRecipe);

    MR::createSceneObj(SceneObj_MiiFacePartsHolder);
}

MiiFaceParts::~MiiFaceParts() {
}

void MiiFaceParts::init(const JMapInfoIter& rIter) {
    mBuffer = new (32) u8[mRecipe->getModelBufferSize()];
    mCharModel = new RFLCharModel;
    _D5 = 1;
}

void MiiFaceParts::calcAnim() {
    if (mFixedPosition != nullptr) {
        mFixedPosition->calc();
        MR::setPosition(this, _CC[0][3], _CC[1][3], _CC[2][3]);
        PSMTXCopy(_CC, _9C);
    } else {
        MR::makeMtxTR(_9C, mPosition, mRotation);
    }

    MR::preScaleMtx(_9C, mScale);
}

void MiiFaceParts::calcViewAndEntry() {
    Mtx viewMtx;

    if (_D5) {
        return;
    }

    PSMTXConcat(j3dSys.mViewMtx, _9C, viewMtx);
    RFLSetMtx(mCharModel, viewMtx);
}

void MiiFaceParts::drawOpa(const RFLDrawCoreSetting* pSetting) const {
    if (_D5) {
        return;
    }

    if (pSetting != nullptr) {
        RFLDrawOpaCore(mCharModel, pSetting);
    } else {
        RFLDrawOpa(mCharModel);
    }
}

void MiiFaceParts::drawXlu(const RFLDrawCoreSetting* pSetting) const {
    if (_D5) {
        return;
    }

    if (pSetting != nullptr) {
        RFLDrawXluCore(mCharModel, pSetting);
    } else {
        RFLDrawXlu(mCharModel);
    }
}

void MiiFaceParts::initFixedPosition(MtxPtr pMtx, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    mFixedPosition = new FixedPosition(pMtx, rLocalTrans, rLocalRotate);
    _CC = mFixedPosition->mMtx;
}

bool MiiFaceParts::changeExpressionNormal() {
    return tryChangeExpression(RFLExp_Normal);
}

bool MiiFaceParts::changeExpressionBlink() {
    return tryChangeExpression(RFLExp_Blink);
}

void MiiFaceParts::changeFaceModel(const MiiFaceRecipe& rRecipe) {
    mRecipe->mIndex = rRecipe.mIndex;
    mRecipe->mDataSource = rRecipe.mDataSource;

    if (rRecipe.mDataSource == RFLDataSource_Middle) {
        mRecipe->setDatabase(rRecipe.mDatabase);
    }

    _D4 = true;
}

void MiiFaceParts::initFaceModel() {
    mRecipe->initFaceModel(mCharModel, mBuffer);
    _D4 = false;
    _D5 = false;
}

bool MiiFaceParts::tryChangeExpression(u32 expression) {
    if (_D5) {
        return false;
    }

    if (!mRecipe->hasExpression(static_cast< RFLExpression >(expression))) {
        return false;
    }

    RFLSetExpression(mCharModel, static_cast< RFLExpression >(expression));

    return true;
}
