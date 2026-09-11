#include <revolution.h>
extern "C" {
extern const s32 lbl_80648B78[];
s32 fn_8024F220(s32 value) { const s32* entries = lbl_80648B78; for (s32 i = 0; i < 3; ++i) if (entries[i] == value) return i; return -1; }
}
