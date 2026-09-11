#include <revolution.h>
struct Area43860 {
 virtual void opaque0();
 virtual void opaque1();
 virtual void opaque2();
 virtual void opaque3();
 virtual void opaque4();
 virtual void opaque5();
 virtual void opaque6();
 virtual void opaque7();
 virtual void opaque8();
 virtual bool test(const void*) const;
 u8 opaque[0x1c]; s32 index,mode;
};
struct Resource43860 { u8 opaque[0x14]; Area43860** areas; u32 unused; s32 count; };
struct Flags43860 { bool a,b,c,d,e; };
struct View43860 { Resource43860* resource; s32 count; Flags43860* flags; };
extern "C" const void* getPlayerPos__2MRFv();
extern "C" void fn_80243860(View43860* obj) {
 if(!obj->resource)return;
 Flags43860* clear;
 for(int i=1;i<obj->count;i++) {
  clear=&obj->flags[i];
  clear->a=false;clear->b=false;clear->c=false;clear->d=false;clear->e=false;
 }
 Area43860* area;
 for(int i=0;i<obj->resource->count;i++) {
  area=obj->resource->areas[i];
  if(area->test(getPlayerPos__2MRFv())) {
   Flags43860* f=&obj->flags[area->index];f->a=true;
   if(area->mode==1)f->b=true;
   else if(area->mode==2)f->c=true;
   else if(area->mode==3)f->d=true;
   else if(area->mode==4){f->a=false;f->e=true;}
  }
 }
}
