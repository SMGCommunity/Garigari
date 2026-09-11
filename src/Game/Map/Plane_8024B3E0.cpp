#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TMatrix.hpp>
extern "C" void fn_8024B3E0(void*,TVec3f* output,const TVec3f* point,const TVec3f& vertex,const TVec3f* normal) {
 TVec3f result(*point);
 TVec3f difference(*point);
 difference.sub(vertex);
 result.add((-*normal).scaleInline(difference.dot(*normal)));
 output->set<float>(result);
}
