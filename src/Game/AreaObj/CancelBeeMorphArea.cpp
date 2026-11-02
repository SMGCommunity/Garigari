#include "Game/AreaObj/CancelBeeMorphArea.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"

CancelBeeMorphArea::CancelBeeMorphArea(const char* pName) : AreaObj(pName) {

}

void CancelBeeMorphArea::init(const JMapInfoIter& rIter) {
    AreaObj::init(rIter);
    MR::connectToSceneAreaObj(this);
}

void CancelBeeMorphArea::movement() {
    if (!MR::isPlayerElementModeBee()) {
        return;
    }

    TVec3f up(0.0f);
    MR::getPlayerUpVec(&up);
    
    TVec3f pos = *MR::getPlayerPos() + up * 150.0f;
    
    if (isInVolume(*MR::getPlayerPos()) || isInVolume(pos)) {
        MR::getPlayerPos(); // Useless...
        MR::curePlayerElementMode();
    }
}