#include <revolution.h>
extern "C" void* fn_80095A40(void*, int);
// Inline base cleanup preserves the retail destructor's second null guard.
inline void destroyVolumeBase(void* obj) {
    if (obj) fn_80095A40(obj, 0);
}
extern "C" void* fn_80241350(void* obj, int deleting) {
    if (obj) {
        destroyVolumeBase(obj);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
