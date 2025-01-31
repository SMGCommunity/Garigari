#ifndef FLIPPER_H
#define FLIPPER_H

#include <revolution/types.h>
#include <revolution/os.h>

#ifdef __MWERKS__
vu16 __VIRegs[0x3B] : OS_BASE_UNCACHED + 0xC002000;
#else
vu16 __VIRegs[0x3B];
#endif

#endif // FLIPPER_H
