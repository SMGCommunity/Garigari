#ifndef OSUTF_H
#define OSUTF_H

#include "revolution.h"

#ifdef __cplusplus
extern "C" {
#endif

char* OSUTF8to32(const char *, u32 *);
u32* OSUTF16to32(const u16 *, u32 *);
u8 OSUTF32toANSI(u32);
u16 OSUTF32toSJIS(u32);

#ifdef __cplusplus
}
#endif

#endif // OSUTF_H
