#include <revolution.h>
class CallbackTarget43050;
struct Callback43050 { const void* vtable; CallbackTarget43050* target; void (CallbackTarget43050::*method)(); };
extern "C" void fn_80243050(const Callback43050* obj) { (obj->target->*obj->method)(); }
