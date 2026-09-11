#include "NameObj/NameObj.hpp"
#include "Map/CollisionCode.hpp"
#include "Scene/SceneObjHolder.hpp"
struct DirectorView { const void* vtable; u8 base[0x10]; NameObj** holders; CollisionCode* code; };
namespace MR { void connectToScene(NameObj*,int,int,int,int); }
extern "C" {
void* __ct__7NameObjFPCc(void*,const char*);
void* __dt__7NameObjFv(void*,s32);
extern const char lbl_80696968[];
extern const void* lbl_80696978[];
void* fn_80247B40(void*,s32);
DirectorView* __ct__17CollisionDirectorFv(DirectorView* obj) {
 __ct__7NameObjFPCc(obj,lbl_80696968);
 obj->vtable=lbl_80696978;obj->holders=0;obj->code=0;
 obj->code=new CollisionCode();
 obj->holders=new NameObj*[5];
 for(s32 i=0;i<5;++i) {
  void* holder=::operator new(0xac);
  if(holder)holder=fn_80247B40(holder,i);
  obj->holders[i]=static_cast<NameObj*>(holder);
 }
 MR::connectToScene(reinterpret_cast<NameObj*>(obj),31,-1,-1,-1);
 return obj;
}
void fn_80249EA0(void*,const JMapInfoIter&) {}
void fn_80249EB0(void*) {}
void fn_80249EC0(DirectorView* obj) {
 for(s32 i=0;i<5;++i)obj->holders[i]->movement();
}
NameObj* fn_80249F20() { return MR::getSceneObjHolder()->getObj(1); }
void* fn_80249F50(void* obj,s32 flag) {
 if(obj) { __dt__7NameObjFv(obj,0);if(flag>0)::operator delete(obj); }
 return obj;
}
}
