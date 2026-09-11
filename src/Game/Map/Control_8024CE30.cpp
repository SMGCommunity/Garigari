#include <revolution/types.h>
struct Child4CE30 {
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
};
struct Actor4CE30 {
    u8 opaque0[0x98];
    void* value98;
    u8 opaque9C[8];
    Child4CE30* childA4;
    u8 opaqueA8[0xa0];
    u8 flag148, flag149;
    u8 opaque14A[10];
    void* field154;
};
extern "C" {
void fn_8024CF80(void*);
void fn_8046E4F0(void*);
void fn_8024C770(void*, const void*);
void fn_8024CE30(Actor4CE30* obj) {
    if (obj->flag148) fn_8024CF80(obj);
    obj->flag149 = 1;
}
void fn_8024CE70(Actor4CE30* obj) { obj->flag149 = 0; }
void fn_8024CE80(Actor4CE30* obj) {
    obj->childA4->slot2C();
}
void fn_8024CEA0(Actor4CE30* obj) { fn_8046E4F0(obj->childA4); }
void fn_8024CEB0(const Actor4CE30* obj, void* output) { fn_8024C770(output, obj->value98); }
void fn_8024CEC0(Actor4CE30* obj, void* value) { obj->field154 = value; }
}
