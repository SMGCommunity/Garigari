#include <revolution.h>
struct ModelEE0 { u8 opaque[8]; void* data; };
struct ViewEE0 {
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
 virtual void invoke();
 u8 opaque[0x8C]; ModelEE0* model; void* data; void* item;
};
struct MemberEE0 { u32 words[3]; };
struct CallbackEE0 { const void* vt; void* obj; MemberEE0 member; };
extern "C" {
void* __ct__9LiveActorFPCc(void*,const char*);
void initActor__2MRFP9LiveActorPCcb(void*,const char*,bool);
ModelEE0* fn_80043020(void*,int);
void fn_8004B920(const void*,int);
extern const void* lbl_80695F38[];
extern const void* lbl_80695F28[];
extern const MemberEE0 lbl_80695F18;
}
extern "C" ViewEE0* fn_80242EE0(ViewEE0* obj,void*,const char* name,const char* resource,int index) {
 __ct__9LiveActorFPCc(obj,name);
 *(const void**)obj=lbl_80695F38;
 obj->model=0;obj->data=0;obj->item=0;
 if(index>=0) {
 CallbackEE0 callback;
 callback.vt=lbl_80695F28;callback.obj=obj;
 callback.member=lbl_80695F18;
 fn_8004B920(&callback,index);
 }
 initActor__2MRFP9LiveActorPCcb(obj,resource,false);
 obj->model=fn_80043020(obj,0);obj->data=obj->model->data;
 obj->item=**(void***)((u8*)obj->data+0x3C);
 obj->invoke();return obj;
}
