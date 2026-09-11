#include "LiveActor/LiveActor.hpp"
struct Value52690 { bool tag; u16 value; };
struct Child52690 { u8 opaque0[0x144]; s32 index144; };
struct Actor52690 : LiveActor { u8 opaque90[0x20]; Child52690* childB0; u8 opaqueB4[0x14]; u8* flagsC8; u8 opaqueCC[4]; void* childD0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_80250180(void*);
Value52690* fn_8024C740(Value52690*);
void fn_80483440(void*, Value52690*);
void fn_8024CCD0(void*, const Value52690*, u8);
void fn_802503B0(void*, s32);
bool fn_8024CC80(const void*);
bool fn_8024C7A0(const Value52690*);
extern u32 lbl_807D35C8, lbl_807D358C;
void fn_80252690(Actor52690* obj) {
    if (MR::isFirstStep(obj)) {
        fn_80250180(obj);
        s32 index = obj->childB0->index144;
        Value52690 value;
        fn_8024C740(&value);
        fn_80483440(obj->childD0, &value);
        fn_8024CCD0(obj->childB0, &value, obj->flagsC8[index - 1]);
        fn_802503B0(obj, index);
    }
    if (fn_8024CC80(obj->childB0)) {
        Value52690 value;
        fn_8024C740(&value);
        fn_80483440(obj->childD0, &value);
        if (fn_8024C7A0(&value)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35C8));
        else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D358C));
    }
}
}
