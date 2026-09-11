#include "LiveActor/LiveActor.hpp"
#include "Util/ActionSoundUtil.hpp"
namespace MR {
bool isFirstStep(const LiveActor*);
bool isLessStep(const LiveActor*, s32);
bool isStep(const LiveActor*, s32);
bool isGreaterEqualStep(const LiveActor*, s32);
void shakeCameraNormal();
}
struct Actor4D110 : LiveActor {
    u8 opaque90[0xd4];
    f32 field164;
    u8 opaque168;
    u8 flag169;
};
extern "C" {
extern const f32 lbl_807DC6D4;
extern const char lbl_80696CF4[], lbl_80696D20[];
extern u32 lbl_807D351C;
void fn_8024DFE0(void*);
void fn_8024E2D0(void*);
void fn_8024E220(void*);
void fn_8024E0C0(void*);
void fn_8004E100(void*, s32);
void fn_8024D110(Actor4D110* obj) {
    MR::isFirstStep(obj);
    if (MR::isLessStep(obj, 40)) MR::startActionSound(obj, lbl_80696CF4, -1, -1, -1);
    if (MR::isStep(obj, 40)) {
        MR::startActionSound(obj, lbl_80696D20, -1, -1, -1);
        fn_8024DFE0(obj);
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
