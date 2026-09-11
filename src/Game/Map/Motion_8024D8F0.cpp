#include "LiveActor/LiveActor.hpp"
#include "System/NerveExecutor.hpp"
#include <JGeometry/TVec.hpp>
#include <cmath>
extern "C" double __fabs(double);
namespace MR { void normalize(TVec3f*); }
struct Actor4D8F0 : LiveActor {
    u8 opaque90[0xc0];
    NerveExecutor* helper150;
    void* callback154;
    u8 flag158, flag159, flag15A, padding15B;
    TVec2f point15C;
    f32 speed164;
    u8 flag168, padding169[3];
    s32 duration16C, step170;
};
extern "C" {
extern const f32 lbl_807DC6D0, lbl_807DC6D4, lbl_807DC6D8, lbl_807DC6DC, lbl_807DC6E4;
extern const f32 lbl_807DC6F0, lbl_807DC6F4, lbl_807DC6F8, lbl_807DC6FC, lbl_807DC700, lbl_807DC704, lbl_807DC708;
extern const f64 lbl_80648B68;
extern u32 lbl_807D353C;
void fn_8024E960(NerveExecutor*);
bool fn_8005D350(u32);
const TVec2f* fn_8005D250(u32);
void fn_80055BE0(TVec2f*, const TVec2f*);
void fn_8001CF90(TVec3f*);
void fn_8001C8B0(TVec3f*, const TVec2f*, f32);
void fn_80037060(TVec3f*, const TVec3f*, const TVec3f*);
void fn_800D3010(const TVec3f*, const TVec3f&, TVec3f*);
f32 fn_80007B60(f32);
f32 PSVECMag(const Vec*);
f32 PSVECDistance(const Vec*, const Vec*);
void PSVECCrossProduct(const Vec*, const Vec*, Vec*);
bool fn_8024C7F0(const TVec3f&, const TVec3f&, const TVec3f&, f32);
}
ALWAYS_INLINE inline TVec3f sub4D8F0(const TVec3f& a, const TVec3f& b) {
    TVec3f result; fn_80037060(&result, &a, &b); return result;
}
inline TVec3f add4D8F0(const TVec3f& a, const TVec3f& b) { TVec3f result(a); fn_800D3010(&result, b, &result); return result; }
ALWAYS_INLINE inline TVec3f scaled4D8F0(const TVec3f& v, f32 scale) { TVec3f r(v); r.scale(scale); return r; }
extern "C" void fn_8024D8F0(Actor4D8F0* obj) {
    if (obj->duration16C > 0) {
        obj->speed164 = lbl_807DC6D4;
        ++obj->step170;
        f32 fraction = (f32)obj->step170 / (f32)obj->duration16C;
        fraction *= fraction;
        if (fraction > lbl_807DC6D0) fraction = lbl_807DC6D0;
        if (fraction < lbl_807DC6D4) fraction = lbl_807DC6D4;
        if (obj->step170 >= obj->duration16C) { obj->step170 = 0; obj->duration16C = 0; }
        f32 angle = lbl_807DC6F4 + (f32)fmod(lbl_807DC6F0 + (obj->mRotation.y - lbl_807DC6F4), lbl_80648B68);
        obj->mRotation.y = angle - angle * fraction;
        NerveExecutor* helper = obj->helper150;
        fn_8024E960(helper);
        helper->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D353C));
        return;
    }
    if (obj->flag168) return;
    if (fn_8005D350(0)) {
        TVec3f normal, ca, bc, ab, c, b, a;
        TVec3f center = add4D8F0(obj->mPosition, TVec3f(lbl_807DC6D4, lbl_807DC6E4, lbl_807DC6D4));
        TVec2f point; const TVec2f* input = fn_8005D250(0); point.x = input->x; point.y = input->y;
        if (obj->flag158) {
            fn_80055BE0(&obj->point15C, &point);
            obj->flag15A = obj->flag159; obj->flag158 = 0;
        }
        TVec3f origin; fn_8001CF90(&origin);
        TVec3f difference; fn_80037060(&difference, &center, &origin);
        f32 depth = lbl_807DC6E4 + PSVECMag(&difference);
        f32 dx = point.x - obj->point15C.x;
        f32 dy = point.y - obj->point15C.y;
        if (fn_80007B60((f32)dx * (f32)dx + dy * dy) < lbl_807DC6DC) {
            TVec3f current; fn_8001C8B0(&current, &point, depth);
            TVec3f direction; fn_80037060(&direction, &current, &origin);
            MR::normalize(&direction);
            TVec3f cross; PSVECCrossProduct(&difference, &direction, &cross);
            if (PSVECMag(&cross) < lbl_807DC6E4) obj->flag159 = 1;
        } else {
            TVec3f current; fn_8001C8B0(&current, &point, depth);
            TVec3f previous; fn_8001C8B0(&previous, &obj->point15C, depth);
            a = origin; b = current; c = previous;
            ab = sub4D8F0(current, origin);
            bc = sub4D8F0(previous, current);
            ca = sub4D8F0(origin, previous);
            PSVECCrossProduct(&bc, &ab, &normal); MR::normalize(&normal);
            bool hit;
            f32 distance = normal.dot(sub4D8F0(center, origin));
            if (__fabs(distance) >= lbl_807DC6E4) hit = false;
            else {
                TVec3f projected;
                projected = sub4D8F0(center, scaled4D8F0(normal, distance));
                TVec3f cross;
                bool inside;
                PSVECCrossProduct(sub4D8F0(projected, a), &ab, &cross);
                if (cross.dot(normal) < lbl_807DC6D4) inside = false;
                else {
                    PSVECCrossProduct(sub4D8F0(projected, b), &bc, &cross);
                    if (cross.dot(normal) < lbl_807DC6D4) inside = false;
                    else {
                        PSVECCrossProduct(sub4D8F0(projected, c), &ca, &cross);
                        inside = !(cross.dot(normal) < lbl_807DC6D4);
                    }
                }
                if (inside) hit = true;
                else if (PSVECDistance(&a, &center) <= lbl_807DC6E4) hit = true;
                else if (PSVECDistance(&b, &center) <= lbl_807DC6E4) hit = true;
                else if (PSVECDistance(&c, &center) <= lbl_807DC6E4) hit = true;
                else if (fn_8024C7F0(center, a, ab, lbl_807DC6E4)) hit = true;
                else if (fn_8024C7F0(center, b, bc, lbl_807DC6E4)) hit = true;
                else hit = fn_8024C7F0(center, c, ca, lbl_807DC6E4);
            }
            if (hit) obj->flag159 = 1;
        }
        if (obj->flag159) {
            TVec2f delta; delta.x = point.x - obj->point15C.x; delta.y = point.y - obj->point15C.y;
            TVec2f copy = delta;
            TVec2f movement; movement.x = copy.x; movement.y = copy.y;
            obj->speed164 += lbl_807DC6F8 * movement.x / obj->mScale.x;
            f32 speed = obj->speed164;
            obj->speed164 = speed < lbl_807DC6FC ? lbl_807DC6FC : speed > lbl_807DC700 ? lbl_807DC700 : speed;
        }
        obj->flag15A = obj->flag159;
        fn_80055BE0(&obj->point15C, &point);
    } else obj->flag158 = 1;
    obj->speed164 *= lbl_807DC704;
    if (obj->speed164 >= lbl_807DC6D4 && obj->speed164 < lbl_807DC6D8) obj->speed164 = lbl_807DC6D8;
    if (obj->speed164 < lbl_807DC6D4 && obj->speed164 > lbl_807DC708) obj->speed164 = lbl_807DC708;
    obj->mRotation.y = lbl_807DC6D4 + (f32)fmod(lbl_807DC6F0 + ((obj->mRotation.y + obj->speed164) - lbl_807DC6D4), lbl_80648B68);
    obj->flag159 = 0;
}
