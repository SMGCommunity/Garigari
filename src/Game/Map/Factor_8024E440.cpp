#include "System/NerveExecutor.hpp"
struct Helper4E440 : NerveExecutor { f32 factor; };
namespace MR { bool isLessEqualStep(const NerveExecutor*, s32); void setNerveAtStep(NerveExecutor*, const Nerve*, s32); }
extern "C" {
extern const f32 lbl_807DC6E8, lbl_807DC6D0, lbl_807DC70C;
extern u32 lbl_807D3530, lbl_807D3538;
void fn_8024E440(Helper4E440* obj) {
    if (MR::isLessEqualStep(obj, 30)) {
        f32 fraction = (f32)obj->getNerveStep() / lbl_807DC6E8;
        obj->factor = obj->factor + fraction * (lbl_807DC6D0 - obj->factor);
    }
    MR::setNerveAtStep(obj, reinterpret_cast<const Nerve*>(&lbl_807D3530), 30);
}
void fn_8024E4D0(Helper4E440* obj) {
    if (MR::isLessEqualStep(obj, 30)) {
        f32 fraction = (f32)obj->getNerveStep() / lbl_807DC6E8;
        obj->factor = obj->factor + fraction * (lbl_807DC70C - obj->factor);
    }
    MR::setNerveAtStep(obj, reinterpret_cast<const Nerve*>(&lbl_807D3538), 30);
}
}
