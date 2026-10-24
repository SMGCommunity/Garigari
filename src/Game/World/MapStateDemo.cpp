#include "Game/World/MapStateDemo.hpp"
#include "Game/LiveActor/ActorStateBase.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/NerveUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "decomp.h"

EXTERN_UNKNOWN_FUNC(void, 804E1590, GrandGalaxyMap*, const char*)
EXTERN_UNKNOWN_FUNC(void, 804E1740, GrandGalaxyMap*, s32, s32)

namespace NrvMapStateDemo {
    NEW_NERVE(MapStateDemoNerve1, MapStateDemo, Nerve1);
    NEW_NERVE(MapStateDemoNerve2, MapStateDemo, Nerve2)
};

MapStateDemo::MapStateDemo(GrandGalaxyMap* pHost) : ActorStateBase< GrandGalaxyMap >("State[開始デモ]", pHost) {
}

void MapStateDemo::init() {
    initNerve(GET_NERVE(MapStateDemo, MapStateDemoNerve2));
    mIsDead = true;
}

void MapStateDemo::appear() {
    mIsDead = false;
    fn_804E1590(mHost, "Wait");
    fn_804E1740(mHost, -1, 0);

    MR::openSystemWipeWhiteFade();

    setNerve(GET_NERVE(MapStateDemo, MapStateDemoNerve1));
}

void MapStateDemo::kill() {
    fn_804E1740(mHost, -1, -1);
    mIsDead = true;
}

void MapStateDemo::exeNerve1() {
    if (MR::isFirstStep(this)) {
        _10 = MR::getFovy();
    }

    // FIXME: float shenanigans
    MR::setFovy(MR::getEaseOutValue(getNerveStep() / 20, 0.01f, _10, 1.0f));

    if (MR::isStep(this, 20)) {
        kill();
    }
}

void MapStateDemo::exeNerve2() {
    _10 = MR::getFovy();

    setNerve(GET_NERVE(MapStateDemo, MapStateDemoNerve2));
}
