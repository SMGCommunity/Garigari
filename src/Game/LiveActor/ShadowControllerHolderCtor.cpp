#include "LiveActor/ShadowControllerHolder.hpp"


extern "C" {
    extern const char lbl_80695958[];
    extern const f32 lbl_807DC50C;
    extern void* lbl_807CFAE8;
    void* fn_8004C580(const void*, ...);
    void fn_8004C9F0(u8*, void*, const char*, int);
    void fn_8004C970(f32*, void*, const char*, int);
}
namespace MR { void connectToScene(NameObj*, int, int, int, int); }
ShadowControllerHolder::ShadowControllerHolder() : NameObj(lbl_80695958 + 0x18) {
    ShadowControllerHolder* c = this;
    register const char* names = lbl_80695958;
    c->distance = lbl_807DC50C;
    c->defaultDistance = lbl_807DC50C;
    c->enabled = 0;
    c->defaultEnabled = 0;
    c->registered.array = new ShadowController*[0x500];
    c->registered.capacity = 0x500;
    c->pending.array = new ShadowController*[0x400];
    c->pending.capacity = 0x400;
    MR::connectToScene(reinterpret_cast<NameObj*>(c), 0x2C, -1, -1, -1);
    void* params = fn_8004C580(lbl_807CFAE8);
    if (params) {
        u8 enabled = 0;
        fn_8004C9F0(&enabled, params, names + 0x20, 0);
        c->enabled = enabled;
        fn_8004C970(&c->distance, params, names + 0x28, 0);
        c->defaultDistance = c->distance;
        c->defaultEnabled = c->enabled;
    }
}

// Retail parameter/name pool; Japanese NameObj name is stored as Shift-JIS.
extern "C" __attribute__((section(".data"))) const char lbl_80695958[56] =
    "ShadowControllerParam\0\0\0"
    "\x89\x65\x8A\xC7\x97\x9D\0\0"
    "FarClip\0"
    "FarClipDistance";
