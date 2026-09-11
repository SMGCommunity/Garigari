#include <revolution.h>
struct View44960 { const void* vtable; };
struct Holder44B80 { const void* vtable; u8 opaque[0x10]; void* items[8]; s32 count; };
extern "C" {
void* fn_80244260(void*,const char*);
void* __dt__7NameObjFv(void*,int);
void __ct__7NameObjFPCc(void*,const char*);
void initActor__2MRFP9LiveActorPCcb(void*,const char*,bool);
void* fn_80031FF0(const void*);
void fn_80031ED0(void*);
void fn_80239F30(void*);
void setClippingFarMax__2MRFP9LiveActor(void*);
void fn_80031720(void*);
void connectToScene__2MRFP9LiveActoriiii(void*,int,int,int,int);
void* createSceneObj__2MRFi(int);
void* getSceneObjHolder__2MRFv();
void* getObj__14SceneObjHolderCFi(const void*,int);
void fn_80244BD0(Holder44B80*,void*);
extern const void* lbl_80696264[],*lbl_806962E0[],*lbl_806961E8[],*lbl_8069616C[],*lbl_80696140[];
extern const char lbl_8069611C[];
}
extern "C" View44960* fn_80244960(View44960* obj,const char* name) {
 fn_80244260(obj,name);obj->vtable=lbl_80696264;return obj;
}
inline void cleanup449A0(void* obj) { if(obj)__dt__7NameObjFv(obj,0); }
extern "C" void* fn_802449A0(void* obj,int deleting) {
 if(obj) { cleanup449A0(obj);if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" void fn_80244A00(void* obj,const char* name) {
 initActor__2MRFP9LiveActorPCcb(obj,name,true);
 void* model=fn_80031FF0(obj);fn_80031ED0(obj);fn_80239F30(model);
}
extern "C" void fn_80244A60(void* obj) { setClippingFarMax__2MRFP9LiveActor(obj); }
extern "C" View44960* fn_80244A70(View44960* obj,const char* name) {
 fn_80244260(obj,name);obj->vtable=lbl_806962E0;return obj;
}
extern "C" void fn_80244AB0(void* obj) { fn_80031720(obj); }
extern "C" View44960* fn_80244AC0(View44960* obj,const char* name) {
 fn_80244260(obj,name);obj->vtable=lbl_806961E8;return obj;
}
extern "C" void fn_80244B00(void* obj) { connectToScene__2MRFP9LiveActoriiii(obj,35,5,20,-1); }
extern "C" View44960* fn_80244B20(View44960* obj,const char* name) {
 fn_80244260(obj,name);obj->vtable=lbl_8069616C;
 createSceneObj__2MRFi(128);
 fn_80244BD0(static_cast<Holder44B80*>(getObj__14SceneObjHolderCFi(getSceneObjHolder__2MRFv(),128)),obj);
 return obj;
}
extern "C" Holder44B80* fn_80244B80(Holder44B80* obj) {
 __ct__7NameObjFPCc(obj,lbl_8069611C);obj->vtable=lbl_80696140;obj->count=0;return obj;
}
extern "C" void fn_80244BD0(Holder44B80* obj,void* item) { s32 index=obj->count;obj->count=index+1;obj->items[index]=item; }
