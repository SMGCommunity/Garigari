#include <revolution.h>
struct Group490F0 { u32 index; void* items[512]; s32 count; };
inline void** find490F0(void** first,void** last,void* value) ALWAYS_INLINE { while(first!=last && *first!=value)++first;return first; }
extern "C" void fn_802490F0(Group490F0* obj,void* item) {
 s32 count=obj->count;
 void** end=obj->items+count;
 void** found=find490F0(obj->items,end,item);
 if(found==end)return;
 s32 index=found-obj->items;
 obj->items[index]=obj->items[static_cast<int>(count)-1];
 --obj->count;
}
