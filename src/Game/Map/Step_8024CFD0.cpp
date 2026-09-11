#include "LiveActor/LiveActor.hpp"
#include "Util/ActionSoundUtil.hpp"
namespace MR {
bool isFirstStep(const LiveActor*);
bool isLessStep(const LiveActor*, s32);
bool isStep(const LiveActor*, s32);
bool isGreaterEqualStep(const LiveActor*, s32);
void shakeCameraNormal();
}
struct Actor4CFD0 : LiveActor {
    u8 opaque90[0xc8];
    u8 flag158;
    u8 opaque159[11];
    f32 field164;
    u8 flag168;
    u8 padding169[3];
    void* field16C;
    u32 field170;
};
extern "C" {
extern const f32 lbl_807DC6D4;
extern const char lbl_80696CF4[], lbl_80696D0C[];
extern u32 lbl_807D3518;
void fn_8024E170(void*);
void fn_8024DF60(void*);
void fn_8004E100(void*, s32);
void fn_8024CFD0(Actor4CFD0* obj) { obj->flag168 = 0; }
void fn_8024CFE0(Actor4CFD0* obj) {
    obj->flag168 = 1;
    obj->flag158 = 1;
    obj->field164 = lbl_807DC6D4;
}
void fn_8024D000(Actor4CFD0* obj, void* value) { obj->field16C = value; obj->field170 = 0; }
void fn_8024D010(Actor4CFD0* obj) { obj->flag158 = 1; }
void fn_8024D020(Actor4CFD0* obj) {
    MR::isFirstStep(obj);
    if (MR::isLessStep(obj, 40)) MR::startActionSound(obj, lbl_80696CF4, -1, -1, -1);
    if (MR::isStep(obj, 40)) {
        MR::startActionSound(obj, lbl_80696D0C, -1, -1, -1);
        fn_8024E170(obj);
        fn_8024DF60(obj);
        fn_8004E100(obj, 0);
        MR::shakeCameraNormal();
    }
    if (MR::isGreaterEqualStep(obj, 40)) {
        obj->mRotation.y = lbl_807DC6D4;
        obj->field164 = lbl_807DC6D4;
    }
    if (MR::isStep(obj, 60)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3518));
}
}
