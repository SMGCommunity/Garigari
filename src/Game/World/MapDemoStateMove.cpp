#include "Game/World/MapDemoStateMove.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 804E1BE0, GrandGalaxyMap*)
EXTERN_UNKNOWN_FUNC(void, 804E1C60, GrandGalaxyMap*)

namespace NrvMapDemoStateMove {
    NEW_NERVE(MapDemoStateMoveNrv1, MapDemoStateMove, Nerve1);
    NEW_NERVE(MapDemoStateMoveNrv2, MapDemoStateMove, Nerve1);
};  // namespace NrvMapDemoStateMove

MapDemoStateMove::MapDemoStateMove(GrandGalaxyMap* pHost)
    : ActorStateBase< GrandGalaxyMap >("State[移動]", pHost), _10(100.0f), _14(400.0f), _18(0.85f), _1C(0.0f, 0.0f, 0.0f), _28(0.0f, 0.0f, 0.0f),
      _34(0.0f, 0.0f, 0.0f), _40(), _44(), _48(), _4C(-1), _50(-1), _54() {
}

void MapDemoStateMove::init() {
    initNerve(GET_NERVE(MapDemoStateMove, MapDemoStateMoveNrv1));
    mIsDead = true;
}

// void MapDemoStateMove::appear() {}

void MapDemoStateMove::kill() {
    if (isNerve(GET_NERVE(MapDemoStateMove, MapDemoStateMoveNrv1))) {
        fn_804E1BE0(mHost);
    } else {
        fn_804E1C60(mHost);
    }

    mIsDead = true;
}

// void MapDemoStateMove::exeNerve1() {}
