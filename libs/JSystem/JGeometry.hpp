#pragma once

#include <revolution.h>
#include <revolution/mtx/vec.h>
#include "JMath.hpp"

namespace JGeometry {
    template<typename T>
    class TUtil {
    public:
        static int epsilonEquals(T a1, T a2, T a3) {
            int ret = 0;

            a1 -= a2;

            if (-a3 <= a1 && a1 <= a3) {
                ret = 1;
            }

            return ret;
        }
    };

    template <typename T>
    struct TVec3 {
        T x;
        T y;
        T z;

        inline TVec3(T val) {
            x = val;
            y = val;
            z = val;
        }

        void set(T x_, T y_, T z_) {
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

        inline TVec3(f32 _x, f32 _y, f32 _z) {
            x = _x;
            y = _y;
            z = _z;
        }

        TVec3(f32 val) {
            z = y = x = val;
        }

        inline TVec3() {}

        TVec3& operator=(const TVec3& b) NO_INLINE {
            setTVec3f(&b.x, &x);
            return *this;
        }

        TVec3& operator-=(const TVec3 &op) NO_INLINE {
            sub(op);
            return *this;
        }

        template <typename T>
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

        void sub(const TVec3<f32> &b) {
            JMathInlineVEC::PSVECSubtract(this, &b, this);
        }

        void setTrans(MtxPtr mtx) {
            set((*mtx)[3], (*mtx)[7], (*mtx)[11]);
        }

        void setPS(const TVec3<f32>& rVec) {
            setTVec3f(&rVec.x, &x);
        }

        void add(const TVec3<f32> &b) {
            JMathInlineVEC::PSVECAdd(this, &b, this);
        }
        
        f32 squareMag() const {
            return JMathInlineVEC::PSVECSquareMag(this);
        }

        f32 dot(const TVec3 &) const;

        bool epsilonEquals(const TVec3<f32> &a1, f32 a2) const {
            bool ret = false;
            if (JGeometry::TUtil<f32>::epsilonEquals(x, a1.x, a2)) {
                if (JGeometry::TUtil<f32>::epsilonEquals(y, a1.y, a2)) {
                    if (JGeometry::TUtil<f32>::epsilonEquals(z, a1.z, a2)) {
                        ret = true;
                    }
                }
            }

            return ret;
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

        inline void rotateX(f32 cos, f32 sin) __attribute__((always_inline)) {
            this->data[1][1] = cos;
            this->data[2][1] = sin;
            this->data[1][2] = -sin;
            this->data[2][2] = cos;
        }

        inline void rotateY(f32 cos, f32 sin) __attribute__((always_inline)) {
            this->data[0][0] = cos;
            this->data[0][2] = sin;
            this->data[2][0] = -sin;
            this->data[2][2] = cos;            
        }

        inline void rotateZ(f32 cos, f32 sin) __attribute__((always_inline)) {
            this->data[0][0] = cos;
            this->data[1][0] = sin;
            this->data[0][1] = -sin;
            this->data[1][1] = cos;            
        }

        inline void scale(f32 x, f32 y, f32 z) {
            this->data[0][0] = x;
            this->data[1][1] = y;
            this->data[2][2] = z;
        }

        typedef f32 ArrType[4];

        operator ArrType*() {
            return data;
        }

        operator const ArrType*() const {
            return data;
        }
    };

    template<typename T>
    struct TMatrix34 : public T {
    public:
        void mult(const JGeometry::TVec3<f32> &, const JGeometry::TVec3<f32> &) const;
    };

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
