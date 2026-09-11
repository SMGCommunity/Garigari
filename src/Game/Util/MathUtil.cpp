#include "Util/MtxUtil.hpp"
#include "Util/MathUtil.hpp"
#include <revolution.h>
#include <cmath>
#include "System/GameSystem.hpp"
#include "System/GameSystemObjHolder.hpp"

// Retain the zero vector at the start of this translation unit's constant pool.
#pragma force_active on
static const Vec gZeroVec = {0.0f, 0.0f, 0.0f};
#pragma force_active reset

namespace {
    f32* gAcosTable;
};

namespace MR {
    void initAcosTable() {
        gAcosTable = new f32[0x100];
        u32 i = 0;

        do {
            f64 v7 = 0.02 * (i / 255.0) + 0.98;
            if (v7 > 1.0) {
                v7 = 1.0;
            }
            gAcosTable[i++] = acos(v7);
        } while (i < 0x100);
    }







    void repeatDegree(f32* value) {
        *value = repeat(*value, 0.0f, 360.0f);
    }

    f32 repeatDegree(f32 value) {
        return repeat(value, 0.0f, 360.0f);
    }




};

// This specialization is an out-of-line call in the original MathUtil object.
template <> void JGeometry::TVec3<f32>::set<f32>(const JGeometry::TVec3<f32>&) NO_INLINE;
extern "C" void fn_805C8AC0(const Vec*, Vec*);
namespace MR {
    void normalize(TVec3f* v) { fn_805C8AC0(v, v); }
    void normalize(TVec3f* dst, const TVec3f& src) {
        dst->set<f32>(src);
        fn_805C8AC0(dst, dst);
    }
    bool isNearZero(f32 value, f32 epsilon) NO_INLINE {
        if (value < 0.0f) value = -value;
        if (value < epsilon) return true;
        return false;
    }
    f32 lerp(f32 a, f32 b, f32 t) { return a + t * (b - a); }
    void vecBlend(TVec3f* dst, const TVec3f& a, const TVec3f& b, f32 t) {
        PSvecBlend(&a, &b, dst, 1.0f - t, t);
    }
    void sortSmall(long count, unsigned long* values, long* indices) {
        for (long i = 0; i < count; ++i) indices[i] = i;
        unsigned long original;
        for (long i = 0; i < count; ++i) {
            original = values[i];
            unsigned long minimum = original;
            long smallest = i;
            for (long j = i + 1; j < count; ++j) {
                if (minimum > values[j]) { minimum = values[j]; smallest = j; }
            }
            long index = indices[i];
            indices[i] = indices[smallest];
            values[i] = minimum;
            indices[smallest] = index;
            values[smallest] = original;
        }
    }
}

// Original names are not yet recovered; address labels preserve symbol identity.
extern "C" {
    extern GameSystem* lbl_807D0DA4;
    // LCG and float conversion adapted from Petari's MR::getRandom (CC0).
    f32 fn_8003B3F0() NO_INLINE {
        GameSystemObjHolder* holder = lbl_807D0DA4->mObjHolder;
        u32 random = holder->mRandomSeed = 0x19660d * holder->mRandomSeed + 0x3c6ef35f;
        u32 bits = (random >> 9) | 0x3f800000;
        return reinterpret_cast<f32&>(bits) - 1.0f;
    }

    f32 fn_8003B440(f32 low, f32 high) NO_INLINE {
        return low + (high - low) * fn_8003B3F0();
    }
    // Adapted from Petari MathUtil.cpp (CC0): retain the range helper's evaluation order.
    inline f32 randomInRange(f32 low, f32 high) {
        return low + (high - low) * fn_8003B3F0();
    }
    s32 fn_8003B4A0(s32 low, s32 high) {
        return randomInRange(static_cast<f32>(low), static_cast<f32>(high));
    }
    f32 fn_8003B540() NO_INLINE { return randomInRange(0.0f, 360.0f); }
    bool fn_8003B570() NO_INLINE { return fn_8003B3F0() < 0.5f; }
    f32 fn_8003B5A0() NO_INLINE { return fn_8003B570() ? -1.0f : 1.0f; }
    f32 fn_8003B820(f32 t, f32 low, f32 high) { return low + t * (high - low); }
    f32 fn_8003B830(f32 t, f32 low, f32 high, f32 duration) {
        t /= duration;
        return low + t * (high - low);
    }
    f32 fn_8003B8E0(f32 value, f32 low, f32 high) NO_INLINE {
        if (value < low) return low;
        if (value > high) return high;
        return value;
    }
    f32 fn_8003DA40(f32 value) {
        if (0.0f < value) return 1.0f;
        if (value < 0.0f) return -1.0f;
        return 0.0f;
    }
    void fn_8003DA70(f32* a, f32* b) {
        f32 value = *a;
        *a = *b;
        *b = value;
    }
    struct Float4 { f32 x, y, z, w; };
    void fn_8003CE80(Float4* dst, const Float4* src) NO_INLINE {
        dst->x = src->x; dst->y = src->y; dst->z = src->z; dst->w = src->w;
    }
}

inline TVec3f randomOffsetVector(f32 range) {
    f32 x = randomInRange(-range, range);
    f32 y = randomInRange(-range, range);
    f32 z = randomInRange(-range, range);
    TVec3f offset;
    offset.x = x;
    offset.y = y;
    offset.z = z;
    return offset;
}

extern "C" {
    // Adapted from Petari's random-vector routines (CC0), with Galaxy 2 symbols.
    void fn_8003B5E0(TVec3f* dst, f32 range) {
        dst->set<f32>(randomInRange(-range, range), randomInRange(-range, range), randomInRange(-range, range));
    }
    void fn_8003B690(TVec3f* dst, const TVec3f& src, f32 range) NO_INLINE {
        dst->set<f32>(src.addInline(randomOffsetVector(range)));
    }
}

extern "C" {
    f32 __fabsf(f32);
    f32 fn_8003B1A0(f32);
    // Petari acosEx structure, checked against the Galaxy 2 lookup sequence.
    f32 fn_8003B350(f32 x) {
        if (__fabsf(x) < 0.98f) {
            return fn_8003B1A0(x);
        } else if (x < 0.0f) {
            u32 index = static_cast<u32>((-x - 0.98f) * 50.0f * 255.0f);
            f32 angle = gAcosTable[index];
            return PI - angle;
        } else {
            u32 index = static_cast<u32>((x - 0.98f) * 50.0f * 255.0f);
            return gAcosTable[index];
        }
    }
}

inline f32 acosHalfPi() { return HALF_PI; }
extern "C" {
    extern f32 lbl_8074F9E0[];
    f32 fn_8003B1A0(f32 x) NO_INLINE {
        if (x >= 1.0f) return 0.0f;
        if (x <= -1.0f) return PI;
        if (x < 0.0f) {
            u32 index = static_cast<u32>(1023.5f * -x);
            f32 angle = lbl_8074F9E0[index];
            return angle + acosHalfPi();
        }
        u32 index = static_cast<u32>(1023.5f * x);
        f32 angle = lbl_8074F9E0[index];
        return HALF_PI - angle;
    }
}

extern "C" {
    // Component-wise near-zero predicate; deliberately preserve NaN comparison behavior.
    bool fn_8003F1A0(const TVec3f* v, f32 tolerance) NO_INLINE {
        if (v->x > tolerance) return false;
        if (v->x < -tolerance) return false;
        if (v->y > tolerance) return false;
        if (v->y < -tolerance) return false;
        if (v->z > tolerance) return false;
        return !(v->z < -tolerance);
    }
    void fn_8000DBB0(TVec3f*);
}
namespace MR {
    bool normalizeOrZero(TVec3f* v) NO_INLINE {
        if (fn_8003F1A0(v, 0.001f)) {
            fn_8000DBB0(v);
            return true;
        }
        fn_805C8AC0(v, v);
        return false;
    }
}
extern "C" {
    bool fn_8003E630(TVec3f* dst, const TVec3f& src) {
        dst->set<f32>(src);
        return MR::normalizeOrZero(dst);
    }
    f32 fn_8003E670(f32, f32, f32);
    f32 fn_8003E720(f32 value, f32 low, f32 high) {
        if (value >= 0.0f) return fn_8003E670(value, low, high);
        return -fn_8003E670(-value, low, high);
    }
    typedef TVec2f Float2;
    f32 fn_8003E820(const Float2* a, const Float2* b) NO_INLINE {
        return a->x * b->x + a->y * b->y;
    }
    s32 fn_8003FE80(const f32*);
    s32 fn_8003FED0(const f32*);
    f32 fn_8003FE00(const f32* values) { return values[fn_8003FE80(values)]; }
    f32 fn_8003FE40(const f32* values) { return values[fn_8003FED0(values)]; }
}

