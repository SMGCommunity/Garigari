#include "Game/World/MiniStarWorldPoint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Screen/LayoutActor.hpp"
#include "Game/System/GalaxyStatusAccessor.hpp"
#include "Game/System/ScenarioDataParser.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include <cstdio>
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(bool, 804F26A0, WorldMapObjHolder*, s32)

MiniStarWorldPoint::MiniStarWorldPoint(WorldMapObjHolder* pObjHolder, s32 pointIndex, s32 worldNo)
    : LiveActor("グランドギャラクシーマップ用ワープポイント"), mObjHolder(pObjHolder), mPointIndex(pointIndex), mWorldNo(worldNo), _9C() {
}

void MiniStarWorldPoint::init(const JMapInfoIter& rIter) {
    char fileName[0x80];
    snprintf(fileName, sizeof(fileName), "MiniWorld%02d", mWorldNo);

    if (!MR::initActor(this, fileName, false) && mModelManager != nullptr) {
        MR::connectToSceneMapObjDecoration(this);
        initEffectKeeper(8, nullptr, false);
    }

    fn_804E6820();
    MR::setClippingTypeSphereContainsModelBoundingBox(this, 1000.0f);
    MR::registerDemoSimpleCastAll(this);
    makeActorAppeared();
}

void MiniStarWorldPoint::fn_804E6820() {
    // TODO: create '_9C' layout
    MR::registerDemoSimpleCastAll(_9C);
    MR::hidePaneRecursive(_9C, "MapGalaxyState");
    MR::showPane(_9C, "MapGalaxyState");

    bool isCompletedWithGreen = true;
    bool isCompletedNoGreen = true;

    for (ScenarioDataIter iter = MR::makeBeginScenarioDataIter(); !iter.isEnd(); iter.goNext()) {
        GalaxyStatusAccessor accessor = iter.makeAccessor();
        if (accessor.getWorldNo() != mWorldNo) {
            continue;
        }

        if (!accessor.isCompletedWithGreen()) {
            isCompletedWithGreen = false;
        }

        if (!accessor.isCompletedNoGreen()) {
            isCompletedNoGreen = false;
        }

        if (isCompletedWithGreen) {
            continue;
        }

        if (!isCompletedNoGreen) {
            break;
        }
    }

    if (isCompletedNoGreen) {
        MR::showPaneRecursive(_9C, "Crown2");
    }
    else if (isCompletedWithGreen) {
        MR::showPaneRecursive(_9C, "Crown1");
    }

    if (isCompletedNoGreen || isCompletedWithGreen) {
        _9C->appear();
    }
    else {
        _9C->kill();
    }
}

void MiniStarWorldPoint::makeActorAppeared() {
    if (fn_804F26A0(mObjHolder, mPointIndex)) {
        LiveActor::makeActorAppeared();
    }
}

void MiniStarWorldPoint::control() {
    mRotation.y += 0.1f;
    mRotation.y = MR::repeatDegree(mRotation.y);
}
