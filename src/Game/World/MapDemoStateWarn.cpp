#include "Game/World/MapDemoStateWarn.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/System/GameDataFunction.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/NerveUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "Game/Util/TalkUtil.hpp"
#include "Game/World/GrandGalaxyMap.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(s32, 804D3F80, void)
EXTERN_UNKNOWN_FUNC(void, 804D75B0, void)
EXTERN_UNKNOWN_FUNC(bool, 804D75E0, void)
EXTERN_UNKNOWN_FUNC(void, 804DFE90, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804DFEA0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(LiveActor*, 804E15A0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E15B0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E15C0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E15D0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(bool, 804E15E0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(bool, 804E15F0, GrandGalaxyMap*)

namespace NrvMapDemoStateWarn {
    NEW_NERVE(MapDemoStateWarnNrv1, MapDemoStateWarn, Nerve1);  // TODO: better name
    NEW_NERVE(MapDemoStateWarnNrv2, MapDemoStateWarn, Nerve2);  // TODO: better name
    NEW_NERVE(MapDemoStateWarnNrv3, MapDemoStateWarn, Nerve3);  // TODO: better name
    NEW_NERVE(MapDemoStateWarnNrv4, MapDemoStateWarn, Nerve4);  // TODO: better name
};  // namespace NrvMapDemoStateWarn

MapDemoStateWarn::MapDemoStateWarn(GrandGalaxyMap* pHost)
    : ActorStateBase< GrandGalaxyMap >("State[グランドギャラクシーニュース]", pHost), mWorldId(-1), mTalkMessageCtrlArray() {
}

namespace {
    const char* sGrandGalaxyMapMessages[] = {
        "GrandGalaxyMapNewsGrandGalaxyExplain",
        "WorldMapNewsAnotherGalaxy",
        "WorldMapNewsAnotherGalaxy",
        "WorldMapNewsAnotherGalaxy",
        "WorldMapNewsAnotherGalaxy",
        "WorldMapNewsAnotherGalaxy",
    };
};  // namespace

void MapDemoStateWarn::init() {
    initNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv2));

    mTalkMessageCtrlArray = new TalkMessageCtrl*[6];

    for (s32 i = 0; i < 6; i++) {
        mTalkMessageCtrlArray[i] = MR::createTalkCtrlDirect(fn_804E15A0(mHost), ::sGrandGalaxyMapMessages[i], TVec3f(0.0f, 0.0f, 0.0f), nullptr);
    }

    mIsDead = true;
}

void MapDemoStateWarn::appear() {
    mIsDead = false;

    setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv1));

    fn_804DFE90(mHost);
}

void MapDemoStateWarn::kill() {
    fn_804DFEA0(mHost);

    MR::deactivateDefaultGameLayout();

    mIsDead = true;
}

bool MapDemoStateWarn::fn_804E29D0() {
    s32 lastUnlockedWorld = fn_804D3F80();

    if (!GameDataFunction::isOnGameEventFlag("グランドギャラクシーマップ初プレイ")) {
        mWorldId = 0;
        return true;
    }

    if (fn_804D75E0() && GameDataFunction::getPlayerGameOverNum() % 3 == 0) {
        if (lastUnlockedWorld == 2 && !GameDataFunction::isOnGameEventFlag("ワールド2ゲームオーバーによる誘導")) {
            mWorldId = 1;
            return true;
        }

        if (lastUnlockedWorld == 3 && !GameDataFunction::isOnGameEventFlag("ワールド3ゲームオーバーによる誘導")) {
            mWorldId = 2;
            return true;
        }

        if (lastUnlockedWorld == 4 && !GameDataFunction::isOnGameEventFlag("ワールド4ゲームオーバーによる誘導")) {
            mWorldId = 3;
            return true;
        }

        if (lastUnlockedWorld == 5 && !GameDataFunction::isOnGameEventFlag("ワールド5ゲームオーバーによる誘導")) {
            mWorldId = 4;
            return true;
        }

        if (lastUnlockedWorld == 6 && !GameDataFunction::isOnGameEventFlag("ワールド6ゲームオーバーによる誘導")) {
            mWorldId = 5;
            return true;
        }
    }

    return false;
}

void MapDemoStateWarn::exeNerve1() {
    if (MR::isFirstStep(this)) {
        fn_804E15B0(mHost);
    }

    if (!fn_804E15E0(mHost)) {
        setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv3));
    }
}

void MapDemoStateWarn::exeNerve2() {
    if (MR::isFirstStep(this)) {
        fn_804E15C0(mHost);
    }

    if (MR::tryTalkForceWithoutDemoAtEnd(mTalkMessageCtrlArray[mWorldId])) {
        fn_804E2D40();
    }
}

void MapDemoStateWarn::exeNerve3() {
    if (MR::isFirstStep(this)) {
        fn_804E15D0(mHost);
    }

    if (!fn_804E15F0(mHost)) {
        kill();
    }
}

void MapDemoStateWarn::exeNerve4() {
    if (MR::isGreaterEqualStep(this, 60)) {
        setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv2));
    }
}

void MapDemoStateWarn::fn_804E2C40() {
    if (mWorldId == 0) {
        setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv3));
        return;
    }

    if (mWorldId >= 1 && mWorldId <= 5) {
        // FIXME
        setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv3));
        return;
    }

    kill();
}

void MapDemoStateWarn::fn_804E2C80() {
    fn_804D75B0();

    if (mWorldId == 0) {
        GameDataFunction::onGameEventFlag("グランドギャラクシーマップ初プレイ");
    }

    if (mWorldId == 1) {
        GameDataFunction::onGameEventFlag("ワールド2ゲームオーバーによる誘導");
    }

    if (mWorldId == 2) {
        GameDataFunction::onGameEventFlag("ワールド3ゲームオーバーによる誘導");
    }

    if (mWorldId == 3) {
        GameDataFunction::onGameEventFlag("ワールド4ゲームオーバーによる誘導");
    }

    if (mWorldId == 4) {
        GameDataFunction::onGameEventFlag("ワールド5ゲームオーバーによる誘導");
    }

    if (mWorldId == 5) {
        GameDataFunction::onGameEventFlag("ワールド6ゲームオーバーによる誘導");
    }
}

void MapDemoStateWarn::fn_804E2D40() {
    fn_804E2C80();

    if (fn_804E29D0()) {
        fn_804E2C40();
    } else {
        setNerve(GET_NERVE(MapDemoStateWarn, MapDemoStateWarnNrv4));
    }
}
