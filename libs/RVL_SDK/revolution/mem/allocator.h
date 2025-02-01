#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMAllocator MEMAllocator;
typedef void* (*MEMFuncAllocatorAlloc)( MEMAllocator *, u32);
typedef void  (*MEMFuncAllocatorFree) ( MEMAllocator *, void *);
typedef struct MEMAllocatorFunc MEMAllocatorFunc;

struct MEMAllocatorFunc {
    MEMFuncAllocatorAlloc pfAlloc;
    MEMFuncAllocatorFree pfFree;
};

struct MEMAllocator {
    MEMAllocatorFunc const* pFunc;
    void* pHeap;
    u32 heapParam1;
    u32 heapParam2;
};

void* MEMAllocFromAllocator(MEMAllocator *, u32);
void MEMFreeToAllocator(MEMAllocator *, void *);

#ifdef __cplusplus
}
#endif

#endif // ALLOCATOR_H
