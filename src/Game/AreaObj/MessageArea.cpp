#include "Game/AreaObj/MessageArea.hpp"
#include "Game/Util/SceneUtil.hpp"

MessageArea::MessageArea(const char* pName) : AreaObj(pName), mZoneID(-1) {
}

void MessageArea::init(const JMapInfoIter& rIter) {
    AreaObj::init(rIter);

    mZoneID = MR::getPlacedZoneId(rIter);
}
