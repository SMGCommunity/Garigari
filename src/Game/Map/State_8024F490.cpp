#include "LiveActor/LiveActor.hpp"
struct Actor4F490 : LiveActor { u8 opaque90[0x14]; LiveActor* childA4; };
extern "C" {
void* fn_803B65E0();
void fn_80050FD0(void*);
void fn_803B6830(s32);
void fn_8024FDF0(LiveActor*);
void fn_80250060(LiveActor*);
extern u32 lbl_807D3560, lbl_807D3590, lbl_807D35A4, lbl_807D35D4;
void fn_8024F490(LiveActor* obj) {
    obj->LiveActor::appear();
    fn_80050FD0(fn_803B65E0());
    obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3560));
}
void fn_8024F4D0(Actor4F490* obj) {
    obj->childA4->makeActorAppeared();
    obj->LiveActor::kill();
    fn_803B6830(0);
}
void fn_8024F520(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3590)); }
void fn_8024F530(LiveActor* obj) {
    fn_8024FDF0(obj);
    fn_80250060(obj);
    obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35A4));
}
void fn_8024F570(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35D4)); }
}
