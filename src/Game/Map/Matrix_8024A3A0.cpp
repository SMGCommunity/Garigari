#include <JGeometry/TMatrix.hpp>
struct Item4A3A0 { const TMtx34f* source; TMtx34f matrix04,matrix34,matrix64,matrix94; u8 opaque[0xa];bool flagCE,flagCF; };
extern "C" {
void fn_8008F8E0(TMtx34f*,const TMtx34f*);
void fn_8024A5F0(void*,TMtx34f*);
void fn_8024A420(Item4A3A0*,const TMtx34f*);
inline bool enabled4A3A0(Item4A3A0* obj) ALWAYS_INLINE { return obj->flagCE||obj->flagCF; }
void fn_8024A3A0(Item4A3A0* obj) {
 if(enabled4A3A0(obj)) {
  TMtx34f matrix;
  fn_8008F8E0(&matrix,obj->source);
  fn_8024A5F0(obj,&matrix);
  fn_8024A420(obj,&matrix);
 }
}
void fn_8024A420(Item4A3A0* obj,const TMtx34f* matrix) {
 fn_8008F8E0(&obj->matrix94,matrix);
 fn_8008F8E0(&obj->matrix34,matrix);
 fn_8008F8E0(&obj->matrix04,matrix);
 PSMTXInverse(obj->matrix34.mMtx,obj->matrix64.mMtx);
}
void fn_8024A480(Item4A3A0* obj,const TMtx34f* matrix) { fn_8008F8E0(&obj->matrix04,matrix); }
void fn_8024A490(Item4A3A0* obj) { fn_8008F8E0(&obj->matrix04,obj->source); }
}
