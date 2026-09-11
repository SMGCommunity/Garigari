#include <revolution.h>
// Only the three used virtual slots are identified; preceding entries stay opaque.
struct VolumeDrawView {
 virtual void slot0() const;
 virtual void slot1() const;
 virtual void slot2() const;
 virtual void slot3() const;
 virtual void slot4() const;
 virtual void slot5() const;
 virtual void slot6() const;
 virtual void slot7() const;
 virtual void slot8() const;
 virtual void load() const;
 virtual void shape() const;
 virtual bool enabled() const;
};
extern "C" {
extern const u32 lbl_807D34B8;
void fn_805CF5D0(int, const u32*);
void fn_805CFE50(int);
void fn_805D0000(int,int);
void fn_805CCA20(int);
void fn_805CFE00(int,int,int,int);
}
extern "C" void fn_80241720(const VolumeDrawView* obj) {
 if (!obj->enabled()) return;
 obj->load();
 u32 color=lbl_807D34B8;
 fn_805CF5D0(1,&color); fn_805CFE50(0); fn_805D0000(0,0);
 fn_805CCA20(1); fn_805CFE00(1,1,1,3);
 obj->shape();
 fn_805CCA20(2); fn_805CFE00(3,0,0,3);
 obj->shape();
 fn_805CCA20(0); fn_805CFE50(1); fn_805D0000(1,0);
}
