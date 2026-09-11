#include <revolution.h>
struct Nerve4C170 { const void* vtable; };
struct Spine4C170 { void* host; };
extern "C" {
extern const void* lbl_80696A58[];
extern const void* lbl_80696A48[];
extern const void* lbl_80696A38[];
extern const void* lbl_80696A28[];
extern const void* lbl_80696A18[];
void fn_8024BFF0(void*);
void fn_8024BED0(void*);
void fn_8024BE50(void*);
void fn_8024BD20(void*);
void fn_8024BC80(void*);
Nerve4C170* fn_8024C170(Nerve4C170* obj) { obj->vtable=lbl_80696A58;return obj; }
Nerve4C170* fn_8024C180(Nerve4C170* obj) { obj->vtable=lbl_80696A48;return obj; }
Nerve4C170* fn_8024C190(Nerve4C170* obj) { obj->vtable=lbl_80696A38;return obj; }
Nerve4C170* fn_8024C1A0(Nerve4C170* obj) { obj->vtable=lbl_80696A28;return obj; }
Nerve4C170* fn_8024C1B0(Nerve4C170* obj) { obj->vtable=lbl_80696A18;return obj; }
void fn_8024C1C0(void*,const Spine4C170* spine) { fn_8024BFF0(spine->host); }
void fn_8024C1D0(void*,const Spine4C170* spine) { fn_8024BED0(spine->host); }
void fn_8024C1E0(void*,const Spine4C170* spine) { fn_8024BE50(spine->host); }
void fn_8024C1F0(void*,const Spine4C170* spine) { fn_8024BD20(spine->host); }
void fn_8024C200(void*,const Spine4C170* spine) { fn_8024BC80(spine->host); }
}
