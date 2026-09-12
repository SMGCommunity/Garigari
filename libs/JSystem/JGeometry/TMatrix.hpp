#pragma once

#include <revolution.h>
#include <revolution/mtx/vec.h>
#include <JMath.hpp>
#include <JGeometry/TVec.hpp>

namespace JGeometry {
    template <typename T>
    struct SMatrix34C {
        typedef f32 ArrType[4];
        void set(const ArrType* pSrc) {
            JMath::gekko_ps_copy12(this, pSrc);
        }
        void set(const SMatrix34C< T >& rSrc) {
            JMath::gekko_ps_copy12(this, rSrc);
        }
        void set(T rxx, T ryx, T rzx, T tx, T rxy, T ryy, T rzy, T ty, T rxz, T ryz, T rzz, T tz);


        operator ArrType* () {
            return mMtx;
        }
        operator const ArrType* () const {
            return mMtx;
        }


        T mMtx[3][4];
    };

    template<>
    struct SMatrix34C< f32 > {
        f32 mMtx[3][4];

        inline void rotateX(f32 cos, f32 sin) ALWAYS_INLINE {
            this->mMtx[1][1] = cos;
            this->mMtx[2][1] = sin;
            this->mMtx[1][2] = -sin;
            this->mMtx[2][2] = cos;
        }

        inline void rotateY(f32 cos, f32 sin) ALWAYS_INLINE {
            this->mMtx[0][0] = cos;
            this->mMtx[0][2] = sin;
            this->mMtx[2][0] = -sin;
            this->mMtx[2][2] = cos;
        }

        inline void rotateZ(f32 cos, f32 sin) ALWAYS_INLINE {
            this->mMtx[0][0] = cos;
            this->mMtx[1][0] = sin;
            this->mMtx[0][1] = -sin;
            this->mMtx[1][1] = cos;
        }

        inline void scale(f32 x, f32 y, f32 z) {
            this->mMtx[0][0] = x;
            this->mMtx[1][1] = y;
            this->mMtx[2][2] = z;
        }

        typedef f32 ArrType[4];

        operator ArrType* () {
            return mMtx;
        }

        operator const ArrType* () const {
            return mMtx;
        }
    };

    template<typename T>
    struct TMatrix34 : public T {
    public:
        void identity();
        void mult(const JGeometry::TVec3<f32>&, const JGeometry::TVec3<f32>&) const;
    };

    template < class T >
    struct TRotation3 : public T {
    public:
        void setXYZDir(const TVec3f& rSrcX, const TVec3f& rSrcY, const TVec3f& rSrcZ) NO_INLINE {
            setXYZDirInline(rSrcX, rSrcY, rSrcZ);
        }



        inline void setXDirInline(f32 x, f32 y, f32 z) ALWAYS_INLINE {
            this->mMtx[0][0] = x;
            this->mMtx[1][0] = y;
            this->mMtx[2][0] = z;
        }
        inline void setXDirInline(const TVec3f& rSrc) ALWAYS_INLINE {
            f32 z = mMtx[2][0];
            f32 y = mMtx[1][0];
            f32 x = mMtx[0][0];
            rSrc.set<f32>(x, y, z);
        }

        inline void setYDirInline(f32 x, f32 y, f32 z) ALWAYS_INLINE {
            this->mMtx[0][1] = x;
            this->mMtx[1][1] = y;
            this->mMtx[2][1] = z;
        }
        inline void setYDirInline(const TVec3f& rSrc) ALWAYS_INLINE {
            f32 z = mMtx[2][1];
            f32 y = mMtx[1][1];
            f32 x = mMtx[0][1];
            rSrc.set<f32>(x, y, z);
        }

        inline void setZDirInline(f32 x, f32 y, f32 z) ALWAYS_INLINE {
            this->mMtx[0][2] = x;
            this->mMtx[1][2] = y;
            this->mMtx[2][2] = z;
        }
        inline void setZDirInline(TVec3f& rSrc) ALWAYS_INLINE {
            f32 z = mMtx[2][2];
            f32 y = mMtx[1][2];
            f32 x = mMtx[0][2];
            rSrc.set<f32>(x, y, z);
        }
    
        inline void setXYZDirInline(const TVec3f& rSrcX, const TVec3f& rSrcY, const TVec3f& rSrcZ) ALWAYS_INLINE {
            this->mMtx[0][0] = rSrcX.x;
            this->mMtx[1][0] = rSrcX.y;
            this->mMtx[2][0] = rSrcX.z;
            this->mMtx[0][1] = rSrcY.x;
            this->mMtx[1][1] = rSrcY.y;
            this->mMtx[2][1] = rSrcY.z;
            this->mMtx[0][2] = rSrcZ.x;
            this->mMtx[1][2] = rSrcZ.y;
            this->mMtx[2][2] = rSrcZ.z;
        }


        void setRotate(const TVec3f&, f32);
    };

    template < class T >
    struct TPosition3 : public TRotation3< T > {
    public:
        TPosition3() {};


        void getTrans(TVec3f& rDest) const;

        void setTrans(const TVec3f& rSrc) {
            this->mMtx[0][3] = rSrc.x;
            this->mMtx[1][3] = rSrc.y;
            this->mMtx[2][3] = rSrc.z;
        }
    };
};


typedef JGeometry::SMatrix34C< f32 > TSMtxf;
typedef JGeometry::TMatrix34< TSMtxf > TMtx34f;
typedef JGeometry::TRotation3< TMtx34f > TRot3f;
typedef JGeometry::TPosition3< TMtx34f > TPos3f;
