#include "Game/World/MapDemoManager.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/NerveUtil.hpp"
#include "Game/Util/SoundUtil.hpp"
#include "Game/Util/StarPointerUtil.hpp"
#include "Game/World/GrandGalaxyMap.hpp"
#include "Game/World/MapDemoStateEnter.hpp"
#include "Game/World/MapDemoStateInit.hpp"
#include "Game/World/MapDemoStateMove.hpp"
#include "Game/World/MapDemoStateWait.hpp"
#include "Game/World/MapDemoStateWarn.hpp"
#include "Game/World/MapDemoStateWarp.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(bool, 804E1130, GrandGalaxyMap*, s32)
EXTERN_UNKNOWN_FUNC(s32, 804E11D0, GrandGalaxyMap*, f32)
EXTERN_UNKNOWN_FUNC(bool, 804E1330, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(bool, 804E1390, GrandGalaxyMap*, MapDemoStateWarp*)
EXTERN_UNKNOWN_FUNC(s32, 804E14D0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1600, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(LiveActor*, 804E1840, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1CE0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1D80, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(bool, 804F60E0, void)
EXTERN_UNKNOWN_FUNC(bool, 804F60F0, void)

namespace NrvMapDemoManager {
    NEW_NERVE(MapDemoManagerNrvEnterDemo, MapDemoManager, Enter);
    NEW_NERVE(MapDemoManagerNrvEnterDirect, MapDemoManager, Enter);
    NEW_NERVE(MapDemoManagerNrvWait, MapDemoManager, Wait);
    NEW_NERVE(MapDemoManagerNrvNews, MapDemoManager, News);
    NEW_NERVE(MapDemoManagerNrvPointMove, MapDemoManager, PointMove);
    NEW_NERVE(MapDemoManagerNrvWorldWarp, MapDemoManager, WorldWarp);
};  // namespace NrvMapDemoManager

MapDemoManager::MapDemoManager(GrandGalaxyMap* pMap) : NerveExecutor("シーケンス管理"), mMap(pMap), mStateWait(), mIsPlayerStickMoving() {
}

void MapDemoManager::init(bool isEnterDirect) {
    fn_804E1600(mMap);

    initNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWait), 16);

    mStateEnter = new MapDemoStateEnter(mMap);
    mStateInit = new MapDemoStateInit(mMap);
    mStateWait = new MapDemoStateWait(mMap);
    mStateWarn = new MapDemoStateWarn(mMap);
    mStateWarp = new MapDemoStateWarp(mMap);

    MR::initActorState(this, mStateEnter, GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDemo), "EnterDemo");
    MR::initActorState(this, mStateInit, GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDirect), "EnterDirect");
    MR::initActorState(this, mStateWait, GET_NERVE(MapDemoManager, MapDemoManagerNrvWait), "Wait");
    MR::initActorState(this, mStateWarn, GET_NERVE(MapDemoManager, MapDemoManagerNrvNews), "News");
    MR::initActorState(this, new MapDemoStateMove(mMap), GET_NERVE(MapDemoManager, MapDemoManagerNrvPointMove), "PointMove");
    MR::initActorState(this, mStateWarp, GET_NERVE(MapDemoManager, MapDemoManagerNrvWorldWarp), "WorldWarp");

    if (isEnterDirect) {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDirect));
    } else {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDemo));
    }
}

void MapDemoManager::fn_804E0640() {
    if (!isNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDirect))) {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvEnterDemo));
    }
}

void MapDemoManager::fn_804E0690() {
}

void MapDemoManager::exeEnter() {
    if (!MR::updateActorState(this)) {
        return;
    }

    if (mStateWarn->fn_804E29D0()) {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvNews));
    } else {
        fn_804E1CE0(mMap);
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWait));
    }
}

void MapDemoManager::exeNews() {
    if (MR::updateActorState(this)) {
        fn_804E1CE0(mMap);
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWait));
    }
}

void MapDemoManager::exeWait() {
    if (MR::isFirstStep(this)) {
        mIsPlayerStickMoving = fn_804F60F0();
        MR::disableStarPointerShootStarPiece();
    }

    MR::updateActorState(this);

    if (fn_804E0820()) {
        return;
    }

    if (!fn_804E1390(mMap, mStateWarp)) {
        return;
    }

    MR::startActionSound(fn_804E1840(mMap), "PushAButton");

    fn_804E1D80(mMap);

    setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWorldWarp));
}

void MapDemoManager::exePointMove() {
    if (MR::updateActorState(this)) {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWait));
    }
}

void MapDemoManager::exeWorldWarp() {
    MR::updateActorState(this);
}

bool MapDemoManager::isActiveWorldWarp() {
    return isNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvWorldWarp));
}

bool MapDemoManager::isNotWarping() {
    return mStateWarp->mIsDead;
}

bool MapDemoManager::fn_804E0820() {
    s32 val = fn_804E14D0(mMap);
    if (val > -1) {
        mStateWait->fn_804E26F0(val);
    } else {
        mStateWait->fn_804E2750();
    }

    bool b1 = fn_804E1130(mMap, val);
    bool b2 = fn_804E1330(mMap);

    if (b1) {
        MR::startCSSound("CSmStateEnterLICK_WMAP", nullptr, 0, 0, 1.0f);
    }

    if (b1 || b2) {
        setNerve(GET_NERVE(MapDemoManager, MapDemoManagerNrvPointMove));
        return true;
    }

    LiveActor* pActor = fn_804E1840(mMap);
    if (!b1 && val > 0 && fn_804F60E0()) {
        MR::startActionSound(pActor, "NoMove");
    }

    bool val2 = fn_804E11D0(mMap, 0.1f) >= 0;
    if (!b2 && !mIsPlayerStickMoving && fn_804F60F0() && !val2) {
        MR::startActionSound(pActor, "NoMove");
    }

    mIsPlayerStickMoving = fn_804F60F0();

    return false;
}
