#ifndef GXSTRUCT_H
#define GXSTRUCT_H

#include "revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXColor {
    u8  r, g, b, a;
} GXColor;

typedef struct _GXColorS10 {
    s16 r, g, b, a;
} GXColorS10;

#ifdef __cplusplus
}
#endif

#endif // GXSTRUCT_H
