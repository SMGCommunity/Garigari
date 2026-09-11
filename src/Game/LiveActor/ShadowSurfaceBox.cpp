#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowBoxDrawView { u8 opaque[0x18]; TVec3f size; };
struct ShadowBoxHostView { u8 opaque[0x2C]; TVec3f scale; };
class ShadowController;
extern "C" {
    ShadowController* fn_8023FAC0(const void*);
    bool fn_8023F380(const ShadowController*);
    bool fn_8023F3B0(const ShadowController*);
    bool isFollowHostScale__16ShadowControllerCFv(const ShadowController*);
    void fn_8023F120(const ShadowController*, Mtx);
    void fn_8023F290(const ShadowController*, TVec3f*);
    void fn_8023F260(const ShadowController*, TVec3f*);
    ShadowBoxHostView* fn_8023F0F0(const ShadowController*);
    void fn_800638E0(const Mtx);
    void fn_805CC730(int, int, int);
    void* fn_8023FB40(void*, int);
    extern f32 lbl_807DC518, lbl_807DC51C, lbl_807DC520, lbl_807DC524;
}
inline void boxColumn(TVec3f& out, const Mtx matrix, int column) ALWAYS_INLINE {
    f32 z = matrix[2][column];
    f32 y = matrix[1][column];
    f32 x = matrix[0][column];
    out.set<f32>(x, y, z);
}
// Paired-single component multiplication, following the existing JMath primitives.
inline void boxMultiply(register Vec* a, register const Vec* b) ALWAYS_INLINE {
    register f32 bxy, axy, az, bz;
    asm {
        psq_l axy, 0(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        lfs az, 8(a)
        lfs bz, 8(b)
        ps_mul axy, axy, bxy
        fmuls bz, az, bz
        psq_st axy, 0(a), 0, 0
        stfs bz, 8(a)
    }
}
inline void boxAdd(register Vec* a, register const Vec* b) ALWAYS_INLINE {
    register f32 bz, az, sumZ, sumXY, bxy, axy;
    asm {
        psq_l axy, 0(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        psq_l az, 8(a), 1, 0
        psq_l bz, 8(b), 1, 0
        ps_add sumXY, axy, bxy
        psq_st sumXY, 0(a), 0, 0
        ps_add sumZ, az, bz
        psq_st sumZ, 8(a), 1, 0
    }
}
inline const TVec3f& boxHostScale(const ShadowController* controller) ALWAYS_INLINE {
    return fn_8023F0F0(controller)->scale;
}
extern "C" void fn_8023FBC0(const ShadowBoxDrawView* obj) {
    ShadowController* controller = fn_8023FAC0(obj);
    if (!fn_8023F380(controller) || !fn_8023F3B0(controller)) return;
    Mtx model, projected;
    TVec3f x, y, z, normal;
    fn_8023F120(controller, model);
    boxColumn(x, model, 0);
    boxColumn(y, model, 1);
    boxColumn(z, model, 2);
    fn_8023F290(controller, &normal);
    f32 dx = normal.dot(x);
    f32 dy = normal.dot(y);
    f32 dz = normal.dot(z);
    TVec3f halfSize(obj->size);
    TVec3f point;
    if (isFollowHostScale__16ShadowControllerCFv(controller)) {
        TVec3f scale(boxHostScale(controller));
        scale.scale(lbl_807DC520);
        boxMultiply(&halfSize, &scale);
    } else {
        halfSize.scale(lbl_807DC520);
    }
    TVec3f xProjection(normal); xProjection.scale(dx); x -= xProjection;
    TVec3f yProjection(normal); yProjection.scale(dy); y -= yProjection;
    TVec3f zProjection(normal); zProjection.scale(dz); z -= zProjection;
    x.scale(halfSize.x); y.scale(halfSize.y); z.scale(halfSize.z);
    projected[0][0] = x.x; projected[1][0] = x.y; projected[2][0] = x.z;
    projected[0][1] = y.x; projected[1][1] = y.y; projected[2][1] = y.z;
    projected[0][2] = z.x; projected[1][2] = z.y; projected[2][2] = z.z;
    fn_8023F260(controller, &point);
    TVec3f translated(point);
    boxAdd(&translated, &normal);
    projected[0][3] = translated.x;
    projected[1][3] = translated.y;
    projected[2][3] = translated.z;
    fn_800638E0(projected);
    dx = dx >= lbl_807DC51C ? lbl_807DC518 : lbl_807DC524;
    dy = dy >= lbl_807DC51C ? lbl_807DC518 : lbl_807DC524;
    dz = dz >= lbl_807DC51C ? lbl_807DC518 : lbl_807DC524;
    volatile f32* fifo = reinterpret_cast<volatile f32*>(0xCC008000);
    volatile u32* colorFifo = reinterpret_cast<volatile u32*>(0xCC008000);
    fn_805CC730(0x80, 0, 4);
    *fifo = dx; *fifo = -dx; *fifo = lbl_807DC524; *colorFifo = 0x80; *fifo = dx; *fifo = -dx; *fifo = lbl_807DC518; *colorFifo = 0x80;
    *fifo = dx; *fifo = dx; *fifo = lbl_807DC518; *colorFifo = 0x80; *fifo = dx; *fifo = dx; *fifo = lbl_807DC524; *colorFifo = 0x80;
    fn_805CC730(0x80, 0, 4);
    *fifo = lbl_807DC524; *fifo = dy; *fifo = -dy; *colorFifo = 0x80; *fifo = lbl_807DC518; *fifo = dy; *fifo = -dy; *colorFifo = 0x80;
    *fifo = lbl_807DC518; *fifo = dy; *fifo = dy; *colorFifo = 0x80; *fifo = lbl_807DC524; *fifo = dy; *fifo = dy; *colorFifo = 0x80;
    fn_805CC730(0x80, 0, 4);
    *fifo = -dz; *fifo = lbl_807DC524; *fifo = dz; *colorFifo = 0x80; *fifo = -dz; *fifo = lbl_807DC518; *fifo = dz; *colorFifo = 0x80;
    *fifo = dz; *fifo = lbl_807DC518; *fifo = dz; *colorFifo = 0x80; *fifo = dz; *fifo = lbl_807DC524; *fifo = dz; *colorFifo = 0x80;
}
