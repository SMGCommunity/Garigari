#include "LiveActor/LiveActor.hpp"
#include "Util/ActionSoundUtil.hpp"
namespace MR {
bool isFirstStep(const LiveActor*);
bool isLessStep(const LiveActor*, s32);
bool isStep(const LiveActor*, s32);
bool isGreaterEqualStep(const LiveActor*, s32);
void shakeCameraNormal();
}
struct Actor4D220 : LiveActor {
    u8 opaque90[8];
    void* value98;
    void* field9C;
    LiveActor* childA0;
    u8 opaqueA4[0xc0];
    f32 field164;
    u8 opaque168;
    u8 flag169;
};
struct Config4D220 { u32 kind, field4; u16 index, padding; u32 fieldC, field10; };
extern "C" {
u16 fn_8024C7B0(const void*);
Config4D220* fn_80355D20(Config4D220*, u32, u16, u32, u32);
void fn_80354F50(void*, const Config4D220*);
extern const f32 lbl_807DC6D4;
extern const char lbl_80696CF4[], lbl_80696D20[];
extern u32 lbl_807D351C;
void fn_8024E030(void*);
void fn_8024E2D0(void*);
void fn_8024E220(void*);
void fn_8024E0C0(void*);
void fn_8004E100(void*, s32);
void fn_8024D220(Actor4D220* obj) {
    MR::isFirstStep(obj);
    if (MR::isLessStep(obj, 40)) MR::startActionSound(obj, lbl_80696CF4, -1, -1, -1);
    if (MR::isStep(obj, 39)) {
        Config4D220 config;
        Config4D220* configured = fn_80355D20(&config, 0, (u16)fn_8024C7B0(obj->value98), 0x100, 0x21);
        fn_80354F50(obj->childA0, configured);
    }
    if (MR::isStep(obj, 40)) {
        MR::startActionSound(obj, lbl_80696D20, -1, -1, -1);
        fn_8024E030(obj);
        obj->childA0->makeActorAppeared();
        fn_8024E2D0(obj);
        if (obj->flag169) fn_8024E220(obj);
        else fn_8024E0C0(obj);
        fn_8004E100(obj, 0);
        MR::shakeCameraNormal();
    }
    if (MR::isGreaterEqualStep(obj, 40)) {
        obj->mRotation.y = lbl_807DC6D4;
        obj->field164 = lbl_807DC6D4;
    }
    if (MR::isStep(obj, 150)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D351C));
}
}
