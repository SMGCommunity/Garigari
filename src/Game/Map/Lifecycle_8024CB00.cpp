#include "LiveActor/LiveActor.hpp"
struct Actor4CB00 : LiveActor {
    u8 flag90;
    u8 pad91[3];
    LiveActor* child94;
    void* value98;
    LiveActor** entries;
    LiveActor* childA0;
    u8 opaqueA4[0xa4];
    u8 flag148, flag149;
};
extern "C" {
void fn_8024DF60(void*);
bool fn_8024C7A0(const void*);
void fn_8024E030(void*);
void fn_8024DFE0(void*);
extern u32 lbl_807D3518, lbl_807D351C;
void fn_8024CB00(Actor4CB00* obj) {
    obj->LiveActor::appear();
    if (obj->flag90) {
        fn_8024DF60(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3518));
    }
    else {
        if (fn_8024C7A0(obj->value98)) {
            fn_8024E030(obj);
            obj->childA0->makeActorAppeared();
        }
        else fn_8024DFE0(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D351C));
    }
}
void fn_8024CBA0(Actor4CB00* obj) {
    obj->LiveActor::makeActorAppeared();
    obj->flag148 = 0;
    obj->flag149 = 0;
}
void fn_8024CBE0(Actor4CB00* obj) {
    obj->LiveActor::makeActorDead();
    obj->child94->makeActorDead();
    for (s32 i = 0; i < 7; ++i) obj->entries[i]->makeActorDead();
    obj->childA0->makeActorDead();
}
}
