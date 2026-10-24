#include "Game/World/MapDemoStateWait.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/MathUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void*, 804DFD30, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1740, GrandGalaxyMap*, s32, s32)
EXTERN_UNKNOWN_FUNC(s32, 804E1D90, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(s32, 804E1DA0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1DF0, GrandGalaxyMap*, s32)
EXTERN_UNKNOWN_FUNC(void, 804E1E00, GrandGalaxyMap*, s32)
EXTERN_UNKNOWN_FUNC(void, 804E1E10, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804F2ED0, void*, s32)
EXTERN_UNKNOWN_FUNC(void, 804F2F00, void*, s32)

namespace NrvMapDemoStateWait {
    NEW_NERVE(MapDemoStateWaitNrv1, MapDemoStateWait, Nerve1);  // Unknown (unused?)
};  // namespace NrvMapDemoStateWait

MapDemoStateWait::MapDemoStateWait(GrandGalaxyMap* pHost)
    : ActorStateBase< GrandGalaxyMap >("State[ウェイト]", pHost), _10(-1), _14(-1), mWaitTime() {
}

void MapDemoStateWait::init() {
    initNerve(GET_NERVE(MapDemoStateWait, MapDemoStateWaitNrv1));
    mIsDead = true;
}

void MapDemoStateWait::appear() {
    mIsDead = false;

    fn_804E1740(mHost, -1, -1);

    setNerve(GET_NERVE(MapDemoStateWait, MapDemoStateWaitNrv1));

    _10 = fn_804E1DA0(mHost);
    fn_804E1DF0(mHost, _10);
}

void MapDemoStateWait::kill() {
    mIsDead = true;
}

void MapDemoStateWait::fn_804E2680() {
    if (_10 > 0) {
        fn_804E1E10(mHost);
    }

    s32 val = fn_804E1D90(mHost);
    if (val != 0) {
        fn_804E1E00(mHost, val);
    }

    mWaitTime = MR::max(mWaitTime - 1, 0);
}

void MapDemoStateWait::fn_804E26F0(s32 val) {
    if (mWaitTime == 0) {
        fn_804F2ED0(fn_804DFD30(mHost), val);
    }

    _14 = val;
    mWaitTime = 2;
}

void MapDemoStateWait::fn_804E2750() {
    if (mWaitTime != 0) {
        fn_804F2F00(fn_804DFD30(mHost), _14);
    }

    _14 = -1;
}