extern "C" {
    f32 fn_8003E670(f32 value, f32 low, f32 high) NO_INLINE {
        f32 range = high - low;
        if (MR::isNearZero(range, 0.001f)) {
            if (value < low) return 0.0f;
            return 1.0f;
        }
        return (fn_8003B8E0(value, low, high) - low) / range;
    }
    s32 fn_8003FE80(const f32* v) NO_INLINE {
        if (v[0] > v[1] && v[0] > v[2]) return 0;
        if (v[1] > v[2]) return 1;
        return 2;
    }
    s32 fn_8003FED0(const f32* v) NO_INLINE {
        f32 x = __fabsf(v[0]);
        f32 y = __fabsf(v[1]);
        f32 z = __fabsf(v[2]);
        if (x > y && x > z) return 0;
        if (y > z) return 1;
        return 2;
    }
    f32 fn_8003FF20(const TVec3f* a, const TVec3f& b) {
        return fn_8003B1A0(a->dot(b));
    }
}

inline f32 easingPi() { return PI; }
extern "C" {
    f32 PSVECMag(const Vec*);
    void fn_80011BB0(TVec3f*, f32);
    void fn_8003B770(TVec3f* dst, const TVec3f& src, f32 range) {
        f32 length = PSVECMag(&src);
        fn_8003B690(dst, src, range);
        if (fn_8003F1A0(dst, 0.001f)) {
            dst->set<f32>(src);
        } else {
            fn_80011BB0(dst, length);
        }
    }
    f32 fn_8003B850(f32 x, f32 low, f32 high, f32 start, f32 end) {
        f32 t = (fn_8003B8E0(x, low, high) - low) / (high - low);
        return start + t * (end - start);
    }
    // Shared easing formulas from Petari, validated independently for Galaxy 2.
    f32 fn_8003B9C0(f32 x, f32 start, f32 end, f32 duration) NO_INLINE {
        f32 t = 1.0f - JMACosRadian(x / duration * easingPi() / 2.0f);
        return start + t * (end - start);
    }
    f32 fn_8003BA80(f32 x, f32 start, f32 end, f32 duration) NO_INLINE {
        f32 t = JMASinRadian(x / duration * easingPi() / 2.0f);
        return start + t * (end - start);
    }
    f32 fn_8003BB60(f32 x, f32 start, f32 end, f32 duration) NO_INLINE {
        f32 angle = x / duration * easingPi();
        f32 t = (1.0f - JMACosRadian(angle)) / 2.0f;
        return start + t * (end - start);
    }
    f32 fn_8003B900(f32 x, f32 low, f32 high, f32 start, f32 end) {
        return fn_8003B9C0(fn_8003E670(x, low, high), start, end, 1.0f);
    }
    f32 fn_8003B960(f32 x, f32 low, f32 high, f32 start, f32 end) {
        return fn_8003BB60(fn_8003E670(x, low, high), start, end, 1.0f);
    }
    f32 fn_8003BBD0(f32 x, f32 duration) {
        f32 t;
        if (MR::isNearZero(duration, 0.001f)) t = 1.0f;
        else t = 2.0f * x / duration - 1.0f;
        return 1.0f - t * t;
    }
}

extern "C" {
    void fn_8003BF50(TVec3f* side, TVec3f* up, const TVec3f& front, const TVec3f& axis) {
        PSVECCrossProduct(&axis, &front, side);
        fn_805C8AC0(side, side);
        PSVECCrossProduct(&front, side, up);
    }
    void fn_8003BFC0(TVec3f* up, TVec3f* side, const TVec3f& front, const TVec3f& axis) {
        PSVECCrossProduct(&front, &axis, up);
        fn_805C8AC0(up, up);
        PSVECCrossProduct(up, &front, side);
    }
    void fn_8003C0A0(TVec3f* front, TVec3f* side, const TVec3f& up, const TVec3f& axis) {
        PSVECCrossProduct(&axis, &up, front);
        fn_805C8AC0(front, front);
        PSVECCrossProduct(&up, front, side);
    }
}
namespace MR {
    void makeAxisUpFront(TVec3f* side, TVec3f* front, const TVec3f& up, const TVec3f& axis) {
        PSVECCrossProduct(&up, &axis, side);
        fn_805C8AC0(side, side);
        PSVECCrossProduct(side, &up, front);
    }
}

extern "C" {
    f32 fn_8003BC50(f32 x, f32 rise, f32 hold, f32 fall) {
        if (x < rise) {
            f32 t;
            if (MR::isNearZero(rise, 0.001f)) t = 0.0f;
            else t = x / rise - 1.0f;
            return 1.0f - t * t;
        }
        f32 end = rise + hold;
        if (x < end) return 1.0f;
        f32 t;
        if (MR::isNearZero(fall, 0.001f)) t = 1.0f;
        else t = (x - end) / fall;
        return 1.0f - t * t;
    }
    f32 fn_8003BD30(f32 x, f32 rate, f32 amplitude) {
        if (x < 0.5f) {
            return fn_8003BA80(x * 2.0f, 0.0f, 1.0f, 1.0f);
        }
        f32 t = (x - 0.5f) * 2.0f;
        return 1.0f + (1.0f - JMACosRadian(easingPi() * rate * t)) * (1.0f - t) * amplitude;
    }
    f32 fn_8003BDD0(f32 x, f32 start, f32 end, f32 dampScale, f32 rate) {
        f32 vibWeight = (x * x) * (x * x);
        f32 t1 = 1.0f - x;
        f32 convergeWeight = (t1 * t1) * (t1 * t1);
        f32 dampRatio = dampScale * t1;
        f32 vibration = JMASinRadian(PI * (x + rate * vibWeight));
        return start + ((1.0f - convergeWeight) + vibration * dampRatio) * (end - start);
    }
    f32 fn_8003BE80(f32 x, f32 time, f32 base, f32 amplitude, f32 freq) {
        f32 vibMax = base + amplitude;
        f32 vib = JMACosRadian(x * (1.0f / freq * PI));
        f32 vibration = (amplitude * 0.5f) * (vib - 1.0f);
        if (x >= time) return vibration + vibMax;
        f32 t = x - time;
        f32 reduce = (1.0f - vibMax) * (1.0f / (time * time)) * t * t;
        f32 reducedBase = vibMax + reduce;
        return reducedBase + vibration;
    }
    void fn_8003C110(TVec3f* dst, const TVec3f& axis) NO_INLINE {
        TVec3f front(0.0f, 0.0f, 1.0f);
        JMAVECScaleAdd(&axis, &front, dst, -axis.dot(front));
        if (fn_8003F1A0(dst, 0.001f)) {
            TVec3f side(1.0f, 0.0f, 0.0f);
            JMAVECScaleAdd(&axis, &side, dst, -axis.dot(side));
        }
        fn_805C8AC0(dst, dst);
    }
    void fn_8003C220(TVec3f* dst, TVec3f* cross, const TVec3f& axis) {
        fn_8003C110(dst, axis);
        PSVECCrossProduct(dst, &axis, cross);
        MR::normalizeOrZero(cross);
    }
}

extern "C" {
    f32 fn_8003DBB0(f32 x, f32 low, f32 high) {
        return fn_8003B8E0(fn_8003E670(x, low, high), 0.0f, 1.0f);
    }
    bool fn_8003F220(const Float2* v, f32 epsilon) NO_INLINE {
        if (v->x > epsilon) return false;
        if (v->x < -epsilon) return false;
        if (v->y > epsilon) return false;
        return !(v->y < -epsilon);
    }
    f32 fn_8003E760(f32 angle) NO_INLINE {
        for (;;) {
            bool negative = angle < 0.0f;
            if (negative) angle += TWO_PI;
            else if (angle > TWO_PI) angle -= TWO_PI;
            else return angle;
        }
    }
    f32 fn_8003F280(f32 a, f32 b) {
        f32 delta = fn_8003E760(a - b);
        if (delta > PI) delta = TWO_PI - delta;
        return delta;
    }
    f32 fn_80040B20(f32 x, f32 y) { return fmod(x, y); }
    void fn_8003DA90(s16* dst, const TVec3f& src, s32 fractionalBits) {
        f32 scale = static_cast<f32>(1 << fractionalBits);
        s16 z, y, x;
        x = src.x * scale;
        y = src.y * scale;
        z = src.z * scale;
        dst[0] = x;
        dst[1] = y;
        dst[2] = z;
    }
}

