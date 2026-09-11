#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TMatrix.hpp>
struct Item4B070 { u8 opaque[0xc4];void* helper; };
struct Primitive4B070 { u8 opaque[6];u16 face,edge1,edge2,edge3; };
extern "C" {
const TVec3f* fn_80259AB0(void*,u16);
TVec3f fn_80259B20(void*,Primitive4B070*,int);
void fn_8024B3E0(Item4B070*,TVec3f*,const TVec3f*,const TVec3f&,const TVec3f*);
void fn_8024B070(Item4B070* obj,TVec3f* position,Primitive4B070* primitive,u8 type) {
 TVec3f difference,normal;
 switch(type) {
 case 1: {
  const TVec3f* face=fn_80259AB0(obj->helper,primitive->face);
  fn_8024B3E0(obj,position,position,fn_80259B20(obj->helper,primitive,0),face);
  break;
 }
 case 2: {
  const TVec3f* face=fn_80259AB0(obj->helper,primitive->face);
  fn_8024B3E0(obj,position,position,fn_80259B20(obj->helper,primitive,0),face);
  normal.set<float>(*fn_80259AB0(obj->helper,primitive->edge1));
  difference.set<float>(*position);
  difference.sub(fn_80259B20(obj->helper,primitive,0));
  position->add((-normal).scaleInline(difference.dot(normal)));
  break;
 }
 case 3: {
  const TVec3f* face=fn_80259AB0(obj->helper,primitive->face);
  fn_8024B3E0(obj,position,position,fn_80259B20(obj->helper,primitive,0),face);
  normal.set<float>(*fn_80259AB0(obj->helper,primitive->edge2));
  difference.set<float>(*position);
  difference.sub(fn_80259B20(obj->helper,primitive,0));
  position->add((-normal).scaleInline(difference.dot(normal)));
  break;
 }
 case 4: {
  const TVec3f* face=fn_80259AB0(obj->helper,primitive->face);
  fn_8024B3E0(obj,position,position,fn_80259B20(obj->helper,primitive,0),face);
  normal.set<float>(*fn_80259AB0(obj->helper,primitive->edge3));
  difference.set<float>(*position);
  difference.sub(fn_80259B20(obj->helper,primitive,1));
  position->add((-normal).scaleInline(difference.dot(normal)));
  break;
 }
 case 5: position->set<float>(fn_80259B20(obj->helper,primitive,0));break;
 case 6: position->set<float>(fn_80259B20(obj->helper,primitive,1));break;
 case 7: position->set<float>(fn_80259B20(obj->helper,primitive,2));break;
 }
}
}
