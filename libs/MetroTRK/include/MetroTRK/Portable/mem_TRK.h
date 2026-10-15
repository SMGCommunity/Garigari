#ifndef METROTRK_PORTABLE_MEM_TRK_H
#define METROTRK_PORTABLE_MEM_TRK_H

#include <revolution/types.h>
#include <size_t.h>

void* TRK_memset(void* dest, int val, int count);
void* TRK_memcpy(void* dest, const void* src, int count);
void TRK_fill_mem(void* dest, int val, int count);

#endif /* METROTRK_PORTABLE_MEM_TRK_H */
