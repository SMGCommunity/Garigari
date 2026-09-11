#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TVec.hpp>

struct Item484D0 { u8 opaque[0x40]; f32 x; u8 pad44[0xc]; f32 y; u8 pad54[0xc]; f32 z; u8 pad64[0x68]; bool active; u8 pad[0xb]; f32 radius; };
struct Group484D0 { u32 opaque; Item484D0* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
struct Record484D0 { u8 opaque[0x8c]; };
struct View484D0 { u8 opaque[0x14]; Record484D0* records; s32 result; u32 value1C; Group484D0* groups[32]; s32 count; };
struct Predicate484D0 { virtual bool test(Item484D0*)=0; };
extern "C" {
void fn_80249F20(View484D0*);
bool fn_80248AB0(View484D0*,const TVec3f*,const TVec3f*,const TVec3f*,f32);
bool fn_8003C530(const TVec3f*,const TVec3f*,const TVec3f&,void*,f32);
TVec3f fn_80248010(const Item484D0*);
s32 fn_8024B4A0(Item484D0*,Record484D0*,s32,const TVec3f*,const TVec3f*,void*);
extern const f32 lbl_807DC688;
}
inline TVec3f endpoint484D0(const TVec3f& point,const TVec3f& direction) ALWAYS_INLINE { TVec3f end(point);end+=direction;return end; }
extern "C" s32 fn_802484D0(View484D0* obj,const TVec3f* point,const TVec3f* direction,s32 capacity,Predicate484D0* predicate,void* last) {
 fn_80249F20(obj);
 if(!capacity)capacity=32;
 obj->result=0;
 s32 total=0;
 TVec3f low(*point),high(*point);
 if(direction->x<lbl_807DC688)low.x+=direction->x;else high.x+=direction->x;
 if(direction->y<lbl_807DC688)low.y+=direction->y;else high.y+=direction->y;
 if(direction->z<lbl_807DC688)low.z+=direction->z;else high.z+=direction->z;
 Group484D0** group=obj->groups;
 for(;group!=obj->groups+obj->count;++group) {
  if(group!=obj->groups) {
   TVec3f center((*group)->center);
   f32 radius=(*group)->radius;
   if(!fn_80248AB0(obj,&low,&high,&center,radius))continue;
   if(!fn_8003C530(&center,point,endpoint484D0(*point,*direction),0,radius))continue;
  }
  s32 count=(*group)->count;
  for(s32 i=0;i<count;++i) {
   Item484D0* item=(*group)->items[i];
   if(!item->active)continue;
   if(predicate && predicate->test(item))continue;
   TVec3f center=fn_80248010(item);
   f32 radius=item->radius;
   if(!fn_80248AB0(obj,&low,&high,&center,radius))continue;
   if(!fn_8003C530(&center,point,endpoint484D0(*point,*direction),0,radius))continue;
   total+=fn_8024B4A0(item,obj->records+total,capacity-total,point,direction,last);
   if(capacity<=total) { obj->result=total;return total; }
  }
 }
 obj->result=total;return total;
}
