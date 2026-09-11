#include <revolution.h>
extern "C" void* __dt__7NameObjFv(void*, int);
// Inline base cleanup preserves the retail destructor's second null guard.
inline void destroyShadowDrawerBase(void* obj) {
    if (obj) __dt__7NameObjFv(obj, 0);
}
extern "C" void* fn_8023FB40(void* obj, int deleting) {
    if (obj) {
        destroyShadowDrawerBase(obj);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
