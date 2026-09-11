#include <revolution.h>
struct Value4C740 { bool tag; u16 value; };
extern "C" {
Value4C740* fn_8024C740(Value4C740* obj) { obj->tag = false; obj->value = 0; return obj; }
Value4C740* fn_8024C750(Value4C740* obj, const Value4C740* other) {
    *obj = *other;
    return obj;
}
void fn_8024C770(Value4C740* obj, const Value4C740* other) {
    *obj = *other;
}
void fn_8024C790(Value4C740* obj, u16 value) { obj->tag = true; obj->value = value; }
bool fn_8024C7A0(const Value4C740* obj) { return obj->tag; }
u16 fn_8024C7B0(const Value4C740* obj) { return obj->value; }
void fn_8024C7C0(Value4C740* obj, u32 value) { obj->tag = false; obj->value = value; }
bool fn_8024C7D0(const Value4C740* obj) { return !obj->tag; }
u32 fn_8024C7E0(const Value4C740* obj) { return obj->value; }
}
