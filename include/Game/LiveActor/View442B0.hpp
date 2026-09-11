#pragma once
#include "LiveActor/LiveActor.hpp"
// Only the target's appended virtual slots and accessed fields are described.
struct View442B0 : LiveActor {
 void fn_80244730();
 void fn_802446D0();
 virtual void slot70();
 virtual void slot74(const char*);
 virtual void slot78();
 bool flag90, flag91; u8 pad[2]; f32 value;
};
typedef void (View442B0::*Method442B0)();
struct Callback442B0 { Callback442B0(void*, Method442B0); const void* vtable; void* obj; Method442B0 method; };
