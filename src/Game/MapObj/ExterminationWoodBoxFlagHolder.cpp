#include "Game/MapObj/ExterminationWoodBoxFlagHolder.hpp"
#include "Game/Scene/SceneObjHolder.hpp"

ExterminationWoodBoxFlagHolder::ExterminationWoodBoxFlagHolder(const char* pName) : NameObj(pName), mFlag() {
}

void ExterminationWoodBoxFlagHolder::init(const JMapInfoIter& rIter) {
}

void MR::setExterminationWoodBoxFlag() {
    getSceneObj< ExterminationWoodBoxFlagHolder >(SceneObj_WoodBoxExterminationFlagHolder)->mFlag = true;
}

void MR::clearExterminationWoodBoxFlag() {
    getSceneObj< ExterminationWoodBoxFlagHolder >(SceneObj_WoodBoxExterminationFlagHolder)->mFlag = false;
}

bool MR::getExterminationWoodBoxFlagHolder() {
    return getSceneObj< ExterminationWoodBoxFlagHolder >(SceneObj_WoodBoxExterminationFlagHolder)->mFlag;
}
