/**
 * mem_TRK.c
 * Description:
 */

#include "MetroTRK/Portable/mem_TRK.h"
#include "ppc/Generic/ppc_mem.h"

void* TRK_memcpy(void* dst, const void* src, int n) {
    const u8* s = (const u8*)src;
    u8* d = (u8*)dst;
    int i;

    for (i = 0; i != n; i++) {
        ppc_writebyte1(d, ppc_readbyte1(s));
        s++;
        d++;
    }

    return dst;
}

void TRK_fill_mem(void* dst, int val, int n) {
    u8 v = val;
    u8* d = (u8*)dst;
    int i;

    for (i = 0; i != n; i++) {
        ppc_writebyte1(d, v);
        d++;
    }
}

void* TRK_memset(void* dst, int val, int n) {
    TRK_fill_mem(dst, val, n);

    return dst;
}
