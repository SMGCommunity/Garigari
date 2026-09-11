#include <revolution.h>
extern "C" void fn_8023CEF0(void*);
extern "C" void* fn_800BAFC0(void*, int);
extern "C" void fn_80243510(void* obj) { fn_8023CEF0(obj); }
extern "C" void* fn_80243520(void* obj, int deleting) {
 if (obj) { fn_800BAFC0(obj, 0); if (deleting > 0) ::operator delete(obj); }
 return obj;
}
