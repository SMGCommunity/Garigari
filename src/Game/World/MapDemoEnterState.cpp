#include "Game/World/MapDemoEnterState.hpp"
#include "Game/LiveActor/ActorStateBase.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/NerveUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 804E1590, GrandGalaxyMap*, const char*)
EXTERN_UNKNOWN_FUNC(void, 804E1740, GrandGalaxyMap*, s32, s32)

namespace NrvMapStateDemo {
    NEW_NERVE(MapDemoEnterStateNrvWait, MapDemoEnterState, Wait);
    NEW_NERVE(MapDemoEnterStateNrvZoom, MapDemoEnterState, Zoom);
};  // namespace NrvMapStateDemo

MapDemoEnterState::MapDemoEnterState(GrandGalaxyMap* pHost) : ActorStateBase< GrandGalaxyMap >("State[開始デモ]", pHost) {
}

void MapDemoEnterState::init() {
    initNerve(GET_NERVE(MapStateDemo, MapDemoEnterStateNrvWait));
    mIsDead = true;
}

void MapDemoEnterState::appear() {
    mIsDead = false;
    fn_804E1590(mHost, "Wait");
    fn_804E1740(mHost, -1, 0);

    MR::openSystemWipeWhiteFade();

    setNerve(GET_NERVE(MapStateDemo, MapDemoEnterStateNrvZoom));
}

void MapDemoEnterState::kill() {
    fn_804E1740(mHost, -1, -1);
    mIsDead = true;
}

void MapDemoEnterState::exeZoom() {
    if (MR::isFirstStep(this)) {
        mFovy = MR::getFovy();
    }

    // FIXME: float shenanigans
    MR::setFovy(MR::getEaseOutValue(static_cast< f32 >(getNerveStep()) / 20.0f, 0.01f, mFovy, 1.0f));

    if (MR::isStep(this, 20)) {
        kill();
    }
}

void MapDemoEnterState::exeWait() {
    mFovy = MR::getFovy();

    setNerve(GET_NERVE(MapStateDemo, MapDemoEnterStateNrvZoom));
}
