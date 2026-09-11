#include "LiveActor/LiveActor.hpp"
namespace MR { bool isDead(const LiveActor*); void emitEffect(LiveActor*, const char*); void deleteEffect(LiveActor*, const char*); }
struct Actor4E0C0 : LiveActor {
    u8 opaque90[4];
    LiveActor* child94;
    void* value98;
    LiveActor** entries;
    LiveActor* childA0;
    u8 opaqueA4[0xa7];
    u8 flag14B;
};
extern "C" {
extern const char lbl_80696D9C[], lbl_80696DA4[], lbl_80696DAC[], lbl_80696DB4[];
void fn_8024EF20(LiveActor*); void fn_8024EF30(LiveActor*); void fn_8024EF40(LiveActor*);
void fn_8024EF50(LiveActor*); void fn_8024EF60(LiveActor*);
void fn_8024E0C0(Actor4E0C0* obj) {
    if (!MR::isDead(obj->child94)) MR::emitEffect(obj->child94, lbl_80696D9C);
    for (s32 i = 0; i < 7; ++i) if (!MR::isDead(obj->entries[i])) fn_8024EF20(obj->entries[i]);
    if (!MR::isDead(obj->childA0)) MR::emitEffect(obj->childA0, lbl_80696D9C);
}
void fn_8024E170(Actor4E0C0* obj) {
    if (!MR::isDead(obj->child94)) MR::emitEffect(obj->child94, lbl_80696DA4);
    for (s32 i = 0; i < 7; ++i) if (!MR::isDead(obj->entries[i])) fn_8024EF30(obj->entries[i]);
    if (!MR::isDead(obj->childA0)) MR::emitEffect(obj->childA0, lbl_80696DA4);
}
void fn_8024E220(Actor4E0C0* obj) {
    if (!MR::isDead(obj->child94)) MR::emitEffect(obj->child94, lbl_80696DAC);
    for (s32 i = 0; i < 7; ++i) if (!MR::isDead(obj->entries[i])) fn_8024EF40(obj->entries[i]);
    if (!MR::isDead(obj->childA0)) MR::emitEffect(obj->childA0, lbl_80696DAC);
}
void fn_8024E2D0(Actor4E0C0* obj) {
    if (obj->flag14B) {
        for (s32 i = 0; i < 7; ++i) if (!MR::isDead(obj->entries[i])) fn_8024EF50(obj->entries[i]);
        if (!MR::isDead(obj->childA0)) MR::emitEffect(obj->childA0, lbl_80696DB4);
    }
}
void fn_8024E370(Actor4E0C0* obj) {
    for (s32 i = 0; i < 7; ++i) fn_8024EF60(obj->entries[i]);
    MR::deleteEffect(obj->childA0, lbl_80696DB4);
}
}
