#include <revolution/types.h>
struct Actor4C210 { const void* vtable;u8 opaque[0x8c];f32 value; };
extern "C" {
void* __ct__9LiveActorFPCc(void*,const char*);
extern const void* lbl_80696A98[];
extern const f32 lbl_807DC6C8;
Actor4C210* fn_8024C210(Actor4C210* obj,const char* name) {
 __ct__9LiveActorFPCc(obj,name);
 obj->vtable=lbl_80696A98;
 obj->value=lbl_807DC6C8;
 return obj;
}
}
