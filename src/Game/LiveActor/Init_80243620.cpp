#include <revolution.h>
struct Entry43620 { u8 opaque[0x20]; s32 index; };
struct Resource43620 { u8 opaque[0x14]; Entry43620** entries; u32 unused; s32 count; };
struct Flags43620 { bool a,b,c,d,e; };
struct Lod43620 { u8 opaque[0x2c]; s16 index; };
struct View43620 { Resource43620* resource; s32 count; Flags43620* flags; s32 lodCount; Lod43620** lods; };
extern "C" Resource43620* fn_800615B0(const char*);
extern "C" void setViewCtrlPtr__7LodCtrlFPCbPCbPCbPCb(Lod43620*,const bool*,const bool*,const bool*,const bool*);
extern "C" const char lbl_80696048[];
extern "C" void fn_80243620(View43620* obj) {
 if(obj->count==0)obj->count=1;
 obj->resource=fn_800615B0(lbl_80696048);
 if(obj->resource)for(int i=0;i<obj->resource->count;i++) {
  int index=obj->resource->entries[i]->index;
  if(index>=obj->count)obj->count=index+1;
 }
 obj->flags=new Flags43620[obj->count+1];
 for(int i=0;i<obj->count+1;i++) {
  Flags43620* f=&obj->flags[i];
  f->a=false;f->b=false;f->c=false;f->d=false;f->e=false;
 }
 obj->flags[0].a=true;
 for(int i=0;i<obj->lodCount;i++) {
  Lod43620* lod=obj->lods[i];int index=lod->index;
  if(index<0)index=obj->count;
  Flags43620* f=&obj->flags[index];
  setViewCtrlPtr__7LodCtrlFPCbPCbPCbPCb(lod,&f->b,&f->c,&f->d,&f->e);
 }
}
