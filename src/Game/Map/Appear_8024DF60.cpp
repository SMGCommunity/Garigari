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
extern const char lbl_80696D44[];
void fn_8000A010(LiveActor*, const char*);
void fn_80009BB0(LiveActor*, f32);
void fn_8024DF60(Actor4DF60* obj) {
    fn_8024E030(obj);
    obj->child94->makeActorAppeared();
    fn_8000A010(obj->child94, lbl_80696D44);
    fn_80009BB0(obj->child94, (f32)(obj->field144 - 1));
}
}
