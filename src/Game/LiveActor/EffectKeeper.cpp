#include "Game/LiveActor/EffectKeeper.hpp"

#include "Game/Effect/MultiEmitter.hpp"
#include "Game/System/ResourceHolder.hpp"

EffectKeeper::EffectKeeper(const char* pStr1, ResourceHolder* pResourceHolder, int num, const char* pStr2)
    : _0(pStr1), _4(pStr2), mResourceHolder(pResourceHolder), _C(0), mSize_C(0), _14(0), _18(0), _1C(0), _20(0), _24(0), _28(0), _2C(0), _30(false) {
    if (pStr2 == nullptr && pResourceHolder != nullptr) {
        _4 = pResourceHolder->_50;
    }

    int size = num + MR::Effect::getAutoEffectNum(_4);
    _C = new u32[size];
    mSize_C = size;
}
