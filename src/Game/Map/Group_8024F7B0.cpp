#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
void* operator new(unsigned long);
void* operator new[](unsigned long);
struct Actor4F7B0 : LiveActor { u8 opaque90[8]; LiveActorGroup* group98; TVec3f* positions9C; };
struct Method4F7B0 { u32 a, b, c; };
extern "C" { extern const void* lbl_80697478[]; }
struct Callback4F7B0 {
    inline Callback4F7B0(LiveActor* a, const Method4F7B0& m) ALWAYS_INLINE : vtable(lbl_80697478), actor(a), method(m) {}
    const void* vtable; LiveActor* actor; Method4F7B0 method;
};
namespace MR { void* createSceneObj(int); }
extern "C" {
void* __ct__14LiveActorGroupFPCci(void*, const char*, int);
void fn_80021280(void*);
void* __construct_new_array(void*, void (*)(void*), void (*)(void*), u32, u32);
extern const char lbl_806970D0[];
extern const void* lbl_80697484[];
extern const void* lbl_80697478[];
extern const Method4F7B0 lbl_806970C4;
extern const s32 lbl_80648B78[];
extern const f32 lbl_807DC724;
void fn_80250610(LiveActor*, f32);
LiveActor* fn_802506F0(LiveActor*, s32);
void fn_8024CEC0(LiveActor*, Callback4F7B0*);
void fn_80031170(LiveActor*, const TVec3f&);
void fn_8024F7B0(Actor4F7B0* obj) {
    void* allocation = ::operator new(0x20);
    LiveActorGroup* group = static_cast<LiveActorGroup*>(allocation);
    if (allocation) {
        __ct__14LiveActorGroupFPCci(group, lbl_806970D0, 3);
        *reinterpret_cast<const void**>(group) = lbl_80697484;
    }
    obj->group98 = group;
    obj->positions9C = static_cast<TVec3f*>(__construct_new_array(::operator new[](0x34), fn_80021280, 0, 12, 3));
    fn_80250610(obj, lbl_807DC724);
    MR::createSceneObj(0x76);
    Callback4F7B0* callback = new Callback4F7B0(obj, Method4F7B0(lbl_806970C4));
    for (s32 i = 0; i < 3; ++i) {
        LiveActor* child = fn_802506F0(obj, lbl_80648B78[i]);
        fn_8024CEC0(child, callback);
        fn_80031170(child, obj->positions9C[i]);
        obj->group98->registerActor(child);
    }
}
}
