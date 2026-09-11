#include "LiveActor/LiveActor.hpp"
struct Actor52120 : LiveActor { u8 opaque90[0x14]; void* childA4; u8 opaqueA8[0x18]; void* childC0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
bool fn_8045E990(const void*);
bool fn_800308A0(const void*);
extern u32 lbl_807D35AC;
void fn_80252120(Actor52120* obj) {
    MR::isFirstStep(obj);
    if (fn_8045E990(obj->childA4) && fn_800308A0(obj->childC0))
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35AC));
}
}
