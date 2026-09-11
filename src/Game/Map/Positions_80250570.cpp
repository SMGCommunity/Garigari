#define JGEOMETRY_INLINE_VEC3_CTOR
#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Child50570 : LiveActor { u8 opaque90[0xb4]; s32 value144; };
struct Actor50570 : LiveActor { void* child90; u8 opaque94[4]; LiveActorGroup* group98; TVec3f* positions9C; u8 opaqueA0[4]; void* childA4; u8 opaqueA8[8]; Child50570* selectedB0; };
extern "C" {
extern const f32 lbl_807DC724, lbl_807DC74C, lbl_807DC750, lbl_807DC754;
bool fn_8045E990(const void*);
bool fn_8045E9D0(const void*);
s32 fn_8024F220(s32);
void fn_8024BB20(void*, const TVec3f*);
void fn_80250610(Actor50570*, f32);
bool fn_80250570(const Actor50570* obj) {
    if (fn_8045E990(obj->childA4)) return false;
    return fn_8045E9D0(obj->childA4);
}
void fn_802505C0(Actor50570* obj) {
    fn_80250610(obj, lbl_807DC74C);
    s32 offset = fn_8024F220(obj->selectedB0->value144) * 12;
    fn_8024BB20(obj->child90, reinterpret_cast<TVec3f*>(reinterpret_cast<u8*>(obj->positions9C) + offset));
}
void fn_80250610(Actor50570* obj, f32 y) {
    const f32 step = lbl_807DC750;
    TVec3f position(lbl_807DC754, y, lbl_807DC724);
    for (s32 i = 0; i < 3; ++i) {
        if (!obj->selectedB0 || obj->selectedB0 != obj->group98->getActor(i)) {
            TVec3f& destination = obj->positions9C[i];
            destination.x = position.x;
            destination.y = position.y;
            destination.z = position.z;
        }
        TVec3f delta;
        delta.x = step;
        delta.y = lbl_807DC724;
        delta.z = lbl_807DC724;
        position.add(delta);
    }
}
}
