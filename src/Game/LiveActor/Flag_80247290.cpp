#include "LiveActor/LiveActor.hpp"
struct View47290 : LiveActor { u8 opaque[0x24]; bool flag; };
extern "C" {
bool fn_8005DEF0(void*,f32*,void*);
bool fn_8004DA50(void*,const TVec3f*,f32,f32,int,void*);
extern const f32 lbl_807DC664,lbl_807DC668;
}
extern "C" bool fn_80247290(View47290* obj,void* target) {
 if(obj->flag)return false;
 f32 value;
 if(!fn_8005DEF0(obj,&value,target))return false;
 if(lbl_807DC664<value)return false;
 if(!fn_8004DA50(obj,&obj->mPosition,lbl_807DC664,lbl_807DC668,1,0))return false;
 obj->flag=true;
 return true;
}
