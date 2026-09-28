#ifndef OS_H
#define OS_H

#include "revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_BASE_CACHED (0x8000 << 16)
#define OS_BASE_UNCACHED (0xC000 << 16)

#define OSPhysicalToCached(paddr) ((void*) ((u32)(paddr) + OS_BASE_CACHED))

#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

void OSReport(const char*, ...);

#ifdef __cplusplus
}
#endif

#include "revolution/base/PPCArch.h"
#include "revolution/os/OSContext.h"
#include "revolution/os/OSException.h"
#include "revolution/os/OSInterrupt.h"
#include "revolution/os/OSTime.h"

#endif // OS_H
