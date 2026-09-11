#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Actor4FD70 : LiveActor { u8 opaque90[8]; LiveActorGroup* group98; };
extern "C" {
extern const char lbl_80697178[];
void* fn_8024C210(void*, const char*);
void* fn_8024FD70(void* obj) { return fn_8024C210(obj, lbl_80697178); }
void fn_8024FD80(Actor4FD70* obj) {
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) obj->group98->getActor(i)->appear();
}
}
