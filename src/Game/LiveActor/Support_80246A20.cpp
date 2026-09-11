#include <JGeometry.hpp>
struct View46A20 { u8 opaque[0x9c]; f32 value[4]; };
extern "C" {
void fn_8002B390(void*,TVec3f*,void*,void*);
void fn_8003CC70(void*,const TVec3f*);
void fn_80246C40(void*);
bool fn_8005D3A0(void**);
f32 fn_8005D300(void*);
void fn_8005D010(void*,f32);
void fn_80247290(void*,void*);
extern const f32 lbl_807DC63C,lbl_807DC64C,lbl_807DC648;
}
extern "C" void fn_80246A20(View46A20* obj) {
 TVec3f vec;fn_8002B390(obj,&vec,0,0);
 const TVec3f& neg=-vec;
 fn_8003CC70(obj->value,&neg);
}
extern "C" void fn_80246A70(void* obj) {
 fn_80246C40(obj);
 void* target=0;
 if(fn_8005D3A0(&target)) {
  if(fn_8005D300(target)<lbl_807DC63C)fn_8005D010(obj,lbl_807DC64C);
  else fn_8005D010(obj,lbl_807DC648);
  fn_80247290(obj,target);
 }
}
