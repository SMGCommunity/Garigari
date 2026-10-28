#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class CoinRotater : public NameObj {

};

namespace MR {
    void createCoinRotater();
    TMtx34f& getCoinInWaterRotateYMatrix();
};
