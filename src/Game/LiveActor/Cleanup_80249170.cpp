#include <revolution.h>
extern "C" void* __dt__7NameObjFv(void*,s32);
extern "C" void* fn_80249170(void* obj,s32 flag) {
 if(obj) { __dt__7NameObjFv(obj,0);if(flag>0)::operator delete(obj); }
 return obj;
}
