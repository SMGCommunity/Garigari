#include "Map/SwitchWatcher.hpp"
struct View44F10 { void* switchInfo; SwitchEventListener* listener; bool previous; };
struct Holder45060 { const void* vtable; u8 opaque[0x1010]; s32 count; };
extern "C" {
void* createSwitchIdInfo__19StageSwitchFunctionFPCcRC12JMapInfoIterb(const char*,const void*,bool);
bool isOnSwitchBySwitchIdInfo__19StageSwitchFunctionFRC12SwitchIdInfo(const void*);
void __ct__7NameObjFPCc(void*,const char*);
void connectToSceneMapObjMovement__2MRFP7NameObj(void*);
extern const char lbl_80696418[],lbl_80696428[];
extern const void* lbl_80696498[];
}
extern "C" View44F10* fn_80244F10(View44F10* obj,const void* iter,SwitchEventListener* listener) {
 obj->listener=listener;obj->switchInfo=0;obj->previous=false;
 obj->switchInfo=createSwitchIdInfo__19StageSwitchFunctionFPCcRC12JMapInfoIterb(lbl_80696418,iter,false);
 return obj;
}
extern "C" void fn_80244F60(View44F10* obj) {
 if(isOnSwitchBySwitchIdInfo__19StageSwitchFunctionFRC12SwitchIdInfo(obj->switchInfo))obj->listener->listenSwitchOnEvent();
 else obj->listener->listenSwitchOffEvent();
}
extern "C" void fn_80244FD0(View44F10* obj) {
 bool current=isOnSwitchBySwitchIdInfo__19StageSwitchFunctionFRC12SwitchIdInfo(obj->switchInfo);
 if(!obj->previous && current)obj->listener->listenSwitchOnEvent();
 if(obj->previous && !current)obj->listener->listenSwitchOffEvent();
 obj->previous=current;
}
extern "C" Holder45060* fn_80245060(Holder45060* obj) {
 __ct__7NameObjFPCc(obj,lbl_80696428);obj->vtable=lbl_80696498;obj->count=0;
 connectToSceneMapObjMovement__2MRFP7NameObj(obj);return obj;
}
