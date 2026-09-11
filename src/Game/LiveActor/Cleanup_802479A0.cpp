#include <revolution.h>
extern "C" void* __dt__7NameObjFv(void*,int);
inline void cleanup479A0(void* obj) { if(obj)__dt__7NameObjFv(obj,0); }
extern "C" void* fn_802479A0(void* obj,int deleting) {
 if(obj) { cleanup479A0(obj);if(deleting>0)::operator delete(obj); }
 return obj;
}
