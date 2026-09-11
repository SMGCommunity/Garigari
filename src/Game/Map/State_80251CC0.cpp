#include "LiveActor/LiveActor.hpp"
struct Child51CC0 { u8 opaque0[0x144]; s32 index144; };
struct Aux51CC0 { u8 opaque0[0x1f8]; s32 value1F8; };
struct Actor51CC0 : LiveActor { u8 opaque90[0x10]; LiveActor* childA0; LiveActor* childA4; u8 opaqueA8[8]; Child51CC0* childB0; u8 opaqueB4[12]; LiveActor* childC0; u8 opaqueC4[12]; Aux51CC0* childD0; };
namespace MR { bool isFirstStep(const LiveActor*); bool isStep(const LiveActor*, long); }
extern "C" {
bool fn_800308A0(const void*);
void fn_802503B0(void*, s32);
void fn_8046DAF0(void*);
void fn_8024D010(void*);
void fn_8024CFD0(void*);
bool fn_80250570(const void*);
void fn_8024FDF0(void*);
void fn_80250360(void*);
void fn_802515A0(void*);
extern u32 lbl_807D3574;
void fn_80251CC0(Actor51CC0* obj) {
    if (MR::isFirstStep(obj)) {
        obj->childA0->appear();
        obj->childA4->appear();
        if (fn_800308A0(obj->childC0)) {
            fn_802503B0(obj, obj->childB0->index144);
            obj->childC0->appear();
        }
        fn_8046DAF0(obj->childC0);
        fn_8024D010(obj->childB0);
    }
    if (MR::isStep(obj, 90)) fn_8024CFD0(obj->childB0);
    if (fn_80250570(obj)) {
        fn_8024CFD0(obj->childB0);
        fn_8024FDF0(obj);
        fn_80250360(obj);
        obj->childD0->value1F8 = 0;
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3574));
    } else fn_802515A0(obj);
}
}
