#include "LiveActor/LiveActor.hpp"
struct View47130 : LiveActor { TVec3f position90; };
extern "C" {
bool fn_8005D3A0(void**);
f32 PSVECDistance(const Vec*,const Vec*);
const TVec2f* fn_8005D250(void*);
void fn_8001C600(TVec2f*,const TVec3f*);
f32 fn_80007B60(f32);
bool fn_8002A050(void*);
extern const f32 lbl_807DC660,lbl_807DC648;
extern const u32 lbl_807D34D8;
}
extern "C" bool fn_80247130(View47130* obj) {
 void* target=0;
 if(!fn_8005D3A0(&target))return false;
 if(lbl_807DC660<PSVECDistance(&obj->mPosition,&obj->position90))return false;
 TVec2f position;
 const TVec2f* p=fn_8005D250(target);
 TVec2f other={p->x,p->y};
 fn_8001C600(&position,&obj->mPosition);
 f32 x=other.x-position.x,y=other.y-position.y;
 if(lbl_807DC648<fn_80007B60(x*x+y*y))return false;
 if(!fn_8002A050(target))return false;
 obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D8));
 return true;
}
