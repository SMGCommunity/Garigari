#pragma once

#include "Game/System/NerveExecutor.hpp"

class SequenceManager;

class GrandGalaxyMapInfoHolder {  // Maybe?
public:
    GrandGalaxyMapInfoHolder();

    void fn_804DFA40(u32);  // Unknown
    void fn_804DFB00();     // Unknown
    void fn_804DFB10();     // Unknown

    /* 0x0 */ void* _0;  // Unknown
    /* 0x4 */ u32 _4;    // Unknown
    /* 0x8 */ u32 _8;    // Unknown
};

class GrandGalaxyMap : public NerveExecutor {
public:
    GrandGalaxyMap(void*);  // Unknown void* goes into _10

    void fn_804DFB90(bool);  // Unknown
    void fn_804DFC20();      // Unknown
    void fn_804DFC70();      // Unknown
    void fn_804DFCC0();      // Unknown
    void* fn_804DFD30();     // Some getter

    /* 0x08 */ GrandGalaxyMapInfoHolder* _8;
    /* 0x0C */ SequenceManager* _C;
    /* 0x10 */ void* _10;  // Unknown
    /* 0x14 */ bool _14;   // Unknown
    /* 0x15 */ bool _15;   // Unknown
};
