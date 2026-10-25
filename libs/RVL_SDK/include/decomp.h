#ifndef DECOMP_H
#define DECOMP_H

/*******************************************************************************
 * Unknown objects
 */

#define unk1_t char
#define unk2_t short
#define unk4_t int
#define unk8_t long long

#define unk_t unk4_t

#define EXTERN_UNKNOWN_FUNC_NO_ARGS(ret, addr) extern "C" ret fn_ ## addr ();
#define EXTERN_UNKNOWN_FUNC(ret, addr, ...) extern "C" ret fn_ ## addr (__VA_ARGS__);

#endif  // DECOMP_H
