#include "Game/World/MapDemoStateInit.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/NerveUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "Game/World/GrandGalaxyMap.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 804E1450, GrandGalaxyMap*, const TVec3f&)
EXTERN_UNKNOWN_FUNC(void, 804E1490, GrandGalaxyMap*, f32)
EXTERN_UNKNOWN_FUNC(void, 804E1590, GrandGalaxyMap*, const char*)
EXTERN_UNKNOWN_FUNC(void, 804E1740, GrandGalaxyMap*, s32, s32)

namespace NrvMapDemoStateInit {
    NEW_NERVE(MapDemoStateInitNrv1, MapDemoStateInit, Nerve1);
};

MapDemoStateInit::MapDemoStateInit(GrandGalaxyMap* pHost) : ActorStateBase< GrandGalaxyMap >("State[開始状態]", pHost) {
}

void MapDemoStateInit::init() {
    initNerve(GET_NERVE(MapDemoStateInit, MapDemoStateInitNrv1));
    mIsDead = true;
}

void MapDemoStateInit::appear() {
    mIsDead = false;

    fn_804E1590(mHost, "Wait");
    fn_804E1740(mHost, -1, 0);

    MR::openSystemWipeWhiteFade();
}

void MapDemoStateInit::kill() {
    mIsDead = true;
}

void MapDemoStateInit::exeNerve1() {
    // FIXME: fn_804E1450 is inlined in some function
    if (MR::isFirstStep(this)) {
        GrandGalaxyMap* pMap = mHost;
        fn_804E1450(pMap, TVec3f(0.0f, 0.0f, -1.0f));
        return;
    }

    if (MR::isLessStep(this, 30)) {
        GrandGalaxyMap* pMap = mHost;
        fn_804E1450(pMap, TVec3f(0.0f, 0.0f, -1.0f));
    } else {
        fn_804E1490(mHost, 0.08f);
    }

    if (MR::isStep(this, 60)) {
        kill();
    }
}

MapDemoStateInit::~MapDemoStateInit() {};
