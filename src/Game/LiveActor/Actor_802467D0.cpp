#include <revolution.h>
struct View467D0 { const void* vtable; u8 base[0x8c]; f32 position[3]; f32 value9C[4]; s32 arg; void* pointer; bool flag; };
extern "C" {
void* __ct__9LiveActorFPCc(void*,const char*);
extern const void* lbl_80696510[];
extern const f32 gZeroVec[3],lbl_807DC634,lbl_807DC630;
void fn_80044550(void*,const void*);
void fn_80007BA0(void*,f32,f32,f32,f32);
}
extern "C" View467D0* fn_802467D0(View467D0* obj,const char* name) {
 __ct__9LiveActorFPCc(obj,name);
 obj->vtable=lbl_80696510;
 fn_80044550(obj->position,gZeroVec);
 obj->arg=0;obj->pointer=0;obj->flag=false;
 fn_80007BA0(obj->value9C,lbl_807DC634,lbl_807DC634,lbl_807DC634,lbl_807DC630);
 return obj;
}
