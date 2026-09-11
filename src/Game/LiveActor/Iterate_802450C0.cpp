#include "LiveActor/Holder450C0.hpp"
extern "C" {
extern const Method45130 lbl_8069643C;
Call45130 fn_80245130(Opaque45130**,Opaque45130**,Call45130) NO_INLINE;
void* fn_80244F10(void*,const void*,void*);
}
extern "C" void fn_802450C0(Holder450C0* obj) {
 fn_80245130(obj->items,obj->items+obj->count,Call45130(lbl_8069643C));
}
extern "C" Call45130 fn_80245130(Opaque45130** first,Opaque45130** last,Call45130 callback) {
 for(;first!=last;++first)callback(*first);
 return callback;
}
extern "C" void fn_802451B0(Holder450C0* obj,const void*,const void* iter,void* listener) {
 void* item=::operator new(12);
 if(item)item=fn_80244F10(item,iter,listener);
 s32 index=obj->count;obj->count=index+1;obj->items[index]=static_cast<Opaque45130*>(item);
}
