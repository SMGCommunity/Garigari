#include "Map/BezierRail.hpp"
#include "Map/RailPart.hpp"
#include "Util/MathUtil.hpp"
extern "C" {
bool fn_8003F1A0(const TVec3f*,f32);
extern const f32 lbl_807DC610,lbl_807DC600,lbl_807DC614,lbl_807DC5FC,lbl_807DC5F8;
}
extern "C" void fn_80245620(TVec3f* out,const RailPart* part,f32 t) {
 part->calcVelocity(out,t);
 f32 next;
 if(fn_8003F1A0(out,lbl_807DC610)) {
  if(t<lbl_807DC600)next=lbl_807DC614+t;
  else { next=t;t=t-lbl_807DC614; }
  TVec3f pos;
  part->calcPos(&pos,t);part->calcPos(out,next);out->sub(pos);
 }
 MR::normalize(out);
}
void BezierRailPart::set(const TVec3f& rPoint1, const TVec3f& rPoint1Ctrl, const TVec3f& rPoint2Ctrl, const TVec3f& rPoint2) {
    TVec3f v21, v20, v19, v18, v17, v16;

    TVec3f v15(rPoint1Ctrl);
    v15.sub(rPoint1);

    v21 = v15;
    TVec3f v14(rPoint2Ctrl);
    v14.sub(rPoint1Ctrl);

    v20 = v14;
    TVec3f v13(rPoint2);
    v13.sub(rPoint2Ctrl);

    v19 = v13;
    TVec3f v12(v20);
    v12.sub(v21);

    v18 = v12;
    TVec3f v11(v19);
    v11.sub(v20);

    v17 = v11;
    TVec3f v10(v17);
    v10.sub(v18);

    v16 = v10;
    reinterpret_cast<TVec3f*>(_0)[0] = rPoint1;
    reinterpret_cast<TVec3f*>(_0)[1] = v21;
    reinterpret_cast<TVec3f*>(_0)[2] = v18;
    reinterpret_cast<TVec3f*>(_0)[3] = v16;

    mLength = getLength(lbl_807DC5FC, lbl_807DC5F8, 10);
}


extern "C" { extern const f32 lbl_807DC604,lbl_807DC60C; }
void BezierRailPart::calcPos(TVec3f* pOut, f32 t) const {
    f32 v7 = lbl_807DC604 * t;
    f32 v10 = v7 * t;
    f32 v9 = t * t * t;

    TVec3f v16(reinterpret_cast<const TVec3f*>(_0)[1]);
    TVec3f v15(reinterpret_cast<const TVec3f*>(_0)[2]);
    TVec3f v14(reinterpret_cast<const TVec3f*>(_0)[3]);

    v16.scale(v7);
    v15.scale(v10);
    v14.scale(v9);

    pOut->set< f32 >(reinterpret_cast<const TVec3f*>(_0)[0]);
    pOut->add(v16);
    pOut->add(v15);
    pOut->add(v14);
}

void BezierRailPart::calcVelocity(TVec3f* pOut, f32 t) const {
    f32 v5 = t * t;
    f32 v7 = lbl_807DC60C * t;

    TVec3f v12(reinterpret_cast<const TVec3f*>(_0)[3]);
    TVec3f v11(reinterpret_cast<const TVec3f*>(_0)[2]);
    v12.scale(v5);
    v11.scale(v7);

    pOut->set< f32 >(reinterpret_cast<const TVec3f*>(_0)[1]);
    pOut->add(v11);
    pOut->add(v12);
    pOut->scale(lbl_807DC604);
}

