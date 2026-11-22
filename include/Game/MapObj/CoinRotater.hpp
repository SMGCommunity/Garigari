#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>
#include <JSystem/JGeometry/TVec.hpp>


class CoinRotater : public NameObj {
public:
    /// @brief Creates a new `CoinRotater` instance.
    /// @param pName A pointer to the null-terminated name of the object.
    CoinRotater(const char* pName);

    virtual void movement();

    /* 0x14 */ TVec3f _14;
    /* 0x20 */ TMtx34f mRotateYMtx;
    /* 0x50 */ TMtx34f mHiSpeedRotateYMtx;
    /* 0x80 */ TMtx34f mInWaterRotateYMtx;
};

namespace MR {
    CoinRotater* createCoinRotater();
    TMtx34f& getCoinRotateYMatrix();
    TMtx34f& getCoinHiSpeedRotateYMatrix();
    TMtx34f& getCoinInWaterRotateYMatrix();
};  // namespace MR
