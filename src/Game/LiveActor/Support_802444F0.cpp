#include "LiveActor/View442B0.hpp"
extern "C" {
extern const void* lbl_80696130[];
extern const char lbl_80696100[],lbl_80696108[],lbl_80696114[];
extern const u32 lbl_807D34C0,lbl_807D34C4,lbl_807D34C8;
extern const f32 lbl_807DC5EC;
void fn_8004B750(void*);
void appear__9LiveActorFv(void*);
bool isNerve__9LiveActorCFPC5Nerve(const void*,const void*);
void setNerve__9LiveActorFPC5Nerve(void*,const void*);
void tryStartAllAnim__2MRFPC9LiveActorPCc(const void*,const char*);
void fn_800093B0(void*,const char*);
f32 calcDistanceToPlayer__2MRFPC9LiveActor(const void*);
void fn_80034350(void*);
void initActor__2MRFP9LiveActorPCcb(void*,const char*,bool);
bool isValidSwitchA__2MRFPC9LiveActor(const void*);
bool isOnSwitchA__2MRFPC9LiveActor(const void*);
}
inline Callback442B0::Callback442B0(void* host,Method442B0 callback)
 : vtable(lbl_80696130),obj(host),method(callback) {}
extern "C" Callback442B0 fn_802444F0(void* obj,Method442B0 method) {
 return Callback442B0(obj,method);
}
extern "C" void fn_80244530(void* obj) { fn_8004B750(obj); }
extern "C" void fn_80244540(View442B0* obj) {
 appear__9LiveActorFv(obj);
 if(isNerve__9LiveActorCFPC5Nerve(obj,&lbl_807D34C8)) {
  tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696100);fn_800093B0(obj,lbl_80696100);
 } else {
  f32 distance=lbl_807DC5EC*obj->value;
  if(calcDistanceToPlayer__2MRFPC9LiveActor(obj)<distance) {
   tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696100);fn_800093B0(obj,lbl_80696100);
   setNerve__9LiveActorFPC5Nerve(obj,&lbl_807D34C0);
  } else {
   tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696108);fn_800093B0(obj,lbl_80696108);
   fn_80034350(obj);setNerve__9LiveActorFPC5Nerve(obj,&lbl_807D34C4);
  }
 }
}
extern "C" void fn_80244630(void* obj,const char* name) { initActor__2MRFP9LiveActorPCcb(obj,name,false); }
extern "C" bool fn_80244640(View442B0* obj) {
 if(!isValidSwitchA__2MRFPC9LiveActor(obj))return false;
 if(obj->flag90)return false;
 if(isOnSwitchA__2MRFPC9LiveActor(obj)) {
  tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696114);
  obj->flag90=true;return true;
 }
 return false;
}
void View442B0::fn_802446D0() {
 makeActorAppeared();tryStartAllAnim__2MRFPC9LiveActorPCc(this,lbl_80696100);
 setNerve__9LiveActorFPC5Nerve(this,&lbl_807D34C0);
}
void View442B0::fn_80244730() {
 makeActorAppeared();tryStartAllAnim__2MRFPC9LiveActorPCc(this,lbl_80696108);
 setNerve__9LiveActorFPC5Nerve(this,&lbl_807D34C4);
}
