#include <revolution.h>
struct Virtual43A90 {
 virtual void opaque0();
 virtual void opaque1();
 virtual void opaque2();
 virtual void opaque3();
 virtual void opaque4();
 virtual void opaque5();
 virtual void opaque6();
 virtual void opaque7();
 virtual void opaque8();
 virtual void opaque9();
 virtual void invoke();
};
struct Color43A90 { u8 r,g,b,a; };
struct Vec43A90 { f32 x,y,z; };
struct View43A90 { u8 opaque[0x94]; void* ptr; Color43A90 color; s32 mode; Vec43A90 vec; };
extern "C" void fn_80243A90(Virtual43A90* obj){obj->invoke();}
extern "C" void fn_80243AA0(View43A90* obj,void* ptr){obj->ptr=ptr;}
extern "C" void fn_80243AB0(View43A90* obj,const Color43A90* color){
 Color43A90 c=*color;obj->color.r=c.r;obj->color.g=c.g;obj->color.b=c.b;obj->color.a=c.a;
}
extern "C" void fn_80243AF0(View43A90* obj,s32 mode){obj->mode=mode;}
extern "C" void fn_80243B00(View43A90* obj,const Vec43A90* vec){
 f32 z,y,x;x=vec->x;y=vec->y;z=vec->z;obj->vec.x=x;obj->vec.y=y;obj->vec.z=z;
}
