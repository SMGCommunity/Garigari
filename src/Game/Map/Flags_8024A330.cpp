#include <revolution.h>
struct Item4A330 { u8 opaque[0xce];bool flagCE,flagCF,flagD0,flagD1; };
extern "C" {
void fn_8024A0F0(void*,const void*,void*,void*,void*,s32,void*);
void fn_8024A420(void*,const void*);
void fn_8024A330(Item4A330* obj,const void* matrix,void* sensor,void* arg4,void* arg5,s32 category,void* arg7) {
 obj->flagD0=true;obj->flagD1=false;
 fn_8024A0F0(obj,matrix,sensor,arg4,arg5,category,arg7);
}
void fn_8024A350(Item4A330* obj,const void* matrix,void* sensor,void* arg4,void* arg5,s32 category,void* arg7) {
 obj->flagD0=false;obj->flagD1=true;
 fn_8024A0F0(obj,matrix,sensor,arg4,arg5,category,arg7);
}
inline bool enabled4A330(Item4A330* obj) ALWAYS_INLINE { return obj->flagCE||obj->flagCF; }
void fn_8024A370(Item4A330* obj,const void* matrix) {
 if(enabled4A330(obj))fn_8024A420(obj,matrix);
}
}
