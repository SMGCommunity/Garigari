#include "System/NerveExecutor.hpp"
struct Helper4E3E0 { const void* vtable; void* spine; f32 factor; };
extern "C" {
void* __ct__13NerveExecutorFPCc(void*, const char*);
extern const char lbl_80696DC0[];
extern const u32 lbl_80696E14[];
extern const f32 lbl_807DC6D0;
extern u32 lbl_807D3530;
Helper4E3E0* fn_8024E3E0(Helper4E3E0* obj) {
    __ct__13NerveExecutorFPCc(obj, lbl_80696DC0);
    obj->vtable = lbl_80696E14;
    obj->factor = lbl_807DC6D0;
    reinterpret_cast<NerveExecutor*>(obj)->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D3530), 0);
    return obj;
}
}
