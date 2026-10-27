#include "Game/LiveActor/ActorLightCtrl.hpp"

#include "Game/Map/LightPointCtrl.hpp"

ActorLightCtrl::ActorLightCtrl(const LiveActor* pActor) : mActor(pActor), _4(-1), _8(0), _C(0), _10(0), mZoneLightID() {
    /*
    r3: 0x14 bytes into this
    r4: pLiveActor
    r29: this
    r30: -1
    r31: 0
    */
    _1C = 0;
    _50 = 0;
    _54 = 0;
}
