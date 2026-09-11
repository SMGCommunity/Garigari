#include "LiveActor/LiveActor.hpp"
struct Actor52410 : LiveActor { u8 opaque90[0x14]; void* childA4; u8 opaqueA8[0x28]; void* childD0; };
extern "C" {
bool fn_800308A0(const void*);
bool fn_8045E990(const void*);
extern u32 lbl_807D35BC;
void fn_80252410(Actor52410* obj) {
    if (fn_800308A0(obj->childD0) && fn_8045E990(obj->childA4))
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35BC));
}
}
