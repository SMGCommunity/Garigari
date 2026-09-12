#pragma once

#include <revolution.h>

namespace JMath {
    inline void gekko_ps_copy12(__REGISTER void* pDest, __REGISTER const void* pSrc) {
#ifdef __MWERKS__
        register f32 f_0, f_1, f_2, f_3, f_4, f_5;

        __asm {
            psq_l     f_0, 0(pSrc), 0, 0
            psq_l     f_1, 8(pSrc), 0, 0
            psq_l     f_2, 0x10(pSrc), 0, 0
            psq_l     f_3, 0x18(pSrc), 0, 0
            psq_l     f_4, 0x20(pSrc), 0, 0
            psq_l     f_5, 0x28(pSrc), 0, 0
            psq_st    f_0, 0(pDest), 0, 0
            psq_st    f_1, 8(pDest), 0, 0
            psq_st    f_2, 0x10(pDest), 0, 0
            psq_st    f_3, 0x18(pDest), 0, 0
            psq_st    f_4, 0x20(pDest), 0, 0
            psq_st    f_5, 0x28(pDest), 0, 0
        }
        ;
#endif
    }

    inline void gekko_ps_copy16(__REGISTER void* pDest, __REGISTER const void* pSrc) {
#ifdef __MWERKS__
        register f32 f_0, f_1, f_2, f_3, f_4, f_5, f_6, f_7;

        __asm {
            psq_l     f_0, 0(pSrc), 0, 0
            psq_l     f_1, 8(pSrc), 0, 0
            psq_l     f_2, 0x10(pSrc), 0, 0
            psq_l     f_3, 0x18(pSrc), 0, 0
            psq_l     f_4, 0x20(pSrc), 0, 0
            psq_l     f_5, 0x28(pSrc), 0, 0
            psq_l     f_6, 0x30(pSrc), 0, 0
            psq_l     f_7, 0x38(pSrc), 0, 0
            psq_st    f_0, 0(pDest), 0, 0
            psq_st    f_1, 8(pDest), 0, 0
            psq_st    f_2, 0x10(pDest), 0, 0
            psq_st    f_3, 0x18(pDest), 0, 0
            psq_st    f_4, 0x20(pDest), 0, 0
            psq_st    f_5, 0x28(pDest), 0, 0
            psq_st    f_6, 0x30(pDest), 0, 0
            psq_st    f_7, 0x38(pDest), 0, 0
        }
        ;
#endif
    }
};  // namespace JMath

namespace JMathInlineVEC {
    inline void PSVECAdd(__REGISTER const Vec* vec1, __REGISTER const Vec* vec2, __REGISTER Vec* dst) ALWAYS_INLINE {
#ifdef __MWERKS__
        register f32 v1z, v2z, d1z, d1xy, v2xy, v1xy;
        __asm {            
            psq_l     v1xy, 0(vec1), 0, 0
            psq_l     v2xy, 0(vec2), 0, 0
            ps_add    d1xy, v1xy, v2xy
            psq_st    d1xy, 0(dst), 0, 0
            
            psq_l     v1z,   8(vec1), 1, 0
            psq_l     v2z,   8(vec2), 1, 0
            ps_add    d1z, v1z, v2z
            psq_st    d1z,  8(dst), 1, 0
        }
#endif
    }

    inline void PSVECSubtract(__REGISTER const Vec* vec1, __REGISTER const Vec* vec2, __REGISTER Vec* dst) ALWAYS_INLINE {
#ifdef __MWERKS__
        register f32 v1xy, v2xy, dxy, v1z, v2z, dz;
        __asm {
            psq_l     v1xy, 0(vec1), 0, 0
            psq_l     v2xy, 0(vec2), 0, 0
            psq_l     v1z,   8(vec1), 1, 0
            ps_sub    dxy, v1xy, v2xy
            psq_l     v2z,   8(vec2), 1, 0
            ps_sub    dz, v1z, v2z
            psq_st    dxy, 0(dst), 0, 0
            psq_st    dz,  8(dst), 1, 0            
        }
#endif
    }

    inline void PSVECNegate(register const Vec* src, register Vec* dst) ALWAYS_INLINE {
#ifdef __MWERKS__
        register f32 xy;
        __asm {
            psq_l xy, 0(src), 0, 0
            ps_neg xy, xy
            psq_st xy, 0(dst), 0, 0
        }
        dst->z = -src->z;
#endif
    }

    inline f32 PSVECSquareMag(__REGISTER const Vec* src) ALWAYS_INLINE {
#ifdef __MWERKS__
        register f32 z, xy, ret;
        __asm {
            psq_l xy, 0(src), 0, 0
            ps_mul xy, xy, xy
            lfs z, 8(src)            
            ps_madd ret, z, z, xy
            ps_sum0 ret, ret, xy, xy            
        }
        return ret;
#endif
    }
    f32 PSVECDotProduct(const Vec*, const Vec*);
};

void JMAVECScaleAdd(const Vec *, const Vec *, Vec *, f32);
