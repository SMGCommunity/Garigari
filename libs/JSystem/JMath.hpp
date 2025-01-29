#pragma once

#include <revolution.h>

namespace JMathInlineVEC {
    #ifdef __MWERKS__
    __attribute__((always_inline))
    inline void PSVECAdd(register const Vec* vec1, register const Vec* vec2, register Vec* dst)
    {
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
    }
    #else
    void PSVECAdd(const Vec *, const Vec *, Vec *);
    #endif
};

f32 JMACosRadian(f32);
f32 JMASinRadian(f32);

f32 JMACosDegree(f32);
f32 JMASinDegree(f32);
