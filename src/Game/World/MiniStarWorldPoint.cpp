#include "Game/World/MiniStarWorldPoint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Screen/ActorLayout.hpp"
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
    : LiveActor("グランドギャラクシーマップ用ワープポイント"), mObjHolder(pObjHolder), mPointIndex(pointIndex), mWorldNo(worldNo), mStateLayout() {
}

void MiniStarWorldPoint::init(const JMapInfoIter& rIter) {
    char fileName[0x80];
    snprintf(fileName, sizeof(fileName), "MiniWorld%02d", mWorldNo);

    if (!MR::initActor(this, fileName, false) && mModelManager != nullptr) {
        MR::connectToSceneMapObjDecoration(this);
        initEffectKeeper(8, nullptr, false);
    }

    initStateLayout();
    MR::setClippingTypeSphereContainsModelBoundingBox(this, 1000.0f);
    MR::registerDemoSimpleCastAll(this);
    makeActorAppeared();
}

void MiniStarWorldPoint::initStateLayout() {
    mStateLayout = new ActorLayout(this, "コンプリートアイコン", "MapGalaxyState", TVec3f(0.0f), 1, -1);
    MR::registerDemoSimpleCastAll(mStateLayout);
    MR::hidePaneRecursive(mStateLayout, "MapGalaxyState");
    MR::showPane(mStateLayout, "MapGalaxyState");

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
        MR::showPaneRecursive(mStateLayout, "Crown2");
    }
    else if (isCompletedWithGreen) {
        MR::showPaneRecursive(mStateLayout, "Crown1");
    }

    if (isCompletedWithGreen || isCompletedNoGreen) {
        mStateLayout->appear();
    }
    else {
        mStateLayout->kill();
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
