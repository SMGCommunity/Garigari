#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowCircleView { const void* vtable; u8 opaque[0x14]; f32 radius; };
struct ShadowCircleHostView { u8 opaque[0x2C]; f32 scale; };
class ShadowController;
extern "C" {
    void* fn_80240390(void*, const char*);
    void* fn_8023FB40(void*, int);
    extern const char lbl_80695A60[];
    extern void (*const lbl_80695A70[])();
    extern const f32 lbl_807DC530, lbl_807DC534;
    ShadowController* fn_8023FAC0(const void*);
    bool fn_8023F380(const ShadowController*);
    bool fn_8023F3B0(const ShadowController*);
    bool isFollowHostScale__16ShadowControllerCFv(const ShadowController*);
    ShadowCircleHostView* fn_8023F0F0(const ShadowController*);
    void fn_8023F260(const ShadowController*, TVec3f*);
    void fn_8023F290(const ShadowController*, TVec3f*);
    void fn_80063930();
    void fn_80064300(const TVec3f&, const TVec3f&, f32, int, int);
}
inline TVec3f circleOffset(const TVec3f& normal) ALWAYS_INLINE {
    TVec3f result(normal);
    result.x *= lbl_807DC530;
    result.y *= lbl_807DC530;
    result.z *= lbl_807DC530;
    return result;
}
// Component-wise addition using compiler-assigned paired-single operands.
inline void circleAdd(register Vec* destination, register const Vec* offset) ALWAYS_INLINE {
    register f32 rightZ, leftZ, sumZ, sumXY, rightXY, leftXY;
    asm {
        psq_l leftXY, 0(destination), 0, 0
        psq_l rightXY, 0(offset), 0, 0
        psq_l rightZ, 8(offset), 1, 0
        ps_add sumXY, leftXY, rightXY
        psq_l leftZ, 8(destination), 1, 0
        ps_add sumZ, leftZ, rightZ
        psq_st sumXY, 0(destination), 0, 0
        psq_st sumZ, 8(destination), 1, 0
    }
}
inline TVec3f circlePosition(const TVec3f& point, const TVec3f& offset) ALWAYS_INLINE {
    TVec3f result(point);
    circleAdd(&result, &offset);
    return result;
}
inline TVec3f circleNegated(const TVec3f& normal) ALWAYS_INLINE {
    TVec3f result;
    JMathInlineVEC::PSVECNegate(&normal, &result);
    return result;
}
extern "C" void fn_802400C0(const ShadowCircleView* obj) {
    ShadowController* controller = fn_8023FAC0(obj);
    if (!fn_8023F380(controller) || !fn_8023F3B0(controller)) return;
    {
        f32 radius = obj->radius;
        if (isFollowHostScale__16ShadowControllerCFv(controller))
            radius *= fn_8023F0F0(controller)->scale;
        TVec3f point, normal;
        fn_8023F260(controller, &point);
        fn_8023F290(controller, &normal);
        fn_80063930();
        TVec3f center = circlePosition(point, circleOffset(normal));
        fn_80064300(center, circleNegated(normal), radius, 0x80, 0x14);
    }
}
