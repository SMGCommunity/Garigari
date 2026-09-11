#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct VolumePositionView { u8 opaque[0x18]; f32 start; };
extern "C" {
void fn_8023F1E0(const void*, TVec3f*);
void fn_8023F220(const void*, TVec3f*);
}
inline TVec3f volumeOffset(const TVec3f& direction, f32 scale) ALWAYS_INLINE {
 TVec3f result(direction); result.x*=scale; result.y*=scale; result.z*=scale; return result;
}
inline void volumeAdd(register Vec* left, register const Vec* right) ALWAYS_INLINE {
 register f32 rightZ, leftZ, sumZ, sumXY, rightXY, leftXY;
 asm {
  psq_l leftXY, 0(left), 0, 0
  psq_l rightXY, 0(right), 0, 0
  psq_l leftZ, 8(left), 1, 0
  ps_add sumXY, leftXY, rightXY
  psq_l rightZ, 8(right), 1, 0
  ps_add sumZ, leftZ, rightZ
  psq_st sumXY, 0(left), 0, 0
  psq_st sumZ, 8(left), 1, 0
 }
}
inline TVec3f volumePosition(const TVec3f& point, const TVec3f& offset) ALWAYS_INLINE {
 TVec3f result(point); volumeAdd(&result,&offset); return result;
}
extern "C" void fn_80241520(const VolumePositionView* obj, TVec3f* output, const void* controller) {
 TVec3f point, direction;
 fn_8023F1E0(controller,&point); fn_8023F220(controller,&direction);
 TVec3f result=volumePosition(point,volumeOffset(direction,obj->start));
 output->x=result.x; output->y=result.y; output->z=result.z;
}
