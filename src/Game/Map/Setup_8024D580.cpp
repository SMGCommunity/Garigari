#include "LiveActor/LiveActor.hpp"
#include <JGeometry/TMatrix.hpp>
void* operator new(unsigned long);
namespace MR { void invalidateClipping(LiveActor*); }
struct Actor4D580 : LiveActor {
    u8 flag90;
    u8 padding91[3];
    LiveActor* child94;
    void* value98;
    LiveActor** entries;
    LiveActor* childA0;
    NameObj* childA4;
    TMtx34f matrixA8, matrixD8, matrix108;
    u8 opaque138[12];
    void* field144;
};
struct Config4D580 { u32 kind, field4; u16 index, padding; u32 fieldC, field10; };
extern "C" {
extern const char lbl_80696D34[], lbl_80696D44[], lbl_80696D5C[], lbl_80696D6C[], lbl_80696D78[], lbl_80696D8C[];
extern const char* lbl_80696CAC[];
extern const f32 lbl_807DC6E8, lbl_807DC6D4, lbl_807DC6EC;
LiveActor* fn_80036590(void*, const char*, const char*, const TMtx34f*);
LiveActor* fn_8024EDB0(void*, const char*, const TMtx34f*, const char*);
bool fn_8024C7A0(const void*);
u16 fn_8024C7B0(const void*);
LiveActor* fn_803555F0(const char*, u32);
Config4D580* fn_80355D20(Config4D580*, u32, u16, u32, u32);
LiveActor* fn_80355530(const char*, const Config4D580*);
void fn_80354EC0(void*, const TMtx34f*, const TVec3f&, const TVec3f&);
NameObj* fn_8046E330(void*, const char*);
void fn_8046E5E0(void*, void*);
void fn_8024D580(Actor4D580* obj) {
    obj->child94 = fn_80036590(obj, lbl_80696D34, lbl_80696D44, &obj->matrixA8);
    TVec3f& scale = obj->child94->mScale;
    scale.x = lbl_807DC6E8;
    scale.y = lbl_807DC6E8;
    scale.z = lbl_807DC6E8;
    obj->child94->makeActorDead();
}
void fn_8024D5F0(Actor4D580* obj) {
    for (u32 i = 0; i < 7; ++i) {
        void* allocation = ::operator new(0x94);
        LiveActor* child = static_cast<LiveActor*>(allocation);
        if (allocation) child = fn_8024EDB0(allocation, lbl_80696CAC[i], &obj->matrixD8, lbl_80696D5C);
        obj->entries[i] = child;
    }
}
void fn_8024D670(Actor4D580* obj) {
    if (obj->flag90 || !fn_8024C7A0(obj->value98)) obj->childA0 = fn_803555F0(lbl_80696D6C, 0);
    else {
        Config4D580 config;
        Config4D580* configured = fn_80355D20(&config, 0, (u16)fn_8024C7B0(obj->value98), 0x100, 0x21);
        obj->childA0 = fn_80355530(lbl_80696D6C, configured);
    }
    fn_80354EC0(obj->childA0, &obj->matrix108,
        TVec3f(lbl_807DC6D4, lbl_807DC6D4, lbl_807DC6D4),
        TVec3f(lbl_807DC6D4, lbl_807DC6D4, lbl_807DC6D4));
    TVec3f& scale = obj->childA0->mScale;
    scale.x = lbl_807DC6EC;
    scale.y = lbl_807DC6EC;
    scale.z = lbl_807DC6EC;
    obj->childA0->initEffectKeeper(0, lbl_80696D78, false);
    MR::invalidateClipping(obj->childA0);
    obj->childA0->makeActorDead();
}
void fn_8024D790(Actor4D580* obj) {
    void* allocation = ::operator new(0x3c);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_8046E330(allocation, lbl_80696D8C);
    obj->childA4 = child;
    child->initWithoutIter();
    fn_8046E5E0(obj->childA4, obj->field144);
}
}
