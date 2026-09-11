#include <JGeometry/TVec.hpp>
struct Group48C70 { s32 index; void* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; Group48C70(s32); };
extern "C" { extern const f32 lbl_807DC688; void fn_80248D60(Group48C70*); }
Group48C70::Group48C70(s32 value) : index(value),count(0),center(0,0,0),radius(lbl_807DC688),low(0,0,0),high(0,0,0) {}
extern "C" bool fn_80248CF0(const Group48C70* obj,const void* item) {
 for(s32 i=0;i<obj->count;++i)if(obj->items[i]==item)return true;
 return false;
}
extern "C" void fn_80248D30(Group48C70* obj,void* item) {
 s32 slot=obj->count;obj->count=slot+1;obj->items[slot]=item;
 if(obj->index)fn_80248D60(obj);
}
