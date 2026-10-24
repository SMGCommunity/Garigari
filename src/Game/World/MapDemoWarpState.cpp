#include "Game/World/MapDemoWarpState.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/System/GameDataFunction.hpp"
#include "Game/Util/BgmUtil.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/NerveUtil.hpp"
#include <decomp.h>


EXTERN_UNKNOWN_FUNC(void, 80059240, void)
EXTERN_UNKNOWN_FUNC(void, 804D65C0, s32)
EXTERN_UNKNOWN_FUNC(void, 804D72A0, u32)

namespace NrvMapDemoWarpState {
    NEW_NERVE(MapDemoWarpStateNrvWait, MapDemoWarpState, Wait);
};

MapDemoWarpState::MapDemoWarpState(GrandGalaxyMap* pHost)
    : ActorStateBase< GrandGalaxyMap >("State[ワールドワープ]", pHost), mWarpWorldId(-1), _14(-1), mZoom() {
}

void MapDemoWarpState::init() {
    initNerve(GET_NERVE(MapDemoWarpState, MapDemoWarpStateNrvWait));
    mIsDead = true;
}

void MapDemoWarpState::appear() {
    mIsDead = false;
    setNerve(GET_NERVE(MapDemoWarpState, MapDemoWarpStateNrvWait));

    fn_80059240();

    mZoom = MR::getFovy();
}

void MapDemoWarpState::exeWait() {
    if (MR::isFirstStep(this) && GameDataFunction::getCurrentWorldId() != mWarpWorldId) {
        MR::stopStageBGM(30);
        MR::stopSubBGM(0);
    }

    // FIXME: there is some inline here just like in the other states
    f32 val = MR::getEaseInValue(getNerveStep(), mZoom, 0.01f, 1.0f);
    MR::setFovy(MR::clamp(val, 0.01f, 1.0f));

    if (!MR::isGreaterEqualStep(this, 30)) {
        return;
    }

    if (GameDataFunction::getCurrentWorldId() == mWarpWorldId) {
        kill();
    } else {
        fn_804D72A0(_14);
        fn_804D65C0(mWarpWorldId);
    }
}
