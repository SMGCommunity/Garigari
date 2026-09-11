#include <revolution.h>
void operator delete(void*);
extern "C" {
void* __dt__7NameObjFv(void*, s32);
void* fn_8024F080(void* obj, s32 flag) {
    if (obj) { if (obj) __dt__7NameObjFv(obj, 0); if (flag > 0) ::operator delete(obj); }
    return obj;
}
}
