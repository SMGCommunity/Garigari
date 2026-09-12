#pragma once

#include <revolution.h>
#include <JGeometry/TUtil.hpp>
#include <JMath.hpp>


namespace JGeometry {
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

    inline void setTVec3f(const f32* a, f32* b) ALWAYS_INLINE {
#ifdef __MWERKS__
        const register f32* v_a = a;
        register f32* v_b = b;

        register f32 b_x;
        register f32 a_x;

        asm{
            psq_l a_x, 0(v_a), 0, 0
            lfs b_x, 8(v_a)
            psq_st a_x, 0(v_b), 0, 0
            stfs b_x, 8(v_b)
        };
#endif
    }

    template<>
    struct TVec3< f32 > : public Vec {
        TVec3(const Vec& vec) {
            setTVec3f(&vec.x, &x);
        }
        TVec3(const TVec3<f32>& vec) NO_INLINE {
            setTVec3f(&vec.x, &x);
        }
        TVec3(f32 _x, f32 _y, f32 _z) NO_INLINE {
            x = _x;
            y = _y;
            z = _z;
        }
        // Why does NO_INLINE have to come first here, but not elsewhere???
        template < typename T >
        NO_INLINE TVec3(T _x, T _y, T _z) {
            x = _x;
            y = _y;
            z = _z;
        }
        TVec3(f32 val) NO_INLINE {
            z = y = x = val;
        }
        TVec3() {}


        // ASSIGN
        TVec3& operator=(const TVec3& b) NO_INLINE {
            setTVec3f(&b.x, &x);
            return *this;
        }

        template < typename T >
        void set(const TVec3< T >& rVec) {
            x = rVec.x;
            y = rVec.y;
            z = rVec.z;
        }        
        template < typename T >
        void set(T _x, T _y, T _z) NO_INLINE {
            x = _x;
            y = _y;
            z = _z;
        }
        template < typename T >
        void set(int x, int y, int z);
        void set(f32 x_, f32 y_, f32 z_) {
            x = x_;
            y = y_;
            z = z_;
        }
        void set(const Vec& rVec) {
            x = rVec.x;
            y = rVec.y;
            z = rVec.z;
        }
        void setTrans(MtxPtr mtx) {
            set((*mtx)[3], (*mtx)[7], (*mtx)[11]);
        }
        void setPS(const TVec3<f32>& rVec) {
            setTVec3f(&rVec.x, &x);
        }
        




        
        // ADDITION
        TVec3& operator+=(const TVec3& op) {
            add(op);
            return *this;
        }
        void add(const TVec3<f32>& b) {
            JMathInlineVEC::PSVECAdd(this, &b, this);
        }
        TVec3 addInline(const TVec3& op) const {
            TVec3 ret(*this);
            ret.add(op);
            return ret;
        }


        // SUBTRACT
        TVec3& operator-=(const TVec3& op) {
            sub(op);
            return *this;
        }
        void sub(const TVec3<f32>& b) {
            JMathInlineVEC::PSVECSubtract(this, &b, this);
        }
        TVec3 subInline(const TVec3& op) const {
            TVec3 ret(*this);
            ret.sub(op);
            return ret;
        }


        // MULTIPLY
        void scale(f32 scale) {
            x *= scale;
            y *= scale;
            z *= scale;
        }
        TVec3 scaleInline(f32 scalar) const {
            TVec3 ret(*this);
            ret.scale(scalar);
            return ret;
        }


        // DIVIDE


        // NEGATE
        TVec3 operator-() const {
            return this->negateInline();
        }
        void negate() {
            JMathInlineVEC::PSVECNegate(this, this);
        }
        inline TVec3 negateInline() const {
            TVec3 ret(*this);
            ret.negate();
            return ret;
        }


        // CONVERT
        operator Vec* () {
            return (Vec*)&x;
        }
        operator const Vec* () const {
            return (Vec*)&x;
        }


        // MATH
        f32 squareMag() const {
            return JMathInlineVEC::PSVECSquareMag(this);
        }
        f32 dot(const TVec3&) const;
        bool epsilonEquals(const TVec3<f32>& a1, f32 a2) const {
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

};

typedef JGeometry::TVec3<f32> TVec3f;