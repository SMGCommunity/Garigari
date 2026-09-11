#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Record51180 { u8 opaque[16]; };
struct Actor51180 { u8 opaque0[0x98]; LiveActorGroup* group98; u8 opaque9C[0x28]; Record51180* records; u8* flags; };
struct Child51180 : LiveActor { u8 opaque90[0xb4]; s32 index; };
extern "C" {
s32 fn_804DF0A0(const Record51180*);
bool fn_804DF140(const Record51180*, s32);
bool fn_804DF070(const Record51180*);
void fn_804D4700();
s32 fn_8003B4A0(s32, s32);
void fn_800422A0(const char*);
extern const char lbl_80697058[];
s32 fn_80251180(const Actor51180* obj, s32 index) {
    if (obj->flags[index - 1]) return fn_804DF0A0(&obj->records[index - 1]);
    return -1;
}
s32 fn_802511B0(const Actor51180* obj, s32 index) {
    for (s32 i = 6; i > 0; --i) if (fn_804DF140(&obj->records[index - 1], i)) return i;
    return 0;
}
bool fn_80251220(Actor51180* obj, const LiveActor* excluded) {
    for (s32 i = 0; i < 3; ++i) {
        Child51180* child = static_cast<Child51180*>(obj->group98->getActor(i));
        if (child != excluded && fn_804DF070(&obj->records[child->index - 1])) return false;
    }
    fn_804D4700();
    return true;
}
void fn_802512B0(void*) {
    const char* names = lbl_80697058;
    switch (fn_8003B4A0(0, 4)) {
    case 0: fn_800422A0(names + 0x168); break;
    case 1: fn_800422A0(names + 0x180); break;
    case 2: fn_800422A0(names + 0x198); break;
    case 3: fn_800422A0(names + 0x1b0); break;
    }
}
}
