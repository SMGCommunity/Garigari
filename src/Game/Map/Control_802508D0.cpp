#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
class JMapInfoIter;
struct Actor508D0 { u8 opaque0[0x94]; LiveActor* child94; LiveActorGroup* group98; u8 opaque9C[0x14]; LiveActor* childB0; u8 opaqueB4[0x38]; u8 flagEC; u8 opaqueED[3]; void** childrenF0; s32 countF4; };
void* operator new[](unsigned long);
namespace MR {
void requestMovementOff(LiveActor*);
void requestMovementOn(LiveActor*);
s32 getChildObjNum(const JMapInfoIter&);
}
extern "C" {
void fn_8024CFD0(LiveActor*);
void fn_80486AA0(Actor508D0*);
void fn_80486AF0(Actor508D0*);
void* fn_80343090(const JMapInfoIter&, s32);
void fn_802508D0(Actor508D0* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) fn_8024CFD0(obj->group98->getActor(i));
}
void fn_80250930(Actor508D0* obj) {
    if (!obj->flagEC) {
        fn_80486AA0(obj);
        if (obj->child94) MR::requestMovementOff(obj->child94);
        if (obj->childB0) MR::requestMovementOff(obj->childB0);
        obj->flagEC = 1;
    }
}
void fn_80250990(Actor508D0* obj) {
    if (obj->flagEC) {
        fn_80486AF0(obj);
        if (obj->child94) MR::requestMovementOn(obj->child94);
        if (obj->childB0) MR::requestMovementOn(obj->childB0);
        obj->flagEC = 0;
    }
}
void fn_802509F0(Actor508D0* obj, const JMapInfoIter& iter) {
    obj->countF4 = MR::getChildObjNum(iter);
    obj->childrenF0 = new void*[obj->countF4];
    for (s32 i = 0; i < obj->countF4; ++i) obj->childrenF0[i] = fn_80343090(iter, i);
}
}
