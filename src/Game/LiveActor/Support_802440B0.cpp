#include "LiveActor/LiveActor.hpp"

// Opaque target-derived views; owning class identities are not established.
struct Callback44180 { const void* vtable; LiveActor* host; bool appearEnabled, killEnabled; };
struct View44260 { const void* vtable; u8 opaque[0x8c]; bool flag90, flag91; u8 pad[2]; f32 value; };
extern "C" {
void* fn_80243990(void*, const char*, const char*, void*, int);
void initWithoutIter__7NameObjFv(void*);
void* __dt__7NameObjFv(void*, int);
bool isDead__2MRFPC9LiveActor(const LiveActor*);
void __ct__9LiveActorFPCc(void*, const char*);
extern const void* lbl_806960C8[], *lbl_8069635C[];
extern const f32 lbl_807DC5E8;
}
extern "C" void* fn_802440B0(const char* name, const char* resource, void* arg) {
 void* result = ::operator new(0xb8);
 if (result) result = fn_80243990(result, name, resource, arg, 28);
 initWithoutIter__7NameObjFv(result);
 return result;
}
inline void destroyBase44120(void* obj) {
 if (obj) __dt__7NameObjFv(obj, 0);
}
extern "C" void* fn_80244120(void* obj, int deleting) {
 if (obj) {
  destroyBase44120(obj);
  if (deleting > 0) ::operator delete(obj);
 }
 return obj;
}
extern "C" Callback44180* fn_80244180(Callback44180* obj, LiveActor* host, bool appearEnabled, bool killEnabled) {
 obj->host=host;obj->vtable=lbl_806960C8;
 obj->appearEnabled=appearEnabled;obj->killEnabled=killEnabled;
 return obj;
}
extern "C" void fn_802441A0(Callback44180* obj) {
 if (isDead__2MRFPC9LiveActor(obj->host) && obj->appearEnabled) obj->host->appear();
}
extern "C" void fn_80244200(Callback44180* obj) {
 if (!isDead__2MRFPC9LiveActor(obj->host) && obj->killEnabled) obj->host->kill();
}
extern "C" View44260* fn_80244260(View44260* obj, const char* name) {
 __ct__9LiveActorFPCc(obj,name);
 obj->flag90=false;obj->vtable=lbl_8069635C;
 obj->flag91=false;obj->value=lbl_807DC5E8;
 return obj;
}
