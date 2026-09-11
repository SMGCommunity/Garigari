#include "LiveActor/Holder450C0.hpp"
extern "C" { extern const void* lbl_80696488[]; }
struct Callback453C0 {
 const void* vtable; void* obj; Method45130 method;
 inline Callback453C0(void* host,Method45130 callback) ALWAYS_INLINE :vtable(lbl_80696488),obj(host),method(callback) {}
};
struct Flag453C0 { u8 opaque[0x1c]; bool flag; };
struct Clone45550 { const void* vtable; void* target; u32 a,b,c; };
extern "C" {
extern const Method45130 lbl_8069646C,lbl_80696478;
void* getSceneObjHolder__2MRFv();
void* getObj__14SceneObjHolderCFi(const void*,int);
bool isExistStageSwitchAwake__2MRFRC12JMapInfoIter(const void*);
bool isExistStageSwitchAppear__2MRFRC12JMapInfoIter(const void*);
void* fn_80060040(void*);
Callback453C0 fn_802454E0(void*,Method45130) NO_INLINE;
void fn_80060060(void*,const Callback453C0*);
void fn_800600B0(void*,const Callback453C0*);
void fn_802451B0(void*,const void*,const void*,void*);
void* __nw__FUlP7JKRHeapi(u32,void*,int);
void* __dt__7NameObjFv(void*,int);
}
extern "C" void fn_802453C0(Flag453C0* obj) { obj->flag=true; }
extern "C" void fn_802453D0(Flag453C0* obj) { obj->flag=false; }
extern "C" bool fn_802453E0(void* obj,const void* iter) {
 if(!isExistStageSwitchAwake__2MRFRC12JMapInfoIter(iter))return false;
 isExistStageSwitchAppear__2MRFRC12JMapInfoIter(iter);
 void* listener=::operator new(12);
 if(listener)listener=fn_80060040(listener);
 const Callback453C0& on=fn_802454E0(obj,lbl_8069646C);
 fn_80060060(listener,&on);
 const Callback453C0& off=fn_802454E0(obj,lbl_80696478);
 fn_800600B0(listener,&off);
 fn_802451B0(getObj__14SceneObjHolderCFi(getSceneObjHolder__2MRFv(),12),obj,iter,listener);
 return true;
}

extern "C" Callback453C0 fn_802454E0(void* obj,Method45130 method) { return Callback453C0(obj,method); }
extern "C" void fn_80245520(const Callback453C0* obj) { (static_cast<Opaque45130*>(obj->obj)->*obj->method)(); }
extern "C" Clone45550* fn_80245550(const Clone45550* obj,void* heap) {
 Clone45550* copy=(Clone45550*)__nw__FUlP7JKRHeapi(20,heap,0);
 if(copy) { copy->vtable=lbl_80696488;copy->target=obj->target;copy->a=obj->a;copy->b=obj->b;copy->c=obj->c; }
 return copy;
}
extern "C" void* fn_802455C0(void* obj,int deleting) {
 if(obj) { __dt__7NameObjFv(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
