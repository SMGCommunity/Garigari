#include <revolution/types.h>
struct Actor4B920 { const void* vtable;u8 opaque[0xa4];f32 a8,ac,b0,b4,b8,bc,c0,c4,c8,cc,d0; };
extern "C" {
void* __ct__9LiveActorFPCc(void*,const char*);
extern const void* lbl_806969A8[];
extern const f32 lbl_807DC6B4,lbl_807DC6B8,lbl_807DC6B0;
Actor4B920* fn_8024B920(Actor4B920* obj,const char* name) {
 __ct__9LiveActorFPCc(obj,name);
 obj->vtable=lbl_806969A8;
 obj->a8=lbl_807DC6B4;obj->ac=lbl_807DC6B4;obj->b0=lbl_807DC6B4;
 obj->b4=lbl_807DC6B4;obj->b8=lbl_807DC6B4;obj->bc=lbl_807DC6B4;
 obj->c0=lbl_807DC6B8;obj->c4=lbl_807DC6B8;obj->c8=lbl_807DC6B4;
 obj->cc=lbl_807DC6B0;obj->d0=lbl_807DC6B4;
 return obj;
}
}
