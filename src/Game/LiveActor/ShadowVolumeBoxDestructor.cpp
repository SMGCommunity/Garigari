#include <revolution.h>
extern "C" void* fn_80095A40(void*, int);
extern "C" void* fn_80241120(void* obj, int deleting) {
    if (obj) {
        fn_80095A40(obj, 0);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}

