#ifndef PPC_GENERIC_PPC_MEM_H
#define PPC_GENERIC_PPC_MEM_H

#include <revolution/types.h>

static u8 ppc_readbyte1(const u8* ptr) {
    u32* alignedPtr = (u32*)((u32)ptr & ~3);
    return (u8)(*alignedPtr >> ((3 - ((u32)ptr - (u32)alignedPtr)) << 3));
}

static void ppc_writebyte1(u8* ptr, u8 val) {
    u32* alignedPtr = (u32*)((u32)ptr & ~3);
    u32 v = *alignedPtr;
    u32 mask = 0xFF << ((3 - ((u32)ptr - (u32)alignedPtr)) << 3);
    u32 shift = (3 - ((u32)ptr - (u32)alignedPtr)) << 3;
    *alignedPtr = (v & ~mask) | (mask & (val << shift));
}

#endif /* PPC_GENERIC_PPC_MEM_H */
