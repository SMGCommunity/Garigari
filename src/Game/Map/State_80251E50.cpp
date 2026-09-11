#include "LiveActor/LiveActor.hpp"
struct Value51E50 { bool tag; u16 value; };
struct Child51E50 { u8 opaque0[0x144]; s32 index144; };
struct Actor51E50 : LiveActor { u8 opaque90[0x20]; Child51E50* childB0; u8 opaqueB4[0x44]; u8 enabledF8; };
namespace MR { bool isFirstStep(const LiveActor*); void copyString(wchar_t*, const wchar_t*, unsigned long); }
extern "C" {
void fn_804D5E70(s32);
void fn_8005AFD0(const char*, s32);
Value51E50* fn_8024C740(Value51E50*);
void fn_802510B0(void*, Value51E50*, s32);
bool fn_8024C7A0(const Value51E50*);
void fn_8024C670(wchar_t*, const Value51E50*);
const wchar_t* fn_800413C0(const char*);
void fn_804D4380(const wchar_t*);
void fn_804D3DF0();
void fn_804D62C0();
void fn_80059170(s32);
extern const char lbl_80697298[], lbl_806972AC[];
extern const char* lbl_807CFB10;
void fn_80251E50(Actor51E50* obj) {
    wchar_t name[12];
    Value51E50 value;
    if (MR::isFirstStep(obj)) {
        fn_804D5E70(obj->childB0->index144);
        fn_8005AFD0(lbl_80697298, 30);
        fn_8005AFD0(lbl_806972AC, 30);
        obj->enabledF8 = 0;
    }
    fn_8024C740(&value);
    fn_802510B0(obj, &value, obj->childB0->index144);
    if (fn_8024C7A0(&value)) fn_8024C670(name, &value);
    else MR::copyString(name, fn_800413C0(lbl_807CFB10), 12);
    fn_804D4380(name);
    fn_804D3DF0();
    fn_804D62C0();
    fn_80059170(90);
}
}
