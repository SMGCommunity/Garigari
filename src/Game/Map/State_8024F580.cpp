#include "LiveActor/LiveActor.hpp"
extern "C" {
extern u32 lbl_807D35E4;
void fn_80250240(LiveActor*, void*);
void fn_802502C0(LiveActor*, void*);
void fn_8024F580(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35E4)); }
void fn_8024F590(LiveActor* obj, void* argument, s32 kind) {
    switch (kind) {
    case 0: fn_80250240(obj, argument); break;
    case 1: fn_802502C0(obj, argument); break;
    }
}
}
