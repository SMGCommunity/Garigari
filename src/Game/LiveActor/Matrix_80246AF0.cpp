#include "LiveActor/LiveActor.hpp"
#include "Util/LiveActorUtil.hpp"
struct View46AF0 : LiveActor { u8 opaque[12]; f32 x,y,z,w; };
extern "C" { extern const f32 lbl_807DC640,lbl_807DC630; }
extern "C" void fn_80246AF0(View46AF0* obj) {
 TPos3f m;
 f32 yy=(lbl_807DC640*obj->y)*obj->y;
 f32 zz=(lbl_807DC640*obj->z)*obj->z;
 f32 xx=(lbl_807DC640*obj->x)*obj->x;
 f32 xy=(lbl_807DC640*obj->x)*obj->y;
 f32 xz=(lbl_807DC640*obj->x)*obj->z;
 f32 yz=(lbl_807DC640*obj->y)*obj->z;
 f32 wz=(lbl_807DC640*obj->w)*obj->z;
 f32 wx=(lbl_807DC640*obj->w)*obj->x;
 f32 wy=(lbl_807DC640*obj->w)*obj->y;
 m.mMtx[0][0]=lbl_807DC630-yy-zz;
 m.mMtx[0][1]=xy-wz;
 m.mMtx[0][2]=xz+wy;
 m.mMtx[1][0]=xy+wz;
 m.mMtx[1][1]=lbl_807DC630-xx-zz;
 m.mMtx[1][2]=yz-wx;
 m.mMtx[2][0]=xz-wy;
 m.mMtx[2][1]=yz+wx;
 m.mMtx[2][2]=lbl_807DC630-xx-yy;
 m.mMtx[0][3]=obj->mPosition.x;
 m.mMtx[1][3]=obj->mPosition.y;
 m.mMtx[2][3]=obj->mPosition.z;
 MR::setBaseTRMtx(obj,m);
}
