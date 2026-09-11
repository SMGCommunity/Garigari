#include "LiveActor/ShadowHolderView.hpp"

extern "C" void* __dt__7NameObjFv(void*, int);
typedef MR::Vector<MR::AssignableArray<ShadowController*> > ShadowVector;
extern "C" ShadowVector* fn_8023F990(ShadowVector* v, int deleting) {
    if (v) {
        if (v->array) ::operator delete[](v->array);
        if (deleting > 0) ::operator delete(v);
    }
    return v;
}
extern "C" ShadowHolderView* fn_8023F9F0(ShadowHolderView* c, int deleting) {
    if (c) {
        ShadowVector* pending = &c->pending;
        if (pending) fn_8023F990(pending, -1);
        ShadowVector* registered = &c->registered;
        if (registered) fn_8023F990(registered, -1);
        __dt__7NameObjFv(c, 0);
        if (deleting > 0) ::operator delete(c);
    }
    return c;
}
