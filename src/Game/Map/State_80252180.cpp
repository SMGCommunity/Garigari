#include "LiveActor/LiveActor.hpp"
struct Value52180 { bool tag; u16 value; };
struct Record52180 { u8 opaque[16]; };
struct Child52180 { u8 opaque0[0x144]; s32 index144; };
struct Actor52180 : LiveActor { u8 opaque90[0x20]; Child52180* childB0; u8 opaqueB4[0x10]; Record52180* recordsC4; u8 opaqueC8[8]; LiveActor* childD0; u8 opaqueD4[12]; u8 flagE0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
Value52180* fn_8024C740(Value52180*);
void fn_8024CEB0(void*, Value52180*);
void fn_80483470(void*, const Value52180*);
void fn_80483460(void*);
void fn_804834E0(void*);
bool fn_804DF0D0(const Record52180*);
void fn_80483480(void*, s32);
void fn_80250930(void*);
bool fn_80483410(const void*);
extern u32 lbl_807D35AC, lbl_807D35B0;
void fn_80252180(Actor52180* obj) {
    if (MR::isFirstStep(obj)) {
        if (obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D35AC))) {
            Value52180 value;
            fn_8024C740(&value);
            fn_8024CEB0(obj->childB0, &value);
            fn_80483470(obj->childD0, &value);
        } else {
            obj->flagE0 = 1;
            fn_80483460(obj->childD0);
        }
        fn_804834E0(obj->childD0);
        if (!fn_804DF0D0(&obj->recordsC4[obj->childB0->index144 - 1])) fn_80483480(obj->childD0, 5);
        obj->childD0->appear();
        fn_80250930(obj);
    }
    if (!fn_80483410(obj->childD0)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35B0));
}
}
