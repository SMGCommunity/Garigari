#pragma once

#include <revolution.h>
#include <revolution/mtx/vec.h>
#include "JMath.hpp"

namespace JGeometry {
    template <typename T>
    struct TVec3 {
        T x;
        T y;
        T z;

        TVec3<T>& operator=(const TVec3<T>& b) {
            set(b.x, b.y, b.z);
            return *this;
        }

        void set (T x_, T y_, T z_) {
            x = x_;
            y = y_;
            z = z_;
        }
    };

    __attribute__((always_inline))
    inline void setTVec3f(const f32* a, f32* b) {
        #ifdef __MWERKS__
        const register f32* v_a = a;
        register f32* v_b = b;

        register f32 b_x;
        register f32 a_x;

        asm {
            psq_l a_x, 0(v_a), 0, 0
            lfs b_x, 8(v_a)
            psq_st a_x, 0(v_b), 0, 0
            stfs b_x, 8(v_b)
        };
        #endif
    }

    template<>
    struct TVec3<f32> : public Vec {
        inline TVec3(const Vec& vec) {
            setTVec3f(&vec.x, &x);
        }

        inline TVec3(const TVec3<f32> &vec) {
            setTVec3f(&vec.x, &x);
        }

        TVec3(f32 x, f32 y, f32 z) {
            set(x, y, z);
        }

        TVec3() {}

        void set(const TVec3<f32>& rVec) {
            x = rVec.x;
            y = rVec.y;
            z = rVec.z;
        }

        void set(f32 x_, f32 y_, f32 z_) {
            x = x_;
            y = y_;
            z = z_;
        }

        void setTrans(MtxPtr mtx) {
            set((*mtx)[3], (*mtx)[7], (*mtx)[11]);
        }

        void add(const TVec3<f32> &b) {
            JMathInlineVEC::PSVECAdd(this, &b, this);
        }
    };

    template <typename T>
    struct SMatrix34C {
        T data[3][4];
    };

    template<>
    struct SMatrix34C<f32> {
        f32 data[3][4];

        void identity();

        typedef f32 ArrType[4];

        operator ArrType*() {
            return data;
        }

        operator const ArrType*() const {
            return data;
        }
    };

    template<typename T>
    struct TMatrix34 : public T {};

    template<typename T>
    struct TRotation3 : public T {};

    template<typename T>
    struct TPosition3 : public T {};
};

typedef JGeometry::TVec3<f32> TVec3f;
typedef JGeometry::SMatrix34C<f32> SMtx34C;
typedef JGeometry::TMatrix34<SMtx34C> TMtx34f;
typedef JGeometry::TRotation3<TMtx34f> TRot3f;
typedef JGeometry::TPosition3<TRot3f> TPos3f;
