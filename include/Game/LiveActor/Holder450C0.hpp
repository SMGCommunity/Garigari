#pragma once
#include <revolution.h>
struct Opaque45130 {};
typedef void (Opaque45130::*Method45130)();
struct Call45130 {
 inline Call45130(Method45130 value) ALWAYS_INLINE :method(value) {}
 inline void operator()(Opaque45130* obj) const { (obj->*method)(); }
 Method45130 method;
};
struct Holder450C0 { u8 opaque[0x14]; Opaque45130* items[1024]; s32 count; };
