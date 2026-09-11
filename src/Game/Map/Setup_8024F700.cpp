#include "LiveActor/LiveActor.hpp"
void* operator new(unsigned long);
void* operator new[](unsigned long);
struct Actor4F700 : LiveActor { NameObj* child90; u8 opaque94[0x30]; void* arrayC4; u8* flagsC8; };
extern "C" {
void fn_804DEFE0(void*);
void* __construct_new_array(void*, void (*)(void*), void (*)(void*), u32, u32);
void fn_80250120(LiveActor*);
NameObj* fn_8024B920(void*, const char*);
extern const char lbl_8069708C[];
void fn_8024F700(Actor4F700* obj) {
    obj->arrayC4 = __construct_new_array(::operator new[](0x40), fn_804DEFE0, 0, 0x10, 3);
    obj->flagsC8 = new u8[3];
    fn_80250120(obj);
}
void fn_8024F760(Actor4F700* obj) {
    void* allocation = ::operator new(0xd4);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_8024B920(allocation, lbl_8069708C);
    obj->child90 = child;
    child->initWithoutIter();
}
}
