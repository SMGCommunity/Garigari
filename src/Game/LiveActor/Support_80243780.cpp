#include <revolution.h>
struct Flags43780 { bool a,b,c,d,e; };
struct Item43780 { u8 opaque[0x12]; s16 index; Flags43780* flags; };
struct Group43780 { void* opaque; s32 count; Item43780** items; };
struct Lod43780 { u8 opaque[0x2c]; s16 index; };
struct View43780 { void* resource; s32 count; Flags43780* flags; s32 lodCount; Lod43780** lods; };
extern "C" bool getJMapInfoViewGroupID__2MRFRC12JMapInfoIterPl(const void*,s32*);
extern "C" void fn_80243780(View43780* obj, Group43780* group) {
 for(int i=0;i<group->count;i++) {
  int index=group->items[i]->index;
  if(index<0)index=obj->count;
  group->items[i]->flags=&obj->flags[index];
 }
}
extern "C" void fn_802437D0() {}
extern "C" void fn_802437E0(View43780* obj,Lod43780* lod,const void* iter) {
 s32 index=-1;
 if(getJMapInfoViewGroupID__2MRFRC12JMapInfoIterPl(iter,&index)) {
  lod->index=index;obj->lods[obj->lodCount]=lod;obj->lodCount++;
 }
}
