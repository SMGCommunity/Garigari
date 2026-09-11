#include <revolution.h>
struct Nerve4C610 { const void* vtable; };
struct Spine4C610 { void* host; };
extern "C" {
extern const void* lbl_80696B28[];
extern const void* lbl_80696B18[];
extern const void* lbl_80696B08[];
void fn_8024C380(void*);
Nerve4C610* fn_8024C610(Nerve4C610* obj) { obj->vtable = lbl_80696B28; return obj; }
Nerve4C610* fn_8024C620(Nerve4C610* obj) { obj->vtable = lbl_80696B18; return obj; }
Nerve4C610* fn_8024C630(Nerve4C610* obj) { obj->vtable = lbl_80696B08; return obj; }
void fn_8024C640(void*, const Spine4C610* spine) { fn_8024C380(spine->host); }
void fn_8024C650(void*, const Spine4C610*) { }
}
