#include <revolution.h>
struct View43BD0 { u8 opaque[0xac]; f32 value,step; };
extern "C" const f32 lbl_807DC5D8,lbl_807DC5DC;
extern "C" bool fn_80243C60(const void*);
extern "C" void showModel__2MRFP9LiveActor(void*);
extern "C" void fn_80034350(void*);
inline f32 clamp43BD0(f32 v) __attribute__((always_inline)) {
 if(v<lbl_807DC5DC)return lbl_807DC5DC;
 if(v>lbl_807DC5D8)return lbl_807DC5D8;
 return v;
}
extern "C" void fn_80243BD0(View43BD0* obj) {
 obj->value+=obj->step;obj->value=clamp43BD0(obj->value);
 if(fn_80243C60(obj))showModel__2MRFP9LiveActor(obj);else fn_80034350(obj);
}
