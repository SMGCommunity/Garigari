#include <revolution.h>
#include "Util/MtxUtil.hpp"
struct Host43330 {
 virtual void opaque0();
 virtual void opaque1();
 virtual void opaque2();
 virtual void opaque3();
 virtual void opaque4();
 virtual void opaque5();
 virtual void opaque6();
 virtual void opaque7();
 virtual void opaque8();
 virtual void opaque9();
 virtual void opaque10();
 virtual void opaque11();
 virtual void opaque12();
 virtual void opaque13();
 virtual MtxPtr matrix() const;
};
struct View43330 { const void* vt; u8 opaque[0x28]; f32 x,y,z; u8 tail[0x67]; u8 flag; };
extern "C" {
void* fn_8023C900(void*,void*,const char*,const char*,void*,int,int);
void fn_8023CE00(void*,MtxPtr,const TVec3f&,const TVec3f&);
void fn_8000A010(void*,const char*);
void registerDemoSimpleCastAll__2MRFP9LiveActor(void*);
extern const char lbl_80695FA8[];
extern const void* lbl_80695FD8[];
extern const f32 lbl_807DC5C8,lbl_807DC5CC,lbl_807DC5D0;
}
extern "C" View43330* fn_80243330(View43330* obj,Host43330* host,void* arg,f32 radius,f32 length) {
 const char* pool=lbl_80695FA8;
 fn_8023C900(obj,host,pool,pool+12,arg,-1,0);
 obj->vt=lbl_80695FD8;obj->flag=0;
 if(!arg)fn_8023CE00(obj,host->matrix(),TVec3f(lbl_807DC5C8,lbl_807DC5C8,lbl_807DC5C8),TVec3f(lbl_807DC5C8,lbl_807DC5C8,lbl_807DC5C8));
 obj->x=obj->z=radius/lbl_807DC5CC;obj->y=length/lbl_807DC5D0;
 fn_8000A010(obj,pool+28);registerDemoSimpleCastAll__2MRFP9LiveActor(obj);return obj;
}
