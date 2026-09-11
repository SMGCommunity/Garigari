#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
#include "Scene/SceneObjHolder.hpp"
struct Record50790 { u8 opaque[16]; };
struct Actor50790 { u8 opaque0[0x98]; LiveActorGroup* group98; u8 opaque9C[0x28]; Record50790* records; u8* flags; };
struct Child50790 : LiveActor { u8 opaque90[0xb4]; s32 index; u8 opaque148[2]; u8 flag14A; };
struct Value50790 { bool tag; u16 value; };
extern "C" {
bool fn_804DF070(const Record50790*);
Value50790* fn_8024C740(Value50790*);
bool fn_804DF0C0(const Record50790*, u32*);
bool fn_804DF0B0(const Record50790*, u64*);
u32 fn_80250E20(Actor50790*, s32);
void fn_8024C7C0(Value50790*, u32);
bool fn_80355510(const void*);
bool fn_80250E80(Actor50790*, s32);
s32 fn_80250EF0(Actor50790*, s32);
void fn_8024C790(Value50790*, u16);
void fn_8024CD60(LiveActor*, const void*, u8);
void fn_80250790(Actor50790* obj) {
    Child50790* child;
    s32 index;
    s32 offset;
    for (s32 i = 0; i < 3; ++i) {
        child = static_cast<Child50790*>(obj->group98->getActor(i));
        index = child->index;
        offset = (index - 1) * 16;
        if (fn_804DF070(reinterpret_cast<Record50790*>(reinterpret_cast<u8*>(obj->records) + offset))) {
            u64 identity;
            Value50790 value;
            u32 other;
            fn_8024C740(&value);
            if (fn_804DF0C0(reinterpret_cast<Record50790*>(reinterpret_cast<u8*>(obj->records) + offset), &other)) {
                fn_8024C7C0(&value, fn_80250E20(obj, index));
            } else if (fn_804DF0B0(reinterpret_cast<Record50790*>(reinterpret_cast<u8*>(obj->records) + offset), &identity)) {
                if (fn_80355510(MR::getSceneObjHolder()->getObj(0x76))) child->flag14A = 1;
                else if (fn_80250E80(obj, index)) fn_8024C790(&value, (u16)fn_80250EF0(obj, index));
                else child->flag14A = 1;
            }
            fn_8024CD60(child, &value, obj->flags[index - 1]);
        }
    }
}
}
