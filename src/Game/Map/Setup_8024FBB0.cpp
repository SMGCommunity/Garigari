#include "LiveActor/LiveActor.hpp"
void* operator new(unsigned long);
void* operator new[](unsigned long);
struct Record4FBB0 : LiveActor { u32 opaque90; };
struct Actor4FBB0 : LiveActor { u8 opaque90[12]; TVec3f* positions9C; u8 opaqueA0[0x30]; NameObj* childD0; NameObj* childD4; u32 fieldD8; NameObj* childDC; u8 opaqueE0[8]; Record4FBB0* recordsE8; };
namespace MR { void connectToScene(NameObj*, int, int, int, int); }
extern "C" {
extern const char lbl_80697148[], lbl_80697154[], lbl_80697168[];
extern const f32 lbl_807DC748;
NameObj* fn_804831B0(void*, const char*);
NameObj* fn_80482E30(void*, const char*);
NameObj* fn_80480490(void*, const char*);
void fn_8024FD70(void*);
void fn_8024C570(void*, s32);
void* __construct_new_array(void*, void (*)(void*), void (*)(void*,s32), u32, u32);
void fn_80031170(LiveActor*, const TVec3f&);
void fn_80031370(LiveActor*, f32);
void fn_8024FBB0(Actor4FBB0* obj) {
    void* allocation = ::operator new(0x214);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_804831B0(allocation, lbl_80697148);
    obj->childD0 = child;
    child->initWithoutIter();
}
void fn_8024FC00(Actor4FBB0* obj) {
    void* allocation = ::operator new(0x2c);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_80482E30(allocation, lbl_80697154);
    obj->childD4 = child;
    child->initWithoutIter();
    MR::connectToScene(obj->childD4, 14, 13, -1, 81);
}
void fn_8024FC70(Actor4FBB0* obj) {
    void* allocation = ::operator new(0x48);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_80480490(allocation, lbl_80697168);
    obj->childDC = child;
    child->initWithoutIter();
}
void fn_8024FCC0(Actor4FBB0* obj) {
    obj->recordsE8 = static_cast<Record4FBB0*>(__construct_new_array(::operator new[](0x1cc), fn_8024FD70, fn_8024C570, 0x94, 3));
    for (s32 i = 0; i < 3; ++i) {
        obj->recordsE8[i].initWithoutIter();
        fn_80031170(&obj->recordsE8[i], obj->positions9C[i]);
        fn_80031370(&obj->recordsE8[i], lbl_807DC748);
    }
}
}
