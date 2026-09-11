#include "LiveActor/LiveActor.hpp"
struct Actor4CD60 : LiveActor {
    u8 flag90;
    u8 opaque91[7];
    void* value98;
    void* entries;
    LiveActor* childA0;
    u8 opaqueA4[0xa7];
    u8 flag14B;
};
struct Config4CD60 { u32 kind, field4; u16 index, padding; u32 fieldC, field10; };
extern "C" {
void fn_8024E370(void*);
void fn_8024C770(void*, const void*);
bool fn_8024C7A0(const void*);
u16 fn_8024C7B0(const void*);
Config4CD60* fn_80355D20(Config4CD60*, u32, u16, u32, u32);
void fn_80354F50(void*, const Config4CD60*);
void fn_8024E030(void*);
void fn_8024DFE0(void*);
void fn_8024E2D0(void*);
extern u32 lbl_807D351C;
void fn_8024CD60(Actor4CD60* obj, const void* value, u8 flag) {
    fn_8024E370(obj);
    fn_8024C770(obj->value98, value);
    if (fn_8024C7A0(value)) {
        Config4CD60 config;
        Config4CD60* configured = fn_80355D20(&config, 0, (u16)fn_8024C7B0(obj->value98), 0x100, 0x21);
        fn_80354F50(obj->childA0, configured);
        fn_8024E030(obj);
        obj->childA0->makeActorAppeared();
    }
    else fn_8024DFE0(obj);
    obj->flag14B = flag;
    fn_8024E2D0(obj);
    obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D351C));
    obj->flag90 = 0;
}
}
