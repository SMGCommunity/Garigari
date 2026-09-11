#include "LiveActor/LiveActor.hpp"
struct View46FE0 : LiveActor { TVec3f position90; };
extern "C" {
void** fn_8005D440();
bool fn_8005D350(void*);
bool fn_8005C8D0(void*,void*,void*,void*);
bool fn_8002A050(void*);
f32 PSVECDistance(const Vec*,const Vec*);
void fn_8001C600(TVec2f*,const TVec3f*);
void* fn_8005D250(void*);
void fn_8005D7C0(TVec2f*,void*);
TVec2f fn_80246FA0(const TVec2f*,const TVec2f*);
const TVec2f* fn_8005D470(void*);
bool fn_8005C360(void*,void*);
void fn_80246E40(LiveActor*);
extern const f32 lbl_807DC660,lbl_807DC634;
extern const u32 lbl_807D34D4;
}
extern "C" bool fn_80246FE0(View46FE0* obj) {
 void* target=*fn_8005D440();
 if(!fn_8005D350(target))return false;
 if(!fn_8005C8D0(obj,0,0,0))return false;
 if(fn_8002A050(target))return false;
 if(lbl_807DC660<PSVECDistance(&obj->mPosition,&obj->position90))return false;
 TVec2f position;fn_8001C600(&position,&obj->mPosition);
 TVec2f other;fn_8005D7C0(&other,fn_8005D250(target));
 TVec2f difference=fn_80246FA0(&position,&other);
 const TVec2f* direction=fn_8005D470(target);
 if(direction->x*difference.x+direction->y*difference.y<=lbl_807DC634)return false;
 if(!fn_8005C360(obj,0))return false;
 fn_80246E40(obj);
 obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D4));
 return true;
}
