#include "Game/MapObj/CoinRotater.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

CoinRotater::CoinRotater(const char* pName) : NameObj(pName), _14(0.0f, 0.0f, 0.0f) {
    mRotateYMtx.identity();
    mHiSpeedRotateYMtx.identity();
    mInWaterRotateYMtx.identity();
    MR::connectToSceneMapObjMovement(this);
}

void CoinRotater::movement() {
    _14.x += 8.0f;
    _14.x = MR::repeat(_14.x, 0.0f, 360.0f);

    _14.y += 4.0f;
    _14.y = MR::repeat(_14.y, 0.0f, 360.0f);

    _14.z += 16.0f;
    _14.z = MR::repeat(_14.z, 0.0f, 360.0f);

    MR::makeMtxRotateY(mRotateYMtx, _14.x);
    MR::makeMtxRotateY(mHiSpeedRotateYMtx, _14.z);
    MR::makeMtxRotateY(mInWaterRotateYMtx, _14.y);
}

CoinRotater* MR::createCoinRotater() {
    return static_cast< CoinRotater* >(MR::createSceneObj(SceneObj_CoinRotater));
}

TMtx34f& MR::getCoinRotateYMatrix() {
    return MR::getSceneObj< CoinRotater >(SceneObj_CoinRotater)->mRotateYMtx;
}

TMtx34f& MR::getCoinHiSpeedRotateYMatrix() {
    return MR::getSceneObj< CoinRotater >(SceneObj_CoinRotater)->mHiSpeedRotateYMtx;
}

TMtx34f& MR::getCoinInWaterRotateYMatrix() {
    return MR::getSceneObj< CoinRotater >(SceneObj_CoinRotater)->mInWaterRotateYMtx;
}
