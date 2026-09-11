#include <revolution.h>
extern "C" void* fn_8023FB40(void*, int);
extern "C" void* fn_80240000(void* obj, int deleting) {
    if (obj) {
        fn_8023FB40(obj, 0);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