extern "C" {
    void fn_8003DB10(TVec3f* dst, const s16* src, s32 fractionalBits) {
        f32 scale = 1.0f / static_cast<f32>(1 << fractionalBits);
        f32 x = src[0] * scale;
        f32 y = src[1] * scale;
        f32 z = src[2] * scale;
        dst->x = x;
        dst->y = y;
        dst->z = z;
    }
    void fn_8003E840(f32* length, TVec3f* direction, const TVec3f& src) {
        *length = PSVECMag(&src);
        if (fn_8003F1A0(&src, 0.001f)) {
            fn_8000DBB0(direction);
        } else {
            direction->set<f32>(src);
            fn_805C8AC0(direction, direction);
        }
    }
}

namespace MR {
    void normalize(TVec2f* dst) NO_INLINE {
        TVec3f tmp(dst->x, dst->y, 0.0f);
        fn_805C8AC0(&tmp, &tmp);
        dst->x = tmp.x;
        dst->y = tmp.y;
    }
    void normalize(TVec2f* dst, const TVec2f& src) NO_INLINE {
        f32 y, x;
        x = src.x;
        y = src.y;
        dst->x = x;
        dst->y = y;
        normalize(dst);
    }
    bool normalizeOrZero(TVec2f* dst) NO_INLINE {
        if (fn_8003F220(dst, 0.001f)) {
            dst->x = dst->y = 0.0f;
            return true;
        }
        normalize(dst);
        return false;
    }
}
extern "C" {
    f32 fn_80007B60(f32);
    void fn_8003E7A0(f32* length, TVec2f* direction, const TVec2f& src) {
        *length = fn_80007B60(fn_8003E820(&src, &src));
        if (fn_8003F220(&src, 0.001f)) direction->x = direction->y = 0.0f;
        else MR::normalize(direction, src);
    }
}

extern "C" {
    void fn_8003E1E0(TVec3f* dst, const TVec3f& src, const TVec3f& axis, f32 degrees) {
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, degrees * PI_180);
        rotation.mult(src, *dst);
    }
    void fn_8003E260(TVec3f* dst, const TVec3f& axis, f32 radians) {
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, radians);
        rotation.mult(*dst, *dst);
    }
}
namespace MR {
    void rotateVecDegree(TVec3f* dst, const TVec3f& axis, f32 degrees) {
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, degrees * PI_180);
        rotation.mult(*dst, *dst);
    }
}

extern "C" {
    void fn_8003E2D0(TVec3f* dst, const TVec3f& src, const TVec3f& axis, f32 radians) {
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, radians);
        rotation.mult(src, *dst);
    }
    void fn_8003E340(TVec3f* dst, const TVec3f& src, const TVec3f& axis, f32 low, f32 high) NO_INLINE {
        f32 degrees = MR::repeat(randomInRange(low, high), 0.0f, 360.0f);
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, degrees * PI_180);
        rotation.mult(src, *dst);
    }
    void fn_8003C1D0(TVec3f* dst, const TVec3f& axis) {
        fn_8003C110(dst, axis);
        fn_8003E340(dst, *dst, axis, 0.0f, 360.0f);
    }
}

namespace MR {
    u8 lerp(u8 start, u8 end, f32 t) NO_INLINE {
        return fn_8003B8E0(start + t * (end - start), 0.0f, 255.0f);
    }
}
extern "C" {
    bool fn_80040600(const TVec3f* v, f32 tolerance) {
        return __fabsf(1.0f - PSVECMag(v)) <= tolerance;
    }
    void fn_80040650(u32* words) {
        words[0] = 0xffffffff;
        words[1] = 0xffffffff;
        words[2] = 0xffffffff;
    }
    s32 fn_806317CC(f32);
    bool fn_80040670(const TVec3f* v) {
        if (fn_806317CC(v->x) == 1 || fn_806317CC(v->y) == 1 || fn_806317CC(v->z) == 1) return true;
        return false;
    }
}

extern "C" {
    f32 fn_800407F0(const TVec3f&, const TVec3f&, TVec3f*);
    f32 fn_8003FF50(const TVec3f* a, const TVec3f& b) NO_INLINE {
        f32 lengthA = PSVECMag(a);
        f32 lengthB = PSVECMag(&b);
        if (MR::isNearZero(lengthA * lengthB, 0.001f)) return 0.0f;
        f32 cosine = a->dot(b) / (lengthA * lengthB);
        if (cosine >= 1.0f) return 0.0f;
        if (cosine <= -1.0f) return PI;
        return fn_8003B350(cosine);
    }
}
namespace MR {
    f32 vecKillElement(const TVec3f& src, const TVec3f& axis, TVec3f* dst) NO_INLINE {
        if (fn_8003F1A0(&axis, 0.001f)) {
            *dst = src;
            return 0.0f;
        }
        return fn_800407F0(src, axis, dst);
    }
}
extern "C" {
    f32 fn_80040190(const TVec3f& a, const TVec3f& b, const TVec3f& axis) {
        TVec3f projectedA;
        TVec3f projectedB;
        MR::vecKillElement(a, axis, &projectedA);
        MR::vecKillElement(b, axis, &projectedB);
        return fn_8003FF50(&projectedA, projectedB);
    }
}

extern "C" {
    bool fn_8003F070(const TVec3f* a, const TVec3f& b, f32 tolerance) NO_INLINE {
        if (__fabsf(a->y * b.z - a->z * b.y) > tolerance) return false;
        if (__fabsf(a->z * b.x - a->x * b.z) > tolerance) return false;
        return !(__fabsf(a->x * b.y - a->y * b.x) > tolerance);
    }
    bool fn_8003F0F0(const TVec3f* a, const TVec3f& b, f32 tolerance) {
        if (a->dot(b) >= 0.0f) return false;
        return fn_8003F070(a, b, tolerance);
    }
}
namespace MR {
    f32 diffAngleSigned(const TVec3f& a, const TVec3f& b, const TVec3f& axis) {
        f32 angle = fn_8003FF50(&a, b);
        TVec3f cross;
        PSVECCrossProduct(&a, &axis, &cross);
        if (cross.dot(b) >= 0.0f) return angle;
        return -angle;
    }
}

extern "C" {
    f32 fn_80040020(const TVec2f* a, const TVec2f& b) {
        f32 lengthA = fn_80007B60(fn_8003E820(a, a));
        f32 lengthB = fn_80007B60(fn_8003E820(&b, &b));
        if (MR::isNearZero(lengthA * lengthB, 0.001f)) return 0.0f;
        f32 cosine = fn_8003E820(a, &b) / (lengthA * lengthB);
        if (cosine >= 1.0f) return 0.0f;
        if (cosine <= -1.0f) return PI;
        return fn_8003B350(cosine);
    }
    void fn_8003EEC0(TVec3f* dst, const TVec3f& src, const TVec3f& axis, f32 scale) {
        TVec3f normalized;
        normalized.set<f32>(axis);
        if (MR::normalizeOrZero(&normalized)) {
            fn_8000DBB0(dst);
        } else {
            TVec3f cross;
            PSVECCrossProduct(&normalized, &src, &cross);
            cross.scale(1.0f / scale);
            dst->set<f32>(cross);
        }
    }
}

extern "C" {
    bool fn_8003DE90(f32 value, f32 a, f32 b) {
        if (a > b) {
            if (value < b) return false;
            return !(value > a);
        }
        if (value < a) return false;
        return !(value > b);
    }
}

extern "C" {
    void fn_8000DB80(const Vec*, const Vec*, Vec*);
    void fn_8003DEF0(f32* perpendicular, f32* parallel, const TVec3f& origin, const TVec3f& point, const TVec3f& axis) {
        TVec3f delta(point);
        fn_8000DB80(&delta, &origin, &delta);
        TVec3f unitAxis;
        unitAxis.set<f32>(axis);
        if (MR::normalizeOrZero(&unitAxis)) {
            *parallel = 0.0f;
            *perpendicular = PSVECMag(&delta);
        }
        f32 projection = delta.dot(unitAxis);
        *parallel = projection;
        TVec3f offset(unitAxis);
        offset.scale(-projection);
        delta.add(offset);
        *perpendicular = PSVECMag(&delta);
    }
    void fn_80040B50(TVec3f* dst, const TVec3f& origin, const TVec3f& point) {
        fn_8000DB80(&point, &origin, dst);
        fn_805C8AC0(dst, dst);
    }
}

