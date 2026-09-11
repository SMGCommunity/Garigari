#include "LiveActor/LiveActor.hpp"
#include "System/NerveExecutor.hpp"
struct Actor4D7F0;
struct Callback4D7F0 { virtual void slot08(Actor4D7F0*, s32); };
struct Actor4D7F0 : LiveActor {
    u8 opaque90[0xb8];
    u8 flag148, flag149;
    u8 padding14A[2];
    NerveExecutor* helper14C;
    NerveExecutor* helper150;
    Callback4D7F0* callback154;
};
extern "C" {
bool fn_8005C810(Actor4D7F0*, u32, u32, u32);
bool fn_8005CB00(Actor4D7F0*);
bool fn_8002AB20();
extern u32 lbl_807D352C;
void fn_8024D7F0(Actor4D7F0* obj) {
    if (obj->flag149) {
        if (fn_8005C810(obj, 0, 0, 0) && obj->callback154)
            obj->callback154->slot08(obj, 2);
    } else {
        if (fn_8005CB00(obj) && obj->callback154)
            obj->callback154->slot08(obj, 0);
    }
    if (!obj->flag149 && obj->flag148 && fn_8002AB20() && obj->callback154) {
        obj->callback154->slot08(obj, 1);
        obj->helper14C->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D352C));
    }
}
}
