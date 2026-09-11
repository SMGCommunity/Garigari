#include <revolution.h>
void operator delete(void*);
extern "C" {
void* __dt__7NameObjFv(void*, s32);
void* __dt__13NerveExecutorFv(void*, s32);
void* fn_8024EA60(void* obj, s32 flag) {
    if (obj) { if (obj) __dt__7NameObjFv(obj, 0); if (flag > 0) ::operator delete(obj); }
    return obj;
}
void* fn_8024EAC0(void* obj, s32 flag) {
    if (obj) { __dt__13NerveExecutorFv(obj, 0); if (flag > 0) ::operator delete(obj); }
    return obj;
}
void* fn_8024EB20(void* obj, s32 flag) {
    if (obj) { __dt__13NerveExecutorFv(obj, 0); if (flag > 0) ::operator delete(obj); }
    return obj;
}
}
