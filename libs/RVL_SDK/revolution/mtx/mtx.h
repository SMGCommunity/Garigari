#ifndef MTX_H
#define MTX_H

#include "revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

#define MTXDegToRad(deg) ((deg) * 0.01745329252f)
#define MTXRadToDeg(rad) ((rad) * 57.29577951f)

#ifdef __cplusplus
}
#endif

#endif // MTX_H
