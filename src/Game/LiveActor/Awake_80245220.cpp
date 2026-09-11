#include "LiveActor/Holder450C0.hpp"
struct Callback45220 { const void* vtable; void* obj; Method45130 method; };
extern "C" {
extern const Method45130 lbl_80696448,lbl_80696454,lbl_80696460;
Call45130 fn_80245130(Opaque45130**,Opaque45130**,Call45130);
void* getSceneObjHolder__2MRFv();
void* getObj__14SceneObjHolderCFi(const void*,int);
bool isExistStageSwitchAwake__2MRFRC12JMapInfoIter(const void*);
void* fn_80060040(void*);
Callback45220 fn_80070A20(void*,Method45130);
void fn_80060060(void*,const Callback45220*);
void fn_800600B0(void*,const Callback45220*);
void fn_802451B0(void*,const void*,const void*,void*);
void fn_80245220(Holder450C0*) NO_INLINE;
}
extern "C" void fn_80245220(Holder450C0* obj) {
 fn_80245130(obj->items,obj->items+obj->count,Call45130(lbl_80696448));
}
extern "C" void fn_80245290() {
 fn_80245220(static_cast<Holder450C0*>(getObj__14SceneObjHolderCFi(getSceneObjHolder__2MRFv(),12)));
}
extern "C" bool fn_802452C0(void* obj,const void* iter) {
 if(!isExistStageSwitchAwake__2MRFRC12JMapInfoIter(iter))return false;
 void* listener=::operator new(12);
 if(listener)listener=fn_80060040(listener);
 const Callback45220& on=fn_80070A20(obj,lbl_80696454);
 fn_80060060(listener,&on);
 const Callback45220& off=fn_80070A20(obj,lbl_80696460);
 fn_800600B0(listener,&off);
 fn_802451B0(getObj__14SceneObjHolderCFi(getSceneObjHolder__2MRFv(),12),obj,iter,listener);
 return true;
}
