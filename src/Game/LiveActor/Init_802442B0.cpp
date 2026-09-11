#include "LiveActor/View442B0.hpp"
extern "C" {
extern const u32 lbl_807D34C8,lbl_807D34C4;
extern const f32 lbl_807DC5EC;
void initDefaultPos__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
void getObjectName__2MRFPPCcRC12JMapInfoIter(const char**,const void*);
void initUseStageSwitchReadA__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
void initUseStageSwitchReadB__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
void getJMapInfoArg0NoInit__2MRFRC12JMapInfoIterPf(const void*,f32*);
void getJMapInfoArg1NoInit__2MRFRC12JMapInfoIterPl(const void*,s32*);
void getJMapInfoArg2NoInit__2MRFRC12JMapInfoIterPl(const void*,s32*);
void tryStartAllAnim__2MRFPC9LiveActorPCc(const void*,const char*);
void setClippingTypeSphereContainsModelBoundingBox__2MRFP9LiveActorf(void*,f32);
void setGroupClipping__2MRFP9LiveActorRC12JMapInfoIteri(void*,const void*,int);
void initNerve__9LiveActorFPC5Nervel(void*,const void*,s32);
void registerDemoSimpleCastAll__2MRFP9LiveActor(void*);
void useStageSwitchAwake__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
bool fn_8001F360(void*,const void*);
Callback442B0 fn_802444F0(void*,Method442B0);
bool fn_8001F3D0(void*,const Callback442B0*,const char*);
}
extern "C" void fn_802442B0(View442B0* obj,const void* iter) {
 initDefaultPos__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
 const char* name=0;getObjectName__2MRFPPCcRC12JMapInfoIter(&name,iter);
 obj->slot74(name);obj->slot70();
 initUseStageSwitchReadA__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
 initUseStageSwitchReadB__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
 getJMapInfoArg0NoInit__2MRFRC12JMapInfoIterPf(iter,&obj->value);
 s32 arg1=-1;getJMapInfoArg1NoInit__2MRFRC12JMapInfoIterPl(iter,&arg1);
 obj->flag91=arg1!=-1;
 s32 arg2=-1;getJMapInfoArg2NoInit__2MRFRC12JMapInfoIterPl(iter,&arg2);
 bool nerve=arg2!=-1;
 tryStartAllAnim__2MRFPC9LiveActorPCc(obj,name);
 setClippingTypeSphereContainsModelBoundingBox__2MRFP9LiveActorf(obj,lbl_807DC5EC);
 obj->slot78();setGroupClipping__2MRFP9LiveActorRC12JMapInfoIteri(obj,iter,16);
 if(nerve)initNerve__9LiveActorFPC5Nervel(obj,&lbl_807D34C8,0);
 else initNerve__9LiveActorFPC5Nervel(obj,&lbl_807D34C4,0);
 registerDemoSimpleCastAll__2MRFP9LiveActor(obj);
 useStageSwitchAwake__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
 if(fn_8001F360(obj,iter)) {
  bool registered=true;
  const Callback442B0& first=fn_802444F0(obj,&View442B0::fn_80244730);
  if(!fn_8001F3D0(obj,&first,"\x8f\xc1\x96\xc5")) {
   const Callback442B0& second=fn_802444F0(obj,&View442B0::fn_802446D0);
   if(!fn_8001F3D0(obj,&second,0))registered=false;
  }
  if(registered)obj->makeActorDead();
 } else obj->appear();
}
