#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Pair51430 { f32 x, y; };
struct Actor51430 { u8 opaque0[0x98]; LiveActorGroup* group98; };
extern "C" {
bool fn_8005E720(Actor51430*, s32);
void fn_8005E830(const char*, const Pair51430*, const Pair51430*);
void fn_8005EB60(const char*, const char*);
void fn_8005EA60(const char*);
void fn_8005EAA0(const char*);
void fn_8001C600(Pair51430*, const TVec3f*);
void fn_8005E8F0(const char*, const Pair51430*);
void fn_8005E790(Actor51430*);
extern const f32 lbl_807DC724;
void fn_80251430(Actor51430* obj) {
    LiveActor* first; LiveActor* child; LiveActor* last; 
    Pair51430 screen;
    if (fn_8005E720(obj, 1)) {
        s32 i;
        for (i = 0; i < obj->group98->mObjectCount; ++i) {
            child = obj->group98->getActor(i);
            Pair51430 second;
            Pair51430 first = {lbl_807DC724, lbl_807DC724};
            second.x = lbl_807DC724; second.y = lbl_807DC724;
            fn_8005E830(child->mName, &second, &first);
        }
        for (i = 0; i < obj->group98->mObjectCount - 1; ++i) {
            first = obj->group98->getActor(i);
            LiveActor* second = obj->group98->getActor(i + 1);
            fn_8005EB60(first->mName, second->mName);
        }
        first = obj->group98->getActor(0);
        last = obj->group98->getActor(obj->group98->mObjectCount - 1);
        fn_8005EB60(last->mName, first->mName);
        fn_8005EA60(first->mName);
        fn_8005EAA0(last->mName);
    }
    for (s32 i = 0; i < obj->group98->mObjectCount; ++i) {
        child = obj->group98->getActor(i);
        fn_8001C600(&screen, &child->mPosition);
        fn_8005E8F0(child->mName, &screen);
    }
    fn_8005E790(obj);
}
}
