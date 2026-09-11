#include <revolution.h>
struct Actor51340 { u8 opaque0[0x90]; void* child90; u8 opaque94[0x50]; s32 stateE4; u8 opaqueE8[0x10]; u8 enabledF8; u8 opaqueF9[3]; s32 currentFC, target100, remaining104; };
extern "C" {
bool fn_8024BBC0(const void*);
bool fn_8024BC20(const void*);
void fn_8005AF20(const char*, s32, s32);
extern const char lbl_80697298[], lbl_806972AC[];
void fn_80251340(Actor51340* obj) {
    if (obj->enabledF8 && obj->child90) {
        s32 state = 0;
        if (fn_8024BBC0(obj->child90)) { obj->target100 = 0; state = 0; }
        else if (fn_8024BC20(obj->child90)) { obj->target100 = 100; state = 1; }
        if (obj->stateE4 != state) { obj->remaining104 = 60; obj->stateE4 = state; }
        if (obj->remaining104 > 0) obj->currentFC += (obj->target100 - obj->currentFC) / obj->remaining104--;
        fn_8005AF20(lbl_80697298, -1, -1);
        fn_8005AF20(lbl_806972AC, obj->currentFC, -1);
    }
}
}
