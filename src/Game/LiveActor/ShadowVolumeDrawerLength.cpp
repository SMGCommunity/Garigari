#include <revolution.h>
struct VolumeLengthView { u8 opaque[0x18]; f32 start, end; u8 cut; };
extern "C" {
void* fn_8023FAC0(const void*);
f32 fn_8023F250(const void*);
f32 fn_8023F2C0(const void*);
bool fn_8023F380(const void*);
bool fn_8023F3B0(const void*);
f32 fn_80241640(const VolumeLengthView*, const void*) NO_INLINE;
}
extern "C" f32 fn_80241600(const VolumeLengthView* obj) { return fn_80241640(obj,fn_8023FAC0(obj)); }
extern "C" f32 fn_80241640(const VolumeLengthView* obj, const void* controller) {
 f32 length=fn_8023F250(controller);
 if(obj->cut && fn_8023F380(controller)) length=fn_8023F2C0(controller);
 f32 end, start;
 start = obj->start; end = obj->end;
 length += -start + end;
 return length;
}
extern "C" void fn_802416D0(const void*) {}
extern "C" void fn_802416E0(const void*) {}
extern "C" bool fn_802416F0(const void* obj) { return fn_8023F3B0(fn_8023FAC0(obj)); }
