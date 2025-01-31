#ifndef OS_H
#define OS_H

#ifdef __cplusplus
extern "C" {
#endif

#define OS_BASE_CACHED (0x8000 << 16)
#define OS_BASE_UNCACHED (0xC000 << 16)

#define OSPhysicalToCached(paddr) ((void*) ((u32)(paddr) + OS_BASE_CACHED))

#ifdef __cplusplus
}
#endif

#endif // OS_H
