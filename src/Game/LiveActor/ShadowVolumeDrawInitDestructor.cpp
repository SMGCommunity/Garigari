#include <revolution.h>
extern "C" void* __dt__7NameObjFv(void*, int);
extern "C" void* fn_80241820(void* obj, int deleting) {
    if (obj) {
        __dt__7NameObjFv(obj, 0);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}

