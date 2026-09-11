#include "LiveActor/LiveActor.hpp"
struct Actor4DF60 : LiveActor {
    u8 opaque90[4];
    LiveActor* child94;
    void* value98;
    LiveActor** entries;
    LiveActor* childA0;
    u8 opaqueA4[0xa0];
    s32 field144;
};
extern "C" {
void fn_8024E030(Actor4DF60*);
u32 fn_8024C7E0(const void*);
void fn_8024DFE0(Actor4DF60* obj) {
    fn_8024E030(obj);
    obj->entries[fn_8024C7E0(obj->value98)]->makeActorAppeared();
}
void fn_8024E030(Actor4DF60* obj) {
    obj->child94->makeActorDead();
    for (s32 i = 0; i < 7; ++i) obj->entries[i]->makeActorDead();
    obj->childA0->makeActorDead();
}
}
