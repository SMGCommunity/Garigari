#include "LiveActor/LiveActor.hpp"
struct Value52610 { bool tag; u16 value; };
struct Child52610 { u8 opaque0[0x144]; s32 index144; };
struct Actor52610 : LiveActor { u8 opaque90[0x20]; Child52610* childB0; u8 opaqueB4[0x1c]; void* childD0; u8 opaqueD4[12]; u8 flagE0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
Value52610* fn_8024C740(Value52610*);
void fn_80483440(void*, Value52610*);
void fn_80250FC0(void*, s32, const Value52610*);
bool fn_804D6070();
extern u32 lbl_807D35C4;
void fn_80252610(Actor52610* obj) {
    if (MR::isFirstStep(obj)) {
        Value52610 value;
        fn_8024C740(&value);
        fn_80483440(obj->childD0, &value);
        fn_80250FC0(obj, obj->childB0->index144, &value);
        obj->flagE0 = 0;
    }
    if (!fn_804D6070()) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35C4));
}
}
