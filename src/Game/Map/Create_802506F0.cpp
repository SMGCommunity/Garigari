#include "LiveActor/LiveActor.hpp"
#include <cstdio>
void* operator new(unsigned long);
void* operator new[](unsigned long);
struct Value506F0 { bool tag; u16 value; };
extern "C" {
extern const char lbl_806971A0[];
Value506F0* fn_8024C740(Value506F0*);
LiveActor* fn_8024C8D0(void*, s32, u8, const void*, const char*);
LiveActor* fn_802506F0(void*, s32 index) {
    LiveActor* child;
    Value506F0 value;
    fn_8024C740(&value);
    char* name = new char[64];
    snprintf(name, 64, lbl_806971A0, index);
    void* allocation = ::operator new(0x174);
    child = static_cast<LiveActor*>(allocation);
    if (allocation) child = fn_8024C8D0(allocation, index, 1, &value, name);
    child->initWithoutIter();
    return child;
}
}
