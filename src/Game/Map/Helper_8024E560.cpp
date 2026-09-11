#include "System/NerveExecutor.hpp"
struct Actor4E560 { u8 opaque[0x164]; f32 speed; };
struct Helper4E560 { const void* vtable; void* spine; Actor4E560* actor; s32 duration, counter; };
namespace MR { bool isFirstStep(const NerveExecutor*); bool isGreaterEqualStep(const NerveExecutor*, s32); }
extern "C" {
void* __ct__13NerveExecutorFPCc(void*, const char*);
extern const char lbl_80696DE4[];
extern const u32 lbl_80696E08[];
extern u32 lbl_807D353C, lbl_807D3540, lbl_807D3544, lbl_807D3548;
extern const f32 lbl_807DC710, lbl_807DC714, lbl_807DC6DC;
double __fabs(double);
s32 fn_8003B4A0(s32, s32);
void fn_8024E8E0(Helper4E560*); void fn_8024E960(Helper4E560*); void fn_8024E9E0(Helper4E560*);
Helper4E560* fn_8024E560(Helper4E560* obj, Actor4E560* actor) {
    __ct__13NerveExecutorFPCc(obj, lbl_80696DE4);
    obj->vtable = lbl_80696E08;
    obj->actor = actor;
    obj->duration = 0; obj->counter = 0;
    reinterpret_cast<NerveExecutor*>(obj)->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D353C), 0);
    return obj;
}
void fn_8024E5D0(Helper4E560* obj) {
    NerveExecutor* executor = reinterpret_cast<NerveExecutor*>(obj);
    if (MR::isFirstStep(executor)) { obj->duration = fn_8003B4A0(180, 300); obj->counter = 0; }
    double speed = __fabs(obj->actor->speed);
    if (speed > lbl_807DC710) obj->counter += 2;
    else if (speed > lbl_807DC714) ++obj->counter;
    else obj->counter = 0;
    if (obj->counter > 180) executor->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3544));
    else if (MR::isGreaterEqualStep(executor, obj->duration)) executor->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3540));
}
void fn_8024E6B0(Helper4E560* obj) {
    NerveExecutor* executor = reinterpret_cast<NerveExecutor*>(obj);
    if (MR::isFirstStep(executor)) fn_8024E8E0(obj);
    if (MR::isGreaterEqualStep(executor, 10)) {
        fn_8024E960(obj);
        executor->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D353C));
    }
}
void fn_8024E720(Helper4E560* obj) {
    NerveExecutor* executor = reinterpret_cast<NerveExecutor*>(obj);
    if (MR::isFirstStep(executor)) { fn_8024E9E0(obj); obj->counter = 0; }
    ++obj->counter;
    if (__fabs(obj->actor->speed) > lbl_807DC6DC) obj->counter = 0;
    if (obj->counter > 60) executor->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3548));
}
}
