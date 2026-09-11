#include <revolution.h>
struct View43990 { const void* vt; u8 opaque[0x8c]; void* arg; void* field94; u32 color; s32 field9c; f32 x,y,z,a,b; bool flag; };
struct Callback43990 { const void* vt; void (*fn)(); };
extern "C" {
void __ct__9LiveActorFPCc(void*,const char*);
void fn_8012CF90(void*,int,int,int,int);
void fn_800220D0();
void fn_8004B970(const Callback43990*,int);
void initActor__2MRFP9LiveActorPCcb(void*,const char*,bool);
void connectToScene__2MRFP9LiveActoriiii(void*,int,int,int,int);
void invalidateClipping__2MRFP9LiveActor(void*);
extern const void* lbl_80696058[],*lbl_80681C10[];
extern const f32 lbl_807DC5E4,lbl_807DC5D8,lbl_807DC5DC;
}
extern "C" View43990* fn_80243990(View43990* obj,const char* name,const char* resource,void* arg,int scene) {
 __ct__9LiveActorFPCc(obj,name);obj->vt=lbl_80696058;obj->arg=arg;obj->field94=0;
 fn_8012CF90(&obj->color,255,169,0,255);
 obj->field9c=1;obj->x=lbl_807DC5E4;obj->y=lbl_807DC5E4;obj->z=lbl_807DC5E4;
 obj->a=lbl_807DC5D8;obj->b=lbl_807DC5DC;obj->flag=true;
 if(scene<0)scene=29;
 Callback43990 callback;callback.vt=lbl_80681C10;callback.fn=fn_800220D0;fn_8004B970(&callback,scene);
 initActor__2MRFP9LiveActorPCcb(obj,resource,false);
 connectToScene__2MRFP9LiveActoriiii(obj,42,11,-1,scene);
 invalidateClipping__2MRFP9LiveActor(obj);return obj;
}
