#pragma once

#include "Game/System/NerveExecutor.hpp"

class GrandGalaxyMap;

class SequenceManager : public NerveExecutor {
public:
    SequenceManager(GrandGalaxyMap*);

    virtual ~SequenceManager();

    void fn_804E04A0(bool);  // Unknown
    void fn_804E0640();      // Unknown
    void fn_804E0690();      // Unknown
    void fn_804E06A0();      // Unknown
    void fn_804E0710();      // Unknown
    void fn_804E0760();      // Unknown
    void fn_804E0800();      // Unknown
    void fn_804E0810();      // Unknown
    void fn_804E0820();      // Unknown

    void exeNerve1();
    void exeNerve2();
    void exeNerve3();
    void exeNerve4();
    void exeNerve5();
    void exeNerve6();

    /* 0x08 */ GrandGalaxyMap* mMap;
    /* 0x0C */ u32 _C;    // Unknown
    /* 0x10 */ u32 _10;   // Unknown
    /* 0x14 */ u32 _14;   // Unknown
    /* 0x18 */ u32 _18;   // Unknown
    /* 0x1C */ u32 _1C;   // Unknown
    /* 0x20 */ u32 _20;   // Unknown
    /* 0x24 */ bool _24;  // Unknown
};