extern "C" {
    f64 fn_8063DC98(f64);
    f64 fn_8063D88C(f64);
    void fn_8000D770(void*, const TVec3f&, f32);
    void fn_8003D180(Float4* dst, const TVec3f& axis, f32 angle) NO_INLINE {
        f32 halfAngle = angle * 0.5f;
        fn_8000D770(dst, axis, fn_8063DC98(halfAngle));
        dst->w = fn_8063D88C(halfAngle);
    }
}

extern "C" {
    void fn_805C8C70(const Float4*, const Float4*, Float4*);
    void fn_80010480(Float4*);
    void fn_8003D200(Float4* dst, const TVec3f& angularVector) {
        Float4 rotation;
        TVec3f axis;
        f32 angle;
        fn_8003E840(&angle, &axis, angularVector);
        fn_8003D180(&rotation, axis, angle);
        fn_805C8C70(&rotation, dst, dst);
        fn_80010480(dst);
    }
    void fn_8003D260(Float4* dst, const TVec3f& src, const TVec3f& axis, f32 scale) {
        TVec3f angularVector;
        fn_8003EEC0(&angularVector, src, axis, scale);
        f32 angle;
        TVec3f direction;
        fn_8003E840(&angle, &direction, angularVector);
        Float4 rotation;
        fn_8003D180(&rotation, direction, angle);
        fn_805C8C70(&rotation, dst, dst);
        fn_80010480(dst);
    }
}

