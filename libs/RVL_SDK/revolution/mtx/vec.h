#ifndef VEC_H
#define VEC_H

#include "revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec, *VecPtr;

f32 PSVECDistance(const Vec *, const Vec *);
f32 C_VECMag(const Vec *);

#ifdef __cplusplus
}
#endif

#endif // VEC_H
