#include <revolution.h>
struct View429F0 { u8 opaque[0x30]; f32 angle,width; };
extern "C" {
f32 fn_80012FB0(f32);
f32 fn_8009F7C0(f32);
void fn_805CC730(int,int,int);
extern f32 lbl_807DC5A8;
extern const f32 lbl_807DC5B4,lbl_807DC5B8;
}
extern "C" void fn_802429F0(const View429F0* obj) {
 f32 low=fn_80012FB0(obj->angle-obj->width);
 f32 high=fn_80012FB0(obj->angle+obj->width);
 f32 radiusLow=fn_8009F7C0(obj->angle-obj->width);
 f32 radiusHigh=fn_8009F7C0(obj->angle+obj->width);
 for(int i=0;i<32;i++) {
 f32 ai=lbl_807DC5B4*i;
 f32 bi=lbl_807DC5B4*(i+1);
 f32 a=ai*lbl_807DC5B8;
 f32 b=bi*lbl_807DC5B8;
 f32 sa=fn_80012FB0(a),ca=fn_8009F7C0(a);
 f32 sb=fn_80012FB0(b),cb=fn_8009F7C0(b);
 fn_805CC730(0x98,0,6);
 volatile f32* fifo=(volatile f32*)0xCC008000;
 *fifo=lbl_807DC5A8;*fifo=lbl_807DC5A8;*fifo=lbl_807DC5A8;
 *fifo=radiusLow*cb;*fifo=low;*fifo=radiusLow*sb;
 *fifo=radiusLow*ca;*fifo=low;*fifo=radiusLow*sa;
 *fifo=radiusHigh*cb;*fifo=high;*fifo=radiusHigh*sb;
 *fifo=radiusHigh*ca;*fifo=high;*fifo=radiusHigh*sa;
 *fifo=lbl_807DC5A8;*fifo=lbl_807DC5A8;*fifo=lbl_807DC5A8;
 }
}
