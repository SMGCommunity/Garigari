#include "LiveActor/View442B0.hpp"
extern "C" {
bool fn_8001E480(const void*);
bool fn_80244640(View442B0*);
f32 calcDistanceToPlayer__2MRFPC9LiveActor(const void*);
bool isValidSwitchB__2MRFPC9LiveActor(const void*);
bool isOnSwitchB__2MRFPC9LiveActor(const void*);
bool isHiddenModel__2MRFPC9LiveActor(const void*);
bool fn_80009660(const void*,const char*);
void fn_80034350(void*);
void showModel__2MRFP9LiveActor(void*);
void tryStartAllAnim__2MRFPC9LiveActorPCc(const void*,const char*);
void setNerve__9LiveActorFPC5Nerve(void*,const void*);
extern const f32 lbl_807DC5F0,lbl_807DC5EC;
extern const u32 lbl_807D34C0,lbl_807D34C4;
extern const char lbl_80696100[],lbl_80696108[];
}
inline bool suppress44790(const View442B0* obj) ALWAYS_INLINE {
 bool result=false;
 if(obj->flag91 && !fn_8001E480(obj))result=true;
 return result;
}
extern "C" void fn_80244790(View442B0* obj) {
 if(suppress44790(obj))return;
 fn_80244640(obj);
 f32 limit=lbl_807DC5EC*(lbl_807DC5F0+obj->value);
 if(limit<calcDistanceToPlayer__2MRFPC9LiveActor(obj) ||
    (isValidSwitchB__2MRFPC9LiveActor(obj) && isOnSwitchB__2MRFPC9LiveActor(obj))) {
  tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696108);
  setNerve__9LiveActorFPC5Nerve(obj,&lbl_807D34C4);
 }
}
extern "C" void fn_80244860(View442B0* obj) {
 if(suppress44790(obj))return;
 fn_80244640(obj);
 if(!isHiddenModel__2MRFPC9LiveActor(obj) && fn_80009660(obj,lbl_80696108))fn_80034350(obj);
 f32 limit=lbl_807DC5EC*obj->value;
 if(calcDistanceToPlayer__2MRFPC9LiveActor(obj)<limit &&
    (!isValidSwitchB__2MRFPC9LiveActor(obj) || !isOnSwitchB__2MRFPC9LiveActor(obj))) {
  showModel__2MRFP9LiveActor(obj);
  tryStartAllAnim__2MRFPC9LiveActorPCc(obj,lbl_80696100);
  setNerve__9LiveActorFPC5Nerve(obj,&lbl_807D34C0);
 }
}
