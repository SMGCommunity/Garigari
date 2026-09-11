#include <revolution.h>
#include <JGeometry/TVec.hpp>
#include "Util/MtxUtil.hpp"
struct ShadowOvalDrawView { u8 opaque[0x18]; void* model; TVec3f size; u32 color; };
struct ShadowOvalHostView { u8 opaque[0x2C]; TVec3f scale; };
class ShadowController;
extern "C" {
ShadowController* fn_8023FAC0(const void*);
bool fn_8023F380(const ShadowController*);
bool fn_8023F3B0(const ShadowController*);
bool isFollowHostScale__16ShadowControllerCFv(const ShadowController*);
ShadowOvalHostView* fn_8023F0F0(const ShadowController*);
void fn_8023F260(const ShadowController*, TVec3f*);
void fn_8023F290(const ShadowController*, TVec3f*);
void fn_8023F120(const ShadowController*, MtxPtr);
void fn_805CDB40(int, const u32*);
void fn_800638E0(MtxPtr);
void fn_80022220(void*);
extern const f32 lbl_807DC538, lbl_807DC53C, lbl_807DC544;
}
inline void ovalMultiply(register Vec* size, register const Vec* scale) ALWAYS_INLINE {
    register f32 hostXY, z, xy, hostZ;
    asm {
        psq_l xy, 0(size), 0, 0
        psq_l hostXY, 0(scale), 0, 0
        lfs z, 8(size)
        ps_mul xy, xy, hostXY
        psq_st xy, 0(size), 0, 0
        lfs hostZ, 8(scale)
        fmuls hostZ, z, hostZ
        stfs hostZ, 8(size)
    }
}
extern "C" void fn_80240550(const ShadowOvalDrawView* obj) {
    ShadowController* controller = fn_8023FAC0(obj);
    if (!fn_8023F380(controller) || !fn_8023F3B0(controller)) return;
    Mtx matrix;
    TVec3f size(static_cast<const Vec&>(obj->size));
    f32 denominator = lbl_807DC53C;
    f32 factor = lbl_807DC538 / denominator;
    size.x *= factor; size.y *= factor; size.z *= factor;
    if (isFollowHostScale__16ShadowControllerCFv(controller)) {
        const TVec3f& scale = fn_8023F0F0(controller)->scale;
        ovalMultiply(&size, &scale);
    }
    TVec3f point, normal;
    fn_8023F260(controller, &point);
    fn_8023F290(controller, &normal);
    u32 color = obj->color;
    fn_805CDB40(4, &color);
    fn_8023F120(controller, matrix);
    MR::preScaleMtx(matrix, size);
    MR::flattenMtx(matrix, normal);
    matrix[0][3] = point.x; matrix[1][3] = point.y; matrix[2][3] = point.z;
    fn_800638E0(matrix); fn_80022220(obj->model);
    MR::preScaleMtx(matrix, lbl_807DC544);
    fn_800638E0(matrix); fn_80022220(obj->model);
    MR::preScaleMtx(matrix, lbl_807DC544);
    fn_800638E0(matrix); fn_80022220(obj->model);
    u32 resetColor = 0x80;
    fn_805CDB40(4, &resetColor);
}
