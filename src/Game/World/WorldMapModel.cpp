#include "Game/World/WorldMapModel.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/NameObj/NameObjFactory.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include <cstdio>
#include <decomp.h>

EXTERN_UNKNOWN_FUNC_NO_ARGS(void, 804E8370);

WorldMapModel::WorldMapModel(const char* pName) : LiveActor(pName), mChildObjs() {
}

void WorldMapModel::init(const JMapInfoIter& rIter) {
    const char* name = "";
    MR::getObjectName(&name, rIter);

    char filePath[0x80];
    snprintf(filePath, sizeof(filePath), "/ObjectData/%s.arc", name);

    if (MR::isFileExist(filePath, true)) {
        if (!MR::initActor(this, rIter, name, false)) {
            MR::connectToSceneMapObj(this);
            initEffectKeeper(0, nullptr, false);
        }

        MR::tryStartAllAnim(this, name);
    } else {
        MR::connectToSceneMapObjMovement(this);
    }

    MR::invalidateClipping(this);
    MR::registerDemoSimpleCastAll(this);
    makeActorAppeared();

    s32 childObjNum = MR::getChildObjNum(rIter);
    if (childObjNum <= 0) {
        return;
    }

    mChildObjs.init(childObjNum);

    for (LiveActor** childObj = mChildObjs.begin(); childObj != mChildObjs.end(); childObj++) {
        const char* childObjName = nullptr;
        MR::getChildObjName(&childObjName, rIter, mChildObjs.index_of(childObj));
        *childObj = static_cast< LiveActor* >(NameObjFactory::initChildObj(rIter, mChildObjs.index_of(childObj)));
    }
}

void WorldMapModel::appearAll() {
    for (LiveActor** childObj = mChildObjs.begin(); childObj != mChildObjs.end(); childObj++) {
        (*childObj)->makeActorAppeared();
    }

    makeActorAppeared();
    MR::tryStartAllAnim(this, MR::getModelResName(this));
}

void WorldMapModel::killAll() {
    for (LiveActor** childObj = mChildObjs.begin(); childObj != mChildObjs.end(); childObj++) {
        (*childObj)->makeActorDead();

        if (MR::isExistEffectKeeper(*childObj)) {
            MR::forceDeleteEffectAll(*childObj);
        }
    }

    makeActorDead();
    if (MR::isExistEffectKeeper(this)) {
        MR::forceDeleteEffectAll(this);
    }
}

void WorldMapModel::initAfterPlacement() {
    fn_804E8370();
}
