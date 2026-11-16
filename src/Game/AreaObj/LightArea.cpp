#include "Game/AreaObj/LightArea.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

LightArea::LightArea(const char* pName) : AreaObj(pName), _48() {
}

void LightArea::init(const JMapInfoIter& rIter) {
    AreaObj::init(rIter);
    s32 objID = 0;

    if (MR::getLinkObjID(rIter, &objID)) {
        if (objID != -1) {
            _48 = true;
        }
    } else if (MR::getMapPartsID(rIter, &objID)) {
        if (objID != -1) {
            _48 = true;
        }
    }
}
