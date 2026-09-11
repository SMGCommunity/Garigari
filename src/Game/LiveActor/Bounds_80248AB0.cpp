#include <JGeometry/TVec.hpp>
extern "C" bool fn_80248AB0(void*,const TVec3f* low,const TVec3f* high,const TVec3f* point,f32 radius) {
 if(point->x<low->x-radius || high->x+radius<point->x)return false;
 if(point->y<low->y-radius || high->y+radius<point->y)return false;
 if(point->z<low->z-radius || high->z+radius<point->z)return false;
 return true;
}
