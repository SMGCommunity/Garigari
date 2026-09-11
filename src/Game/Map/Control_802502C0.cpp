#include "LiveActor/LiveActor.hpp"
struct Actor502C0 : LiveActor { u8 opaque90[0x20]; LiveActor* valueB0; u8 opaqueB4[4]; void* previousB8; };
namespace MR { void startActionSound(const LiveActor*, const char*, long, long, long); }
extern "C" {
extern u32 lbl_807D3578, lbl_807D3598, lbl_807D357C;
extern const char lbl_8069718C[];
bool fn_8024CC70(const LiveActor*);
void fn_802512B0(LiveActor*);
void fn_8024CF80(void*);
}
extern "C" {
void fn_802502C0(Actor502C0* obj, LiveActor* child) {
    if (obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3578))) {
        if (fn_8024CC70(child)) {
            obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3598));
            goto action;
        } else {
            obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D357C));
            goto action;
        }
    }
    return;
action:
    obj->valueB0 = child;
    MR::startActionSound(obj, lbl_8069718C, -1, -1, -1);
    fn_802512B0(obj);
}
void fn_80250360(Actor502C0* obj) {
    if (obj->previousB8) {
        fn_8024CF80(obj->previousB8);
        obj->previousB8 = 0;
    }
}
}
