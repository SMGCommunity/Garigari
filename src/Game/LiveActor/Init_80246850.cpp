#include "LiveActor/LiveActor.hpp"
struct View46850 : LiveActor { f32 position[3]; f32 value9C[4]; s32 arg; void* pointer; bool flag; };
extern "C" {
extern const char lbl_806964D8[];
extern const u32 lbl_807D34D0;
extern const f32 lbl_807DC634,lbl_807DC644,lbl_807DC648;
void initDefaultPos__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
void initActor__2MRFP9LiveActorRC12JMapInfoIterPCcb(void*,const void*,const char*,bool);
void fn_8004AE10(void*);
bool getJMapInfoArg0NoInit__2MRFRC12JMapInfoIterPl(const void*,s32*);
bool getJMapInfoArg1NoInit__2MRFRC12JMapInfoIterPl(const void*,s32*);
void* getJointMtx__2MRFPC9LiveActorPCc(const void*,const char*);

void fn_8004D8A0(void*,int);
void fn_8005C0D0(void*,const TVec3f*,f32);
void fn_800315C0(void*,f32);
void fn_800316E0(void*);
void startAction__2MRFPC9LiveActorPCc(const void*,const char*);
void fn_800099E0(void*);
void fn_80009BB0(void*,f32);
void useStageSwitchSyncAppear__2MRFP9LiveActorRC12JMapInfoIter(void*,const void*);
}
namespace MR { void addHitSensorMtxAnimal(LiveActor*,const char*,u16,f32,MtxPtr,const TVec3f&); }
extern "C" void fn_80246850(View46850* obj,const void* iter) {
 initDefaultPos__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
 obj->position[0]=obj->mPosition.x;obj->position[1]=obj->mPosition.y;obj->position[2]=obj->mPosition.z;
 initActor__2MRFP9LiveActorRC12JMapInfoIterPCcb(obj,iter,lbl_806964D8,false);
 fn_8004AE10(obj);getJMapInfoArg0NoInit__2MRFRC12JMapInfoIterPl(iter,&obj->arg);
 obj->initHitSensor(1);
 TVec3f offset;offset.x=lbl_807DC634;offset.y=lbl_807DC634;offset.z=lbl_807DC634;
 void* matrix=getJointMtx__2MRFPC9LiveActorPCc(obj,lbl_806964D8+0x14);
 MR::addHitSensorMtxAnimal(obj,lbl_806964D8+0xc,8,lbl_807DC644,static_cast<MtxPtr>(matrix),offset);
 obj->initBinder(lbl_807DC644,lbl_807DC634,0);
 const TVec3f& soundOffset=TVec3f(lbl_807DC634);
 obj->initSound(2,lbl_806964D8,0,soundOffset);
 s32 arg1=-1;getJMapInfoArg1NoInit__2MRFRC12JMapInfoIterPl(iter,&arg1);
 if(arg1==-1)fn_8004D8A0(obj,1);else obj->flag=true;
 TVec3f offset2;offset2.x=lbl_807DC634;offset2.y=lbl_807DC634;offset2.z=lbl_807DC634;
 fn_8005C0D0(obj,&offset2,lbl_807DC648);fn_800315C0(obj,lbl_807DC644);fn_800316E0(obj);
 obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D0),0);
 startAction__2MRFPC9LiveActorPCc(obj,lbl_806964D8);fn_800099E0(obj);
 fn_80009BB0(obj,static_cast<f32>(obj->arg));
 useStageSwitchSyncAppear__2MRFP9LiveActorRC12JMapInfoIter(obj,iter);
}
