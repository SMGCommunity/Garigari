#include "LiveActor/LiveActor.hpp"
#include "System/NerveExecutor.hpp"
#include "Util/ActionSoundUtil.hpp"
struct Actor4CED0 : LiveActor {
    u8 opaque90[0x14];
    void* childA4;
    u8 opaqueA8[0xa0];
    u8 flag148, flag149;
    u8 padding14A[2];
    NerveExecutor* helper14C;
};
extern "C" {
extern u32 lbl_807D3518, lbl_807D3534, lbl_807D352C;
extern const char lbl_80696CD8[], lbl_80696CE8[];
void fn_8046E600(void*);
void fn_8046E610(void*);
void fn_8004E180(void*, s32);
void fn_8024CED0(Actor4CED0* obj) {
    if (obj->flag149) return;
    if (obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3518)))
        MR::startActionSound(obj, lbl_80696CD8, -1, -1, -1);
    else
        MR::startActionSound(obj, lbl_80696CE8, -1, -1, -1);
    fn_8046E600(obj->childA4);
    obj->flag148 = 1;
    obj->helper14C->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3534));
    fn_8004E180(obj, 0);
}
void fn_8024CF80(Actor4CED0* obj) {
    if (obj->flag149) return;
    fn_8046E610(obj->childA4);
    obj->flag148 = 0;
    obj->helper14C->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D352C));
}
}
