#include <revolution.h>
struct Nerve4EC10 { const void* vtable; };
struct Spine4EC10 { void* host; };
struct Helper4EC10 { u8 base[8]; f32 factor; };
extern "C" {
extern const void* lbl_80696F50[];
extern const void* lbl_80696F40[];
extern const void* lbl_80696F30[];
extern const void* lbl_80696F20[];
extern const void* lbl_80696F10[];
extern const void* lbl_80696F00[];
extern const void* lbl_80696EF0[];
extern const void* lbl_80696EE0[];
extern const void* lbl_80696ED0[];
extern const void* lbl_80696EC0[];
extern const void* lbl_80696EB0[];
extern const void* lbl_80696EA0[];
extern const void* lbl_80696E90[];
void fn_8024E7B0(void*);
void fn_8024E720(void*);
void fn_8024E6B0(void*);
void fn_8024E5D0(void*);
void fn_8024E4D0(void*);
void fn_8024E440(void*);
void fn_8024D220(void*);
void fn_8024D110(void*);
void fn_8024D020(void*);
extern const f32 lbl_807DC70C;
extern const f32 lbl_807DC6D0;
Nerve4EC10* fn_8024EC10(Nerve4EC10* obj) { obj->vtable = lbl_80696F50; return obj; }
Nerve4EC10* fn_8024EC20(Nerve4EC10* obj) { obj->vtable = lbl_80696F40; return obj; }
Nerve4EC10* fn_8024EC30(Nerve4EC10* obj) { obj->vtable = lbl_80696F30; return obj; }
Nerve4EC10* fn_8024EC40(Nerve4EC10* obj) { obj->vtable = lbl_80696F20; return obj; }
Nerve4EC10* fn_8024EC50(Nerve4EC10* obj) { obj->vtable = lbl_80696F10; return obj; }
Nerve4EC10* fn_8024EC60(Nerve4EC10* obj) { obj->vtable = lbl_80696F00; return obj; }
Nerve4EC10* fn_8024EC70(Nerve4EC10* obj) { obj->vtable = lbl_80696EF0; return obj; }
Nerve4EC10* fn_8024EC80(Nerve4EC10* obj) { obj->vtable = lbl_80696EE0; return obj; }
Nerve4EC10* fn_8024EC90(Nerve4EC10* obj) { obj->vtable = lbl_80696ED0; return obj; }
Nerve4EC10* fn_8024ECA0(Nerve4EC10* obj) { obj->vtable = lbl_80696EC0; return obj; }
Nerve4EC10* fn_8024ECB0(Nerve4EC10* obj) { obj->vtable = lbl_80696EB0; return obj; }
Nerve4EC10* fn_8024ECC0(Nerve4EC10* obj) { obj->vtable = lbl_80696EA0; return obj; }
Nerve4EC10* fn_8024ECD0(Nerve4EC10* obj) { obj->vtable = lbl_80696E90; return obj; }
void fn_8024ECE0(void*, const Spine4EC10* spine) { fn_8024E7B0(spine->host); }
void fn_8024ECF0(void*, const Spine4EC10* spine) { fn_8024E720(spine->host); }
void fn_8024ED00(void*, const Spine4EC10* spine) { fn_8024E6B0(spine->host); }
void fn_8024ED10(void*, const Spine4EC10* spine) { fn_8024E5D0(spine->host); }
void fn_8024ED20(void*, const Spine4EC10* spine) { static_cast<Helper4EC10*>(spine->host)->factor = lbl_807DC70C; }
void fn_8024ED30(void*, const Spine4EC10* spine) { fn_8024E4D0(spine->host); }
void fn_8024ED40(void*, const Spine4EC10* spine) { static_cast<Helper4EC10*>(spine->host)->factor = lbl_807DC6D0; }
void fn_8024ED50(void*, const Spine4EC10* spine) { fn_8024E440(spine->host); }
void fn_8024ED60(void*, const Spine4EC10* spine) { fn_8024D220(spine->host); }
void fn_8024ED70(void*, const Spine4EC10* spine) { fn_8024D110(spine->host); }
void fn_8024ED80(void*, const Spine4EC10* spine) { fn_8024D020(spine->host); }
void fn_8024ED90(void*, const Spine4EC10* spine) {  }
void fn_8024EDA0(void*, const Spine4EC10* spine) {  }
}
