#include <revolution.h>
struct Nerve44E70 { inline Nerve44E70(Nerve44E70* (*init)(Nerve44E70*)) ALWAYS_INLINE { init(this); } const void* vtable; };
struct Spine44E70 { void* host; };
extern "C" {
extern Nerve44E70 lbl_807D34C0,lbl_807D34C4,lbl_807D34C8;
extern const void* lbl_80696408[],*lbl_806963F8[],*lbl_806963E8[];
Nerve44E70* fn_80244EB0(Nerve44E70*) NO_INLINE;
Nerve44E70* fn_80244EC0(Nerve44E70*) NO_INLINE;
Nerve44E70* fn_80244ED0(Nerve44E70*) NO_INLINE;
void fn_80244860(void*);
void fn_80244790(void*);
}
extern "C" Nerve44E70* fn_80244EB0(Nerve44E70* obj) { obj->vtable=lbl_80696408;return obj; }
extern "C" Nerve44E70* fn_80244EC0(Nerve44E70* obj) { obj->vtable=lbl_806963F8;return obj; }
extern "C" Nerve44E70* fn_80244ED0(Nerve44E70* obj) { obj->vtable=lbl_806963E8;return obj; }
extern "C" void fn_80244EE0(const void*,const Spine44E70*) {}
extern "C" void fn_80244EF0(const void*,const Spine44E70* spine) { fn_80244860(spine->host); }
extern "C" void fn_80244F00(const void*,const Spine44E70* spine) { fn_80244790(spine->host); }
