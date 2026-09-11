#include <revolution.h>
struct View47B40 { const void* vtable; u8 base[0x10]; void* entries; u32 value18,value1C; u8 opaque[0x80]; u32 valueA0; void* argument; bool flagA8,flagA9; };
extern "C" {
void* __ct__7NameObjFPCc(void*,const char*);
extern const char lbl_806965F0[];
extern const void* lbl_80696610[];
void fn_802570C0(void*);
void* __construct_new_array(void*,void(*)(void*),void(*)(void*),u32,u32);
}
extern "C" View47B40* fn_80247B40(View47B40* obj,void* argument) {
 __ct__7NameObjFPCc(obj,lbl_806965F0);
 obj->vtable=lbl_80696610;
 obj->entries=0;obj->value18=0;obj->value1C=0;obj->valueA0=0;obj->argument=argument;obj->flagA8=false;obj->flagA9=true;
 obj->entries=__construct_new_array(::operator new[](0x1190),fn_802570C0,0,0x8c,32);
 return obj;
}
