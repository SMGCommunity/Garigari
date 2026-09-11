#include <revolution.h>
#include "Util/MtxUtil.hpp"
struct Host42920 {
 virtual void opaque0();
 virtual void opaque1();
 virtual void opaque2();
 virtual void opaque3();
 virtual void opaque4();
 virtual void opaque5();
 virtual void opaque6();
 virtual void opaque7();
 virtual void opaque8();
 virtual void opaque9();
 virtual void opaque10();
 virtual void opaque11();
 virtual void opaque12();
 virtual void opaque13();
 virtual MtxPtr matrix() const;
};
struct View42920 { u8 opaque[0x24]; Host42920* host; MtxPtr matrix; f32 scale; };
extern "C" {
void fn_8002D710(TPos3f*,MtxPtr);
MtxPtr fn_8001CD10();
void fn_805D05B0(MtxPtr,int);
void fn_805D0660(int);
void fn_805CB330();
void fn_805CAEE0(int,int);
void fn_805CB370(int,int,int,int,int);
}
extern "C" void fn_80242920(const View42920* obj) {
 TPos3f matrix;matrix.identity();
 if(obj->matrix)fn_8002D710(&matrix,obj->matrix);
 else fn_8002D710(&matrix,obj->host->matrix());
 MR::preScaleMtx(matrix.mMtx,TVec3f(obj->scale));
 PSMTXConcat(fn_8001CD10(),matrix.mMtx,matrix.mMtx);
 fn_805D05B0(matrix.mMtx,0);fn_805D0660(0);fn_805CB330();
 fn_805CAEE0(9,1);fn_805CB370(0,9,1,4,0);
}
