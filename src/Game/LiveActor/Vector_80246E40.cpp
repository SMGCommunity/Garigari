#include "LiveActor/LiveActor.hpp"
#include "Util/MathUtil.hpp"
extern "C" {
void** fn_8005D440();
void* fn_8005D250(void*);
void fn_8005D7C0(TVec2f*,void*);
void fn_8001C600(TVec2f*,const TVec3f*);
TVec2f fn_80246FA0(const TVec2f*,const TVec2f*) NO_INLINE;
bool fn_8003F220(const TVec2f*,f32);
void fn_8001D000(TVec3f*);
void fn_8001D070(TVec3f*);
void fn_8002B390(void*,TVec3f*,void*,void*);
void fn_80011BB0(TVec3f*,f32);
extern const f32 lbl_807DC650,lbl_807DC634,lbl_807DC65C;
}
inline void copy2(TVec2f* v,const TVec2f& t) ALWAYS_INLINE { v->x=t.x;v->y=t.y; }
inline TVec3f makeB() ALWAYS_INLINE { TVec3f v;fn_8001D070(&v);return v; }
extern "C" void fn_80246E40(LiveActor* obj) {
 TVec2f target;fn_8005D7C0(&target,fn_8005D250(*fn_8005D440()));
 TVec2f position;fn_8001C600(&position,&obj->mPosition);
 TVec2f difference;copy2(&difference,fn_80246FA0(&position,&target));
 if(!fn_8003F220(&difference,lbl_807DC650))MR::normalize(&target);
 TVec3f a;fn_8001D000(&a);
 const TVec3f& neg=-makeB();
 TVec3f sum=a.scaleInline(difference.x).addInline(neg.scaleInline(difference.y));
 TVec3f v;fn_8002B390(obj,&v,0,0);
 if(lbl_807DC634<sum.dot(v))MR::vecKillElement(sum,v,&sum);
 fn_80011BB0(&sum,lbl_807DC65C);
 obj->mVelocity.add(sum);
}
extern "C" TVec2f fn_80246FA0(const TVec2f* a,const TVec2f* b) {
 f32 by,bx,ay,ax; ax=a->x;bx=b->x;ay=a->y;by=b->y; TVec2f result={ax-bx,ay-by};return result;
}
