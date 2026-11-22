#include "Game/MapObj/ExterminationWoodBoxFlagHolder.hpp"
#include "Game/Scene/SceneObjHolder.hpp"

ExterminationWoodBoxFlagHolder::ExterminationWoodBoxFlagHolder(const char* pName) : NameObj(pName), mFlag() {
}

void ExterminationWoodBoxFlagHolder::init(const JMapInfoIter& rIter) {
}

void MR::setExterminationWoodBoxFlag() {
    ExterminationWoodBoxFlagHolder* flagHolder =
        static_cast< ExterminationWoodBoxFlagHolder* >(MR::getSceneObjHolder()->getObj(SceneObj_WoodBoxExterminationFlagHolder));
    flagHolder->mFlag = true;
}

void MR::clearExterminationWoodBoxFlag() {
    ExterminationWoodBoxFlagHolder* flagHolder =
        static_cast< ExterminationWoodBoxFlagHolder* >(MR::getSceneObjHolder()->getObj(SceneObj_WoodBoxExterminationFlagHolder));
    flagHolder->mFlag = false;
}

bool MR::getExterminationWoodBoxFlagHolder() {
    return static_cast< ExterminationWoodBoxFlagHolder* >(MR::getSceneObjHolder()->getObj(SceneObj_WoodBoxExterminationFlagHolder))->mFlag;
}