extern "C" {
    void fn_8003D2D0(Float4* dst, const Float4* src, const TVec3f& axis, f32 angle) {
        Float4 rotation;
        fn_8003D180(&rotation, axis, angle);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
    void fn_8003D3B0(const Float4*, TVec3f*);
    void fn_8003D330(Float4* dst, const Float4* src, f32 degrees) {
        TVec3f axis;
        fn_8003D3B0(src, &axis);
        Float4 rotation;
        fn_8003D180(&rotation, axis, degrees * PI_180);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
}

extern "C" {
    void fn_8003D3B0(const Float4* q, TVec3f* dst) NO_INLINE {
        dst->set<f32>(1.0f - 2.0f * (q->y * q->y) - 2.0f * (q->z * q->z),
            2.0f * (q->x * q->y) + 2.0f * (q->w * q->z),
            2.0f * (q->x * q->z) - 2.0f * (q->w * q->y));
    }
}

extern "C" {
    void fn_8000FC80(const Float4*, TVec3f*);
    void fn_8003D420(Float4* dst, const Float4* src, f32 degrees) {
        TVec3f axis;
        fn_8000FC80(src, &axis);
        Float4 rotation;
        fn_8003D180(&rotation, axis, degrees * PI_180);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
    void fn_800100C0(const Float4*, TVec3f*);
    void fn_8003D4A0(Float4* dst, const Float4* src, f32 degrees) {
        TVec3f axis;
        fn_800100C0(src, &axis);
        Float4 rotation;
        fn_8003D180(&rotation, axis, degrees * PI_180);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
}

extern "C" {
    bool fn_8003D520(Float4*, const Float4*, const TVec3f&, const TVec3f&, f32);
    bool fn_8003D680(Float4* dst, const Float4* src, const TVec3f& target, f32 angle) {
        TVec3f axis;
        fn_8003D3B0(src, &axis);
        return fn_8003D520(dst, src, axis, target, angle);
    }
    bool fn_8003D6F0(Float4* dst, const Float4* src, const TVec3f& target, f32 angle) {
        TVec3f axis;
        fn_8000FC80(src, &axis);
        return fn_8003D520(dst, src, axis, target, angle);
    }
    bool fn_8003D760(Float4* dst, const Float4* src, const TVec3f& target, f32 angle) {
        TVec3f axis;
        fn_800100C0(src, &axis);
        return fn_8003D520(dst, src, axis, target, angle);
    }
}

extern "C" {
    void fn_8003CEB0(Float4*, const TVec3f&, const TVec3f&, f32);
    bool fn_8003D520(Float4* dst, const Float4* src, const TVec3f& from, const TVec3f& to, f32 maxAngle) NO_INLINE {
        TVec3f adjustedFrom;
        TVec3f adjustedTo(to);
        bool opposite;
        if (from.dot(to) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&from, to, 0.01f);
        if (opposite) fn_8003B770(&adjustedFrom, from, 0.001f);
        else adjustedFrom.set<f32>(from);
        MR::normalizeOrZero(&adjustedFrom);
        MR::normalizeOrZero(&adjustedTo);
        f32 angle = fn_8003B350(fn_8003B8E0(adjustedFrom.dot(adjustedTo), -1.0f, 1.0f));
        f32 fraction;
        if (angle <= maxAngle) fraction = 1.0f;
        else fraction = fn_8003B8E0(maxAngle / angle, 0.0f, 1.0f);
        Float4 rotation;
        fn_8003CEB0(&rotation, adjustedFrom, adjustedTo, fraction);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
        return angle < 0.015f;
    }
}

extern "C" {
    void fn_8003D7D0(Float4* dst, const Float4* src, const TVec3f& target, f32 fraction) {
        TVec3f axis;
        fn_8003D3B0(src, &axis);
        bool opposite;
        if (axis.dot(target) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&axis, target, 0.01f);
        if (opposite) fn_8003B770(&axis, axis, 0.001f);
        Float4 rotation;
        fn_8003CEB0(&rotation, axis, target, fraction);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
    void fn_8003D8A0(Float4* dst, const Float4* src, const TVec3f& target, f32 fraction) {
        TVec3f axis;
        fn_8000FC80(src, &axis);
        bool opposite;
        if (axis.dot(target) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&axis, target, 0.01f);
        if (opposite) fn_8003B770(&axis, axis, 0.001f);
        Float4 rotation;
        fn_8003CEB0(&rotation, axis, target, fraction);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
}

extern "C" {
    void fn_8003D970(Float4* dst, const Float4* src, const TVec3f& target, f32 fraction) {
        TVec3f axis;
        fn_800100C0(src, &axis);
        bool opposite;
        if (axis.dot(target) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&axis, target, 0.01f);
        if (opposite) fn_8003B770(&axis, axis, 0.001f);
        Float4 rotation;
        fn_8003CEB0(&rotation, axis, target, fraction);
        fn_805C8C70(&rotation, src, dst);
        fn_80010480(dst);
    }
}

inline f32 quaternionCrossLength(const TVec3f& v) { return PSVECMag(&v); }
extern "C" {
    extern u8 lbl_8074E9C0[0x1020];
    f32 fn_8053A9C0(const void*, f32, f32);
    void fn_80007BA0(Float4*, f32, f32, f32, f32);
    void fn_8003CEB0(Float4* dst, const TVec3f& from, const TVec3f& to, f32 fraction) NO_INLINE {
        TVec3f cross;
        PSVECCrossProduct(&from, &to, &cross);
        f32 length = quaternionCrossLength(cross);
        if (length <= 0.000003814697265625f) {
            fn_80007BA0(dst, 0.0f, 0.0f, 0.0f, 1.0f);
        } else {
            f32 angle = fn_8053A9C0(lbl_8074E9C0, length, from.dot(to));
            f32 halfAngle = fraction * (0.5f * angle);
            fn_8000D770(dst, cross, static_cast<f32>(fn_8063DC98(halfAngle)) / length);
            dst->w = fn_8063D88C(halfAngle);
        }
    }
}

extern "C" {
    void fn_8003CFD0(Float4* dst, const Float4* src, const TVec3f& targetUp, const TVec3f& targetFront, f32 upFraction, f32 frontFraction) NO_INLINE {
        Float4 current;
        fn_8003CE80(&current, src);
        TVec3f front;
        fn_800100C0(&current, &front);
        bool opposite;
        if (front.dot(targetFront) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&front, targetFront, 0.01f);
        if (opposite) fn_8003B770(&front, front, 0.001f);
        Float4 frontRotation;
        fn_8003CEB0(&frontRotation, front, targetFront, frontFraction);
        fn_805C8C70(&frontRotation, &current, &current);
        TVec3f up;
        fn_8000FC80(&current, &up);
        fn_800100C0(&current, &front);
        TVec3f projectedUp;
        JMAVECScaleAdd(&front, &targetUp, &projectedUp, -front.dot(targetUp));
        MR::normalizeOrZero(&projectedUp);
        if (up.dot(projectedUp) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&up, projectedUp, 0.01f);
        if (opposite) fn_8003B770(&up, up, 0.001f);
        Float4 upRotation;
        fn_8003CEB0(&upRotation, up, projectedUp, upFraction);
        fn_805C8C70(&upRotation, &current, &current);
        fn_80010480(&current);
        fn_8003CE80(dst, &current);
    }
    void fn_8003CFB0(Float4* dst, const TVec3f& up, const TVec3f& front, f32 upFraction, f32 frontFraction) {
        fn_8003CFD0(dst, dst, up, front, upFraction, frontFraction);
    }
}

extern "C" {
    void fn_8003CCD0(Float4* dst, const Float4* src, const TVec3f& targetUp, const TVec3f& targetFront, f32 upFraction, f32 frontFraction) NO_INLINE {
        Float4 current;
        fn_8003CE80(&current, src);
        TVec3f up;
        fn_8000FC80(&current, &up);
        bool opposite;
        if (up.dot(targetUp) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&up, targetUp, 0.01f);
        if (opposite) fn_8003B770(&up, up, 0.001f);
        Float4 upRotation;
        fn_8003CEB0(&upRotation, up, targetUp, upFraction);
        fn_805C8C70(&upRotation, &current, &current);
        TVec3f front;
        fn_8000FC80(&current, &up);
        fn_800100C0(&current, &front);
        TVec3f projectedFront;
        JMAVECScaleAdd(&up, &targetFront, &projectedFront, -up.dot(targetFront));
        MR::normalizeOrZero(&projectedFront);
        if (front.dot(projectedFront) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&front, projectedFront, 0.01f);
        if (opposite) fn_8003B770(&front, front, 0.001f);
        Float4 frontRotation;
        fn_8003CEB0(&frontRotation, front, projectedFront, frontFraction);
        fn_805C8C70(&frontRotation, &current, &current);
        fn_80010480(&current);
        fn_8003CE80(dst, &current);
    }
    void fn_8003CCB0(Float4* dst, const TVec3f& up, const TVec3f& front, f32 upFraction, f32 frontFraction) {
        fn_8003CCD0(dst, dst, up, front, upFraction, frontFraction);
    }
}

extern "C" {
    bool fn_8003E8C0(TVec3f*, const TVec3f&, const TVec3f&, const TVec3f&, f32, f32);
    bool fn_8003EAD0(TVec3f* dst, const TVec3f& from, const TVec3f& to, const TVec3f& axis, f32 angle) NO_INLINE {
        TVec3f projectedTo;
        JMAVECScaleAdd(&axis, &to, &projectedTo, -axis.dot(to));
        MR::normalizeOrZero(&projectedTo);
        TVec3f projectedFrom;
        JMAVECScaleAdd(&axis, &from, &projectedFrom, -axis.dot(from));
        MR::normalizeOrZero(&projectedFrom);
        if (fn_8003F1A0(&projectedFrom, 0.001f)) projectedFrom = -projectedTo;
        if (!fn_8003F1A0(&projectedTo, 0.001f)) {
            if (angle > -1.0f) return fn_8003E8C0(dst, projectedFrom, projectedTo, axis, angle, 0.02f);
            dst->set<f32>(projectedTo);
            return true;
        }
        return false;
    }
    bool fn_8003EC00(TVec3f* dst, const TVec3f& to, const TVec3f& axis, f32 angle) {
        return fn_8003EAD0(dst, *dst, to, axis, angle);
    }
}

inline TVec3f scaledTurnVector(const TVec3f& v, f32 scale) {
    TVec3f result(v);
    result.scale(scale);
    return result;
}
extern "C" {
    f32 fn_8003CB00(f32);
    bool fn_8003E8C0(TVec3f* dst, const TVec3f& from, const TVec3f& to, const TVec3f& axis, f32 cosine, f32 fallbackScale) NO_INLINE {
        if (fn_8003F1A0(&from, 0.001f)) return false;
        if (fn_8003F1A0(&to, 0.001f)) return false;
        if (from.dot(to) > cosine) {
            dst->set<f32>(to);
            fn_805C8AC0(dst, dst);
            return true;
        }
        f32 sine = fn_8003CB00(1.0f - cosine * cosine);
        TVec3f perpendicular;
        JMAVECScaleAdd(&from, &to, &perpendicular, -from.dot(to));
        if (fn_8003F1A0(&perpendicular, 0.001f)) {
            TVec3f cross;
            PSVECCrossProduct(&from, &axis, &cross);
            fn_805C8AC0(&cross, &cross);
            dst->set<f32>(from.addInline(scaledTurnVector(cross, fallbackScale)));
            fn_805C8AC0(dst, dst);
            return false;
        }
        fn_805C8AC0(&perpendicular, &perpendicular);
        dst->set<f32>(scaledTurnVector(from, cosine).addInline(scaledTurnVector(perpendicular, sine)));
        fn_805C8AC0(dst, dst);
        return false;
    }
}

extern "C" f32 fn_8003EC20(TVec3f*, const TVec3f&, const TVec3f&, f32, const TVec3f&);
namespace MR {
    f32 turnVecToVecDegree(TVec3f* dst, const TVec3f& from, const TVec3f& to, f32 degrees, const TVec3f& axis) {
        return fn_8003EC20(dst, from, to, degrees * PI_180, axis) * _180_PI;
    }
}

inline void transformTurnVector(const Float4& q, TVec3f& v) {
    Float4 r;
    r.x = q.y * v.z - q.z * v.y + q.w * v.x;
    r.y = -q.x * v.z + q.z * v.x + q.w * v.y;
    r.z = q.x * v.y - q.y * v.x + q.w * v.z;
    r.w = -q.x * v.x - q.y * v.y - q.z * v.z;
    v.set<f32>(r.x * q.w + r.y * -q.z - r.z * -q.y + r.w * -q.x,
        -r.x * -q.z + r.y * q.w + r.z * -q.x + r.w * -q.y,
        r.x * -q.y - r.y * -q.x + r.z * q.w + r.w * -q.z);
}
inline f32 turnAngle(const TVec3f& from, const TVec3f& to) { return fn_8003B1A0(fn_8003B8E0(from.dot(to), -1.0f, 1.0f)); }
extern "C" {
    f32 fn_8003EC20(TVec3f* dst, const TVec3f& from, const TVec3f& to, f32 maxAngle, const TVec3f& axis) NO_INLINE {
        f32 angle = turnAngle(from, to);
        f32 remaining = 0.0f;
        f32 step = angle;
        if (maxAngle <= step) {
            remaining = step - maxAngle;
            step = maxAngle;
        }
        if (MR::isNearZero(angle, 0.001f)) {
            dst->set<f32>(to);
            return 0.0f;
        }
        Float4 rotation;
        bool opposite;
        if (from.dot(to) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&from, to, 0.01f);
        if (opposite) fn_8003D180(&rotation, axis, step);
        else fn_8003CEB0(&rotation, from, to, step / angle);
        TVec3f result(from);
        transformTurnVector(rotation, result);
        MR::normalizeOrZero(&result);
        if (!fn_8003F1A0(&result, 0.001f)) dst->set<f32>(result);
        return remaining;
    }
}

extern "C" {
    f32 fn_8003CB00(register f32 value) NO_INLINE {
        if (value > 0.0f) {
            register f32 estimate;
            asm { frsqrte estimate, value }
            f32 product = estimate * value;
            estimate = -(product * estimate - 3.0f);
            estimate = estimate * product;
            estimate = estimate / 2.0f;
            return estimate;
        }
        return value;
    }
}

inline f32 quaternionDegreesToRadians(f32 degrees) { return degrees * PI_180; }
extern "C" {
    void fn_80007BC0(Float4*, f32, f32, f32);
    void fn_8003CB40(Float4* dst, const TVec3f& radians) {
        fn_80007BC0(dst, radians.x, radians.y, radians.z);
    }
    void fn_8003CB50(Float4* dst, const TVec3f& degrees) {
        fn_80007BC0(dst, quaternionDegreesToRadians(degrees.x), quaternionDegreesToRadians(degrees.y), quaternionDegreesToRadians(degrees.z));
    }
}

extern "C" {
    void fn_80007930(const TMtx34f*, Float4*);
    void fn_80045F50(TRot3f*, const TVec3f&, const TVec3f&);
    void fn_80045B10(TRot3f*, const TVec3f&, const TVec3f&);
    void fn_80045DB0(TRot3f*, const TVec3f&, const TVec3f&);
    void fn_8003CB70(Float4* dst, const TVec3f& a, const TVec3f& b) {
        TRot3f matrix;
        fn_80045F50(&matrix, a, b);
        fn_80007930(&matrix, dst);
    }
    void fn_8003CBB0(Float4* dst, const TVec3f& a, const TVec3f& b) {
        TRot3f matrix;
        fn_80045B10(&matrix, a, b);
        fn_80007930(&matrix, dst);
    }
    void fn_8003CBF0(Float4* dst, const TVec3f& a, const TVec3f& b) {
        TRot3f matrix;
        fn_80045DB0(&matrix, a, b);
        fn_80007930(&matrix, dst);
    }
    void fn_8003CC30(Float4* dst, const TVec3f& a, const TVec3f& b) {
        TRot3f matrix;
        fn_80045F50(&matrix, a, b);
        fn_80007930(&matrix, dst);
    }
    void fn_80046060(TRot3f*, const TVec3f&);
    void fn_8003CC70(Float4* dst, const TVec3f& axis) {
        TRot3f matrix;
        fn_80046060(&matrix, axis);
        fn_80007930(&matrix, dst);
    }
}

inline f32 headingDegreeFactor() { return 57.2957763671875f; }
inline f32 headingAtan(f32 y, f32 x) { return fn_8053A9C0(lbl_8074E9C0, y, x); }
extern "C" {
    f32 fn_800406E0(f32 x, f32 y) {
        f32 angle = headingAtan(-y, x);
        return MR::repeat(90.0f + angle * headingDegreeFactor(), 0.0f, 360.0f);
    }
    f32 fn_80040750(const TVec3f* v) {
        if (v->z == 0.0f) {
            if (v->x >= 0.0f) return 90.0f;
            return -90.0f;
        }
        if (v->z >= 0.0f) return headingAtan(v->x, v->z) * headingDegreeFactor();
        return 180.0f - headingAtan(v->x, -v->z) * headingDegreeFactor();
    }
}

extern "C" {
    u32 fn_8003F4D0(const u8* from, const u8* to, f32 fraction) {
        u8 alpha = MR::lerp(from[3], to[3], fraction);
        u8 blue = MR::lerp(from[2], to[2], fraction);
        // The target uses the second color's blue channel here.
        u8 green = MR::lerp(from[1], to[2], fraction);
        u8 red = MR::lerp(from[0], to[0], fraction);
        union { u8 channels[4]; u32 packed; } result;
        result.channels[0] = red;
        result.channels[1] = green;
        result.channels[2] = blue;
        result.channels[3] = alpha;
        return result.packed;
    }
}

extern "C" {
    void fn_805C8170(TMtx34f*, const TVec3f&, f32);
    void fn_805C86D0(const TMtx34f*, const TVec3f*, TVec3f*);
    void fn_800409D0(const TVec3f* src, const TVec3f& axis, TVec3f* dst, f32 radians) {
        TMtx34f matrix;
        fn_805C8170(&matrix, axis, radians);
        fn_805C86D0(&matrix, src, dst);
    }
}

extern "C" {
    void fn_8003FD80(TVec3f* dst, const TVec3f* rotation) {
        TVec3f forward(0.0f, 0.0f, 1.0f);
        TMtx34f matrix;
        MR::makeMtxTR(matrix.mMtx, 0.0f, 0.0f, 0.0f, rotation->x, rotation->y, rotation->z);
        fn_805C86D0(&matrix, &forward, dst);
    }
}

extern "C" {
    f32 fn_800401F0(const TVec3f& from, const TVec3f& to, const TVec3f& axis) {
        TVec3f projectedFrom, projectedTo;
        MR::vecKillElement(from, axis, &projectedFrom);
        MR::vecKillElement(to, axis, &projectedTo);
        f32 angle = fn_8003FF50(&projectedFrom, projectedTo);
        TMtx34f matrix;
        fn_805C8170(&matrix, axis, 0.0001745329354889691f);
        f32 originalDot = projectedFrom.dot(projectedTo);
        fn_805C86D0(&matrix, &projectedFrom, &projectedFrom);
        if (projectedFrom.dot(projectedTo) > originalDot) return angle;
        return -angle;
    }
}

extern "C" {
    bool fn_800402C0(const TVec3f& a, const TVec3f& b, f32 radians) NO_INLINE {
        if (fn_8003F1A0(&a, 0.001f) || fn_8003F1A0(&b, 0.001f)) return false;
        TVec3f normalizedA, normalizedB;
        MR::normalize(&normalizedA, a);
        MR::normalize(&normalizedB, b);
        f32 threshold = JMACosRadian(radians);
        return normalizedA.dot(normalizedB) >= threshold;
    }
    bool fn_80040390(const TVec3f& a, const TVec3f& b, f32 degrees) {
        return fn_800402C0(a, b, PI_180 * degrees);
    }
}

extern "C" {
    bool fn_800403A0(const TVec3f& a, const TVec3f& b, const TVec3f& axis, f32 horizontal, f32 vertical) NO_INLINE {
        if (vertical > 1.5707963705062866) vertical = 1.5707963705062866f;
        TVec3f normalizedA, normalizedB, normalizedAxis, projected;
        normalizedA.set<f32>(a);
        if (MR::normalizeOrZero(&normalizedA)) return false;
        normalizedB.set<f32>(b);
        if (MR::normalizeOrZero(&normalizedB)) return false;
        normalizedAxis.set<f32>(axis);
        if (MR::normalizeOrZero(&normalizedAxis)) return false;
        JMAVECScaleAdd(&axis, &a, &projected, -axis.dot(a));
        MR::normalizeOrZero(&projected);
        f32 cosine = JMACosRadian(horizontal);
        if (projected.dot(normalizedB) < cosine) return false;
        f64 sine = __fabs(JMASinRadian(vertical));
        return !(__fabs(normalizedA.dot(normalizedAxis)) > sine);
    }
    bool fn_80040500(const TVec3f& a, const TVec3f& b, const TVec3f& axis, f32 horizontal, f32 vertical) {
        vertical = PI_180 * vertical;
        horizontal = PI_180 * horizontal;
        return fn_800403A0(a, b, axis, horizontal, vertical);
    }
}

extern "C" {
    void fn_80040510(const TVec3f* points, u32 count, TVec3f* minimum, TVec3f* maximum) {
        *minimum = points[0];
        *maximum = points[0];
        for (u32 i = 1; i < count; ++i) {
            if (points[i].x < minimum->x) minimum->x = points[i].x;
            if (points[i].y < minimum->y) minimum->y = points[i].y;
            if (points[i].z < minimum->z) minimum->z = points[i].z;
            if (maximum->x < points[i].x) maximum->x = points[i].x;
            if (maximum->y < points[i].y) maximum->y = points[i].y;
            if (maximum->z < points[i].z) maximum->z = points[i].z;
        }
    }
}

extern "C" {
    void fn_800408A0(const TVec3f& from, const TVec3f& to, const TVec3f& axis, TVec3f* dst, f32 step) {
        f32 lengthFrom = PSVECMag(&from);
        f32 lengthTo = PSVECMag(&to);
        f32 angle;
        if (0.0f == lengthFrom || 0.0f == lengthTo) angle = 0.0f;
        else angle = fn_8003FF50(&from, to);
        if (0.0f == angle) *dst = to;
        else if (angle > step) {
            TVec3f cross;
            if (angle < PI) {
                PSVECCrossProduct(&from, &to, &cross);
                if (cross.dot(axis) < 0.0f) step = -step;
            }
            TMtx34f matrix;
            fn_805C8170(&matrix, axis, step);
            fn_805C86D0(&matrix, &from, dst);
        }
        else *dst = to;
    }
}

extern "C" {
    f32 fn_80040A20(const TVec3f& start, const TVec3f& end, const TVec3f& point, TVec3f* dst) {
        TVec3f direction(end);
        fn_8000DB80(&direction, &start, &direction);
        f32 length = PSVECMag(&direction);
        f32 factor = -(direction.z * (start.z - point.z) +
            (direction.x * (start.x - point.x) + direction.y * (start.y - point.y))) / (length * length);
        *dst = start.addInline(scaledTurnVector(direction, factor));
        return factor;
    }
}

extern "C" {
    bool fn_8003F2C0(f32 angle, f32 a, f32 b) NO_INLINE {
        f32 wrappedAngle = fn_8003E760(angle);
        f32 high = fn_8003E760(a);
        f32 low = fn_8003E760(b);
        if (low > high) { f32 temp = low; low = high; high = temp; }
        bool inside = wrappedAngle >= low && wrappedAngle <= high;
        if (high - low > PI) inside = !inside;
        return inside;
    }
    f32 fn_8003F380(f32 from, f32 to, f32 fraction) {
        from = fn_8003E760(from);
        to = fn_8003E760(to);
        if (!fn_8003F2C0((from + to) / 2.0f, from, to)) {
            if (from < to) from += 6.2831854820251465f;
            else to += 6.2831854820251465f;
        }
        return fn_8003E760((1.0f - fraction) * from + fraction * to);
    }
}

extern "C" {
    void fn_8003F570(long count, f32* values, long* indices) {
        for (long i = 0; i < count; ++i) indices[i] = i;
        for (long i = 0; i < count; ++i) {
            f32 minimum = values[i];
            long smallest = i;
            for (long j = i + 1; j < count; ++j) {
                if (minimum > values[j]) { minimum = values[j]; smallest = j; }
            }
            long index = indices[i];
            f32 original = values[i];
            indices[i] = indices[smallest];
            values[i] = minimum;
            indices[smallest] = index;
            values[smallest] = original;
        }
    }
}

extern "C" {
    void fn_80011BB0(TVec3f*, f32);
    f32 fn_8003FBC0(TVec3f* dst, const TVec3f& src, const TVec3f& axis) {
        TVec3f projected(src);
        f32 length = PSVECMag(&src);
        f32 dot = axis.dot(src);
        TVec3f component(axis);
        component.scale(dot);
        fn_8000DB80(&projected, &component, &projected);
        fn_80011BB0(&projected, length);
        dst->set<f32>(projected);
        return length;
    }
}

inline f32 axisCosDegree(f32 v) { return JMACosDegree(v); }
inline f32 axisSinDegree(f32 v) { return JMASinDegree(v); }
extern "C" {
    void fn_8003FC70(TVec3f* dst, const TVec3f& degrees) {
        f32 cx = axisCosDegree(degrees.x);
        f32 cy = axisCosDegree(degrees.y);
        f32 cz = axisCosDegree(degrees.z);
        f32 sx = axisSinDegree(degrees.x);
        f32 sy = axisSinDegree(degrees.y);
        f32 sz = axisSinDegree(degrees.z);
        f32 x = sx * (cz * sy) - sz * cx;
        f32 y = sx * (sz * sy) + cz * cx;
        dst->z = cy * sx;
        dst->x = x;
        dst->y = y;
    }
}

inline f32 approachCircle() { return 6.2831854820251465f; }
extern "C" {
    f32 fn_8003DDE0(f32 current, f32 target, f32 step) {
        const f32 circle = 6.2831854820251465f;
        if ((target + approachCircle()) - current < PI) target = target + approachCircle();
        else if (current - (target - circle) < PI) target = target - circle;
        f32 result;
        if (current < target) {
            result = current + step;
            if (result > target) result = target;
        } else {
            result = current - step;
            if (result < target) result = target;
        }
        return MR::repeat(result, 0.0f, circle);
    }
}

inline f32 clampMagnitude(f32 v) { return v; }
extern "C" {
    f32 fn_8000E240(const TVec3f*);
    f32 fn_8000D7A0(f32);
    void fn_8003DD30(TVec3f* dst, const TVec3f& src, f32 maximum) {
        if (fn_8000E240(&src) > maximum * maximum) {
            f32 squaredLength = fn_8000E240(&src);
            if (squaredLength <= 0.000003814697265625f) fn_8000DBB0(dst);
            else fn_8000D770(dst, src, fn_8000D7A0(squaredLength) * clampMagnitude(maximum));
        } else dst->set<f32>(src);
    }
}

inline void subtractReflection(TVec3f* dst, const TVec3f& correction) { fn_8000DB80(dst, &correction, dst); }
extern "C" {
    bool fn_8003EF60(TVec3f* velocity, const TVec3f& normal, f32 restitution, f32 threshold) {
        f32 dot = normal.dot(*velocity);
        if (dot < -threshold) {
            subtractReflection(velocity, scaledTurnVector(scaledTurnVector(normal, dot), 1.0f + restitution));
            return true;
        } else if (dot < 0.0f) {
            subtractReflection(velocity, scaledTurnVector(normal, dot));
            return false;
        }
        return false;
    }
}

extern "C" {
    f32 fn_8003C3A0(TVec3f* dst, const TVec3f& point, const TVec3f& start, const TVec3f& end) {
        TVec3f direction(end);
        fn_8000DB80(&direction, &start, &direction);
        f32 startDot = start.dot(direction);
        f32 difference = point.dot(direction) - startDot;
        f32 factor = difference / fn_8000E240(&direction);
        direction.scale(factor);
        dst->set<f32>(start);
        dst->add(direction);
        return factor;
    }
}

inline f32 segmentProjectionRatio(f32 difference, const TVec3f& direction) { return difference / fn_8000E240(&direction); }
inline f32 clampSegmentFactor(const f32& v) { return fn_8003B8E0(v, 0.0f, 1.0f); }
extern "C" {
    f32 fn_8003C460(TVec3f* dst, const TVec3f& point, const TVec3f& start, const TVec3f& end) {
        TVec3f direction(end);
        fn_8000DB80(&direction, &start, &direction);
        f32 startDot = start.dot(direction);
        f32 factor = point.dot(direction) - startDot;
        factor /= fn_8000E240(&direction);
        factor = clampSegmentFactor(factor);
        direction.scale(factor);
        dst->set<f32>(start);
        dst->add(direction);
        return factor;
    }
}

inline void reflectComponents(TVec3f* dst, const TVec3f& normal, f32 dot, f32 z, f32 y, f32 x, f32 multiplier) {
    x -= dot * (multiplier * normal.x);
    dst->x = x;
    y -= dot * (multiplier * normal.y);
    dst->y = y;
    z -= dot * (multiplier * normal.z);
    dst->z = z;
}
extern "C" {
    bool fn_8003C800(TVec3f* velocity, const TVec3f& normal, f32 restitution) {
        f32 dot = velocity->dot(normal);
        if (dot < 0.0f) {
            reflectComponents(velocity, normal, dot, velocity->z, velocity->y, velocity->x, 1.0f + restitution);
            return true;
        }
        return false;
    }
}

extern "C" {
    bool fn_8003C720(TVec3f* dst, const TVec3f& origin, const TVec3f& direction, const TVec3f& planePoint, const TVec3f& normal) {
        f32 denominator = direction.dot(normal);
        TVec3f delta(planePoint);
        fn_8000DB80(&delta, &origin, &delta);
        if (0.0f < denominator) return false;
        f32 factor = normal.dot(delta) / denominator;
        if (dst) {
            dst->set<f32>(origin);
            dst->add(scaledTurnVector(direction, factor));
        }
        return true;
    }
}

extern "C" {
    bool fn_8003C280(TVec3f* axis, f32* cosine, const TVec3f& from, const TVec3f& to) {
        bool opposite;
        if (from.dot(to) >= 0.0f) opposite = false;
        else opposite = fn_8003F070(&from, to, 0.01f);
        TVec3f adjusted, cross;
        if (opposite) {
            fn_8003B770(&adjusted, from, 0.01f);
            MR::normalize(&adjusted);
        } else adjusted.set<f32>(from);
        PSVECCrossProduct(&adjusted, &to, &cross);
        if (fn_8003F1A0(&cross, 0.001f)) {
            fn_8000DBB0(axis);
            *cosine = 1.0f;
            return false;
        }
        MR::normalize(axis, cross);
        *cosine = fn_8003B8E0(adjusted.dot(to), -1.0f, 1.0f);
        return true;
    }
}

extern "C" {
    bool fn_8003C8C0(TVec3f* velocity, const TVec3f& normal, f32 restitution, f32 tangentScale) {
        f32 dot = velocity->dot(normal);
        if (dot < 0.0f) {
            subtractReflection(velocity, scaledTurnVector(normal, dot));
            velocity->scale(tangentScale);
            subtractReflection(velocity, scaledTurnVector(scaledTurnVector(normal, dot), restitution));
            return true;
        }
        return false;
    }
}

extern "C" {
    void fn_8003C9C0(f32* quadratic, f32* linear, f32 height, f32 endHeight) {
        f32 discriminant = height * (height - endHeight);
        if (discriminant <= 0.0f) {
            *quadratic = -height;
            *linear = endHeight + height;
        } else if (__fabsf(endHeight) < 0.0001f) {
            *quadratic = -4.0f * height;
            *linear = 4.0f * height;
        } else {
            f32 root = fn_8003CB00(discriminant);
            f32 first = (height + root) / endHeight;
            f32 second = (height - root) / endHeight;
            f32 peak;
            if (0.0f <= first && first <= 1.0f) peak = first;
            else if (0.0f <= second && second <= 1.0f) peak = second;
            else peak = 1.0f;
            *quadratic = -height / (peak * peak);
            *linear = (-2.0f * peak) * *quadratic;
        }
    }
}

// Copy all twelve matrix elements before writing, allowing in-place use.
inline void copyInverseInput(register const TMtx34f* src, register TMtx34f* dst) {
    register f32 last, fifth, fourth, third, second, first;
    asm {
        psq_l first, 0(src), 0, 0
        psq_l second, 8(src), 0, 0
        psq_l third, 16(src), 0, 0
        psq_l fourth, 24(src), 0, 0
        psq_l fifth, 32(src), 0, 0
        psq_l last, 40(src), 0, 0
        psq_st last, 40(dst), 0, 0
        psq_st first, 0(dst), 0, 0
        psq_st second, 8(dst), 0, 0
        psq_st third, 16(dst), 0, 0
        psq_st fourth, 24(dst), 0, 0
        psq_st fifth, 32(dst), 0, 0
    }
}
inline void prepareInverseInput(TMtx34f& dst, const TMtx34f& src) { copyInverseInput(&src, &dst); }
extern "C" {
    void fn_80007060(TMtx34f*, const TMtx34f*);
    void fn_8003E410(TVec3f* dst, const TVec3f& src, const TMtx34f& transform) {
        TMtx34f inverse;
        copyInverseInput(&transform, &inverse);
        fn_80007060(&inverse, &inverse);
        inverse.mult(src, *dst);
    }
}

extern "C" {
    void fn_805C8AA0(const Vec*, Vec*, f32);
    void fn_805C8A40(const Vec*, const Vec*, Vec*);
}
namespace MR {
    void vecBlendNormal(TVec3f* dst, const TVec3f& from, const TVec3f& to, f32 fraction) {
        TVec3f a, b;
        if (fn_8003F1A0(&from, 0.001f)) fn_8000DBB0(&a);
        else {
            normalize(&a, from);
            fn_805C8AA0(&a, &a, 1.0f - fraction);
        }
        if (fn_8003F1A0(&to, 0.001f)) fn_8000DBB0(&b);
        else {
            normalize(&b, to);
            fn_805C8AA0(&b, &b, fraction);
        }
        fn_805C8A40(&a, &b, dst);
    }
}

extern "C" {
    void fn_8003FA70(u8* dst, const u8* from, const u8* to, f32 fraction) {
        dst[0] = fn_8003B820(fraction, from[0], to[0]);
        dst[1] = fn_8003B820(fraction, from[1], to[1]);
        dst[2] = fn_8003B820(fraction, from[2], to[2]);
        dst[3] = fn_8003B820(fraction, from[3], to[3]);
    }
}

inline f32 interpolationPi() { return 3.1415927f; }
extern "C" {
    bool fn_8003F840(TVec3f* dst, const TVec3f& from, const TVec3f& to, f32 fraction) {
        f32 lengthFrom = PSVECMag(&from);
        f32 lengthTo = PSVECMag(&to);
        f32 angle;
        if (0.0f == lengthFrom || 0.0f == lengthTo) angle = 0.0f;
        else angle = fn_8003FF50(&from, to);
        if (angle < 0.1f) {
            MR::vecBlendNormal(dst, from, to, fraction);
            fn_80011BB0(dst, lengthFrom * (1.0f - fraction) + lengthTo * fraction);
            return true;
        }
        if (0.0f == angle) {
            *dst = from;
            fn_80011BB0(dst, lengthFrom * (1.0f - fraction) + lengthTo * fraction);
            return false;
        }
        if (angle == interpolationPi()) return false;
        f32 sine = JMASinRadian(angle);
        *dst = scaledTurnVector(scaledTurnVector(from, JMASinRadian(angle * (1.0f - fraction))).addInline(scaledTurnVector(to, JMASinRadian(angle * fraction))), 1.0f / sine);
        fn_80011BB0(dst, lengthFrom * (1.0f - fraction) + lengthTo * fraction);
        return true;
    }
}

extern "C" {
    void fn_8003DBE0(TVec3f* dst, const TVec3f& reference, f32 degrees) {
        TVec3f axis;
        TVec3f cross;
        PSVECCrossProduct(dst, &reference, &cross);
        f32 length = PSVECMag(&cross);
        f32 angle = fn_8053A9C0(lbl_8074E9C0, length, dst->dot(reference));
        if (57.2957763671875f * __fabsf(angle) <= degrees) return;
        PSVECCrossProduct(&reference, dst, &axis);
        if (MR::normalizeOrZero(&axis)) return;
        JMACosDegree(degrees);
        TRot3f rotation;
        rotation.identity();
        rotation.setRotate(axis, PI_180 * degrees);
        rotation.mult(reference, *dst);
    }
}

namespace JGeometry {
    template <>
    void TRotation3<TMatrix34<SMatrix34C<f32> > >::setRotate(const TVec3f& axis, f32 angle) {
        TVec3f vec;
        vec.set<f32>(axis);
        PSVECMag(&vec);
        fn_805C8AC0(&vec, &vec);
        f32 s = fn_8063DC98(angle);
        f32 c = fn_8063D88C(angle);
        f32 negc = 1.0f - c;
        f32 x = vec.x, y = vec.y, z = vec.z;
        f32 xx = x * x, yy = y * y, zz = z * z;
        this->mMtx[0][0] = c + negc * xx;
        this->mMtx[0][1] = negc * x * y - s * z;
        this->mMtx[0][2] = negc * x * z + s * y;
        this->mMtx[1][0] = negc * x * y + s * z;
        this->mMtx[1][1] = c + negc * yy;
        this->mMtx[1][2] = negc * y * z - s * x;
        this->mMtx[2][0] = negc * x * z - s * y;
        this->mMtx[2][1] = negc * y * z + s * x;
        this->mMtx[2][2] = c + negc * zz;
    }
}

inline TVec3f capsuleEndpointOffset(const TVec3f& point, const TVec3f& endpoint) {
    TVec3f delta(point);
    fn_8000DB80(&delta, &endpoint, &delta);
    return delta;
}
extern "C" {
    f32 fn_8000DF50(const TVec3f*, const TVec3f*);
    bool fn_8003C530(const TVec3f& point, const TVec3f& start, const TVec3f& end, TVec3f* normal, f32 radius) {
        TVec3f offset(point);
        TVec3f direction(end);
        fn_8000DB80(&offset, &start, &offset);
        fn_8000DB80(&direction, &start, &direction);
        f32 dot = offset.dot(direction);
        radius *= radius;
        if (dot < 0.0f) {
            if (fn_8000DF50(&start, &point) < radius) {
                if (normal) {
                    normal->set<f32>(capsuleEndpointOffset(point, start));
                    MR::normalizeOrZero(normal);
                }
                return true;
            }
        } else if (fn_8000E240(&direction) < dot) {
            if (fn_8000DF50(&end, &point) < radius) {
                if (normal) {
                    normal->set<f32>(capsuleEndpointOffset(point, end));
                    MR::normalizeOrZero(normal);
                }
                return true;
            }
        } else {
            TVec3f perpendicular(direction);
            perpendicular.scale(dot / fn_8000E240(&direction));
            fn_8000DB80(&perpendicular, &offset, &perpendicular);
            if (fn_8000E240(&perpendicular) <= radius) {
                if (normal) {
                    normal->set<f32>(-perpendicular);
                    MR::normalizeOrZero(normal);
                }
                return true;
            }
        }
        return false;
    }
}
