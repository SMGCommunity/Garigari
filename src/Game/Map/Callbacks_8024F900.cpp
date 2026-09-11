#include "LiveActor/LiveActor.hpp"
void* operator new(unsigned long);
struct Method4F900 { u32 a, b, c; };
struct Callback4F900 { const void* vtable; LiveActor* actor; Method4F900 method; };
struct Actor4F900 : LiveActor { u8 opaque90[0x10]; NameObj* childA0; };
extern "C" {
extern const char lbl_80697058[];
NameObj* fn_8046CFE0(void*, const char*);
Callback4F900* fn_8024FA20(Callback4F900*, LiveActor*, const Method4F900&);
void fn_8046D1A0(NameObj*, const Callback4F900&, const Callback4F900&, const Callback4F900&, const Callback4F900&);
void fn_8024F900(Actor4F900* obj) {
    void* allocation = ::operator new(0x64);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_8046CFE0(allocation, lbl_80697058 + 0xc0);
    obj->childA0 = child;
    child->initWithoutIter();
    Method4F900 d = *reinterpret_cast<const Method4F900*>(lbl_80697058 + 0xb4);
    Method4F900 c = *reinterpret_cast<const Method4F900*>(lbl_80697058 + 0xa8);
    Method4F900 b = *reinterpret_cast<const Method4F900*>(lbl_80697058 + 0x9c);
    Method4F900 a = *reinterpret_cast<const Method4F900*>(lbl_80697058 + 0x90);
    Callback4F900 cd, cc, cb, ca;
    fn_8024FA20(&cd, obj, d);
    fn_8024FA20(&cc, obj, c);
    fn_8024FA20(&cb, obj, b);
    fn_8024FA20(&ca, obj, a);
    fn_8046D1A0(obj->childA0, ca, cb, cc, cd);

}
}
