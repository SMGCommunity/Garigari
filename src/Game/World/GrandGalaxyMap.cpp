#include "Game/World/GrandGalaxyMap.hpp"
#include "Game/World/SequenceManager.hpp"
#include "decomp.h"

EXTERN_UNKNOWN_FUNC(u32, 804E8950, void*)
EXTERN_UNKNOWN_FUNC(void, 804F3AE0, void*)
EXTERN_UNKNOWN_FUNC(void, 804F3B30, void*)

GrandGalaxyMapInfoHolder::GrandGalaxyMapInfoHolder() : _4(), _8() {
}

// void GrandGalaxyMapInfoHolder::fn_804DFA40(u32 idx) {}

void GrandGalaxyMapInfoHolder::fn_804DFB00() {
    fn_804F3AE0(_0);
}

void GrandGalaxyMapInfoHolder::fn_804DFB10() {
    fn_804F3B30(_0);
}

GrandGalaxyMap::GrandGalaxyMap(void* a1) : NerveExecutor("グランドギャラクシーマップ"), _8(), _C(), _10(a1), _15() {
}

void GrandGalaxyMap::fn_804DFB90(bool a1) {
    _8 = new GrandGalaxyMapInfoHolder();
    _8->fn_804DFA40(fn_804E8950(_10));

    _C = new SequenceManager(this);
    _C->fn_804E04A0(a1);

    fn_804DFC70();
}

void GrandGalaxyMap::fn_804DFC20() {
    if (_15) {
        _15 = false;

        _C->fn_804E0640();
        _8->fn_804DFB00();
    }
}

void GrandGalaxyMap::fn_804DFC70() {
    if (!_15) {
        _15 = true;

        _C->fn_804E0690();
        _8->fn_804DFB10();
    }
}

void GrandGalaxyMap::fn_804DFCC0() {
    _C->updateNerve();
}
