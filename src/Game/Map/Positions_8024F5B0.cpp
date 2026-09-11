#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Record4F5B0 { u8 data[0x94]; };
struct Actor4F5B0 : LiveActor {
    u8 opaque90[8];
    LiveActorGroup* group98;
    TVec3f* positions9C;
    u8 opaqueA0[0x1c];
    s32 fieldBC;
    u8 opaqueC0[0x28];
    Record4F5B0* recordsE8;
};
extern "C" {
extern const f32 lbl_807DC724, lbl_807DC73C, lbl_807DC740, lbl_807DC744;
void fn_80031170(Record4F5B0*, const TVec3f&);
void fn_80251340(LiveActor*);
inline void copy4F5B0(TVec3f& dst, const TVec3f& src) ALWAYS_INLINE { JGeometry::setTVec3f(&src.x, &dst.x); }
void fn_8024F5B0(Actor4F5B0* obj) {
    s32 i;
    obj->fieldBC = 0;
    for (i = 0; i < obj->group98->mObjectCount; ++i) {
        TVec3f& position = obj->group98->getActor(i)->mPosition;
        copy4F5B0(position, obj->positions9C[i].scaleInline(lbl_807DC740).addInline(position.scaleInline(lbl_807DC73C)));
    }
    for (i = 0; i < obj->group98->mObjectCount; ++i) {
        fn_80031170(&obj->recordsE8[i], obj->group98->getActor(i)->mPosition.addInline(TVec3f(lbl_807DC724, lbl_807DC744, lbl_807DC724)));
    }
    fn_80251340(obj);
}
}
