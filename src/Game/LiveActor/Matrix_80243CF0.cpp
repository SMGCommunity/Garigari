#include "JGeometry/TVec.hpp"

// Target-derived view; the owning class identity is not established.
struct View43CF0 {
    u8 prefix[0x14];
    TVec3f translation;
    u8 opaque[0x70];
    MtxPtr matrix;
};
extern "C" void setBaseTRMtx__2MRFP9LiveActorPA4_f(void*, MtxPtr);
extern "C" void calcAndSetBaseMtx__9LiveActorFv(void*);

extern "C" void fn_80243CF0(View43CF0* obj) {
    if (obj->matrix) {
        obj->translation.set<f32>(obj->matrix[0][3],
                           obj->matrix[1][3], obj->matrix[2][3]);
        setBaseTRMtx__2MRFP9LiveActorPA4_f(obj, obj->matrix);
    } else {
        calcAndSetBaseMtx__9LiveActorFv(obj);
    }
}
