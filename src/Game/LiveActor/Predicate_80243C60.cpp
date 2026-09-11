#include <revolution.h>
struct View43C60 { u8 opaque[0x94]; const void* host; u8 tail[0x14]; f32 value; };
extern "C" bool isDead__2MRFPC9LiveActor(const void*);
extern "C" bool isClipped__2MRFPC9LiveActor(const void*);
extern "C" bool isHiddenModel__2MRFPC9LiveActor(const void*);
extern "C" const f32 lbl_807DC5DC;
extern "C" bool fn_80243C60(const View43C60* obj) {
 if(obj->host && (isDead__2MRFPC9LiveActor(obj->host)||isClipped__2MRFPC9LiveActor(obj->host)||isHiddenModel__2MRFPC9LiveActor(obj->host)))return false;
 if(lbl_807DC5DC==obj->value)return false;
 return true;
}
