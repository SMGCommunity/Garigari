#include "LiveActor/LiveActorGroup.hpp"
struct Actor4FFA0 { u8 opaque0[0x98]; LiveActorGroup* group98; };
extern "C" {
void fn_8024CE80(void*);
void fn_8024CEA0(void*);
void fn_8024CE30(void*);
void fn_8024CE70(void*);
void fn_8024FFA0(Actor4FFA0* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) fn_8024CE80(obj->group98->getActor(i));
}
void fn_80250000(Actor4FFA0* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) fn_8024CEA0(obj->group98->getActor(i));
}
void fn_80250060(Actor4FFA0* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) fn_8024CE30(obj->group98->getActor(i));
}
void fn_802500C0(Actor4FFA0* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) fn_8024CE70(obj->group98->getActor(i));
}
}
