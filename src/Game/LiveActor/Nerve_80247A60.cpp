#include <revolution.h>
struct Nerve47A60 { const void* vtable; };
struct Spine47A60 { void* host; };
extern "C" {
extern const void* lbl_806965E0[];
extern const void* lbl_806965D0[];
extern const void* lbl_806965C0[];
extern const void* lbl_806965B0[];
extern const void* lbl_806965A0[];
extern const void* lbl_80696590[];
extern const void* lbl_80696580[];
void fn_80247900(void*);
void fn_80247850(void*);
void fn_80247760(void*);
void fn_80247670(void*);
void fn_80247560(void*);
void fn_802474B0(void*);
void fn_80247340(void*);
}
extern "C" Nerve47A60* fn_80247A60(Nerve47A60* obj) { obj->vtable=lbl_806965E0;return obj; }
extern "C" Nerve47A60* fn_80247A70(Nerve47A60* obj) { obj->vtable=lbl_806965D0;return obj; }
extern "C" Nerve47A60* fn_80247A80(Nerve47A60* obj) { obj->vtable=lbl_806965C0;return obj; }
extern "C" Nerve47A60* fn_80247A90(Nerve47A60* obj) { obj->vtable=lbl_806965B0;return obj; }
extern "C" Nerve47A60* fn_80247AA0(Nerve47A60* obj) { obj->vtable=lbl_806965A0;return obj; }
extern "C" Nerve47A60* fn_80247AB0(Nerve47A60* obj) { obj->vtable=lbl_80696590;return obj; }
extern "C" Nerve47A60* fn_80247AC0(Nerve47A60* obj) { obj->vtable=lbl_80696580;return obj; }
extern "C" void fn_80247AD0(void*,const Spine47A60* spine) { fn_80247900(spine->host); }
extern "C" void fn_80247AE0(void*,const Spine47A60* spine) { fn_80247850(spine->host); }
extern "C" void fn_80247AF0(void*,const Spine47A60* spine) { fn_80247760(spine->host); }
extern "C" void fn_80247B00(void*,const Spine47A60* spine) { fn_80247670(spine->host); }
extern "C" void fn_80247B10(void*,const Spine47A60* spine) { fn_80247560(spine->host); }
extern "C" void fn_80247B20(void*,const Spine47A60* spine) { fn_802474B0(spine->host); }
extern "C" void fn_80247B30(void*,const Spine47A60* spine) { fn_80247340(spine->host); }
