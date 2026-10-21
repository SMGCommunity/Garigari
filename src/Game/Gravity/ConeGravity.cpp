#include "Game/Gravity/ConeGravity.hpp"

ConeGravity::ConeGravity() : PlanetGravity(), mValidDegree(360.0f), mValidCos(-1.0f), mWorldRadius(), mEnableBottom(true), mTopCutRate() {
    mLocalMtx.identity();
    mWorldMtx.identity();
}

void ConeGravity::setLocalMatrix(const TPos3f& rMtx) {
    mLocalMtx.set(rMtx);
    updateIdentityMtx();
}

void ConeGravity::setEnableBottom(bool isEnable) {
    mEnableBottom = isEnable;
}

void ConeGravity::setTopCutRate(f32 rate) {
    mTopCutRate = rate < 0.0f ? 0.0f : rate > 1.0f ? 1.0f : rate;
}
