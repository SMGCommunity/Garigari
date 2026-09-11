#include <revolution.h>
struct View43460 { u8 opaque[0x9F]; u8 flag; };
extern "C" {
bool fn_8000E080(const void*,f32);
bool fn_800098F0(const void*);
void fn_8000A010(void*,const char*);
extern const f32 lbl_807DC5D0;
extern const char lbl_80695FCC[],lbl_80695FC4[];
}
extern "C" void fn_80243460(View43460* obj) {
 if(fn_8000E080(obj,lbl_807DC5D0)) {
 if(!obj->flag && fn_800098F0(obj)) { fn_8000A010(obj,lbl_80695FCC);obj->flag=1; }
 } else {
 if(obj->flag && fn_800098F0(obj)) { fn_8000A010(obj,lbl_80695FC4);obj->flag=0; }
 }
}
