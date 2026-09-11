#include "LiveActor/ShadowControllerList.hpp"
#include "Scene/SceneObjHolder.hpp"
#include <JGeometry.hpp>
#include "LiveActor/LiveActor.hpp"

// Field offsets follow retail loads/stores; unrecovered pointer meanings stay opaque.
struct ShadowController {
    LiveActor* _0;
    const char* _4;
    const char* _8;
    void* _C;
    void* _10;
    void* _14;
    MtxPtr _18;
    MtxPtr _1C;
    const TVec3f* _20;
    const TVec3f* _24;
    const TVec3f* _28;
    const TVec3f* _2C;
    TVec3f _30, _3C, _48, _54, _60;
    u8 _6C, _6D, _6E, _6F, _70, _71, _72, _73;
    f32 _74, _78;
    u8 _7C, _7D, _7E;
};

struct ShadowPendingHolder {
    u8 _0[0x20];
    MR::Vector<MR::AssignableArray<ShadowController*> > pending;
};

extern "C" {
    bool fn_8023F3B0(const ShadowController*);
    void fn_8023EEC0(ShadowController*);
    void fn_8023EF90(ShadowController*);
    void fn_8023F1E0(const ShadowController*, TVec3f*);
}
namespace MR { f32 calcCameraDistanceZ(const TVec3f&); }

// Flow adapts CC0 Petari fa77cd4d; Galaxy 2 state and holder offsets are verified.

extern "C" {
    void fn_8023FAD0(void*, ShadowController*);
    void fn_805C86D0(MtxPtr, const TVec3f*, TVec3f*);
    bool fn_80031520(const LiveActor*);
    extern const f32 lbl_807DC500;
    extern const f32 lbl_807DC504;
}

extern "C" {
    extern const f32 lbl_807DC508;
    extern const f32 lbl_807DC510;
    extern const f32 lbl_807DC514;
    extern const char lbl_807CFAEC[4];
    bool fn_8003F1A0(const TVec3f*, f32);
}
namespace MR {
    void addShadowController(ShadowController*);
    void makeMtxRotate(MtxPtr, const TVec3f&);
}

extern "C" bool fn_8002B470(LiveActor*, const TVec3f*, TVec3f*, void*, void*);
extern "C" bool fn_8002B450(LiveActor*, const TVec3f*, TVec3f*, void*, void*);

// Retail fn_80256A30 initializes three words and seven vectors through offset 0x54.
struct ShadowProjectionResult {
    void* _0;
    u32 _4;
    void* _8;
    Vec _C[7];
};
extern "C" {
    void fn_80256A30(ShadowProjectionResult*);
    const TVec3f* fn_80256CC0(const ShadowProjectionResult*, s32);
    TVec3f fn_80023780(const TVec3f&, f32);
    bool fn_80038040(TVec3f*, ShadowProjectionResult*, const TVec3f&, const TVec3f&, void*, void*);
    bool fn_800381D0(TVec3f*, ShadowProjectionResult*, const TVec3f&, const TVec3f&, void*, void*);
}

extern "C" ShadowController* fn_8023ECC0(ShadowController* c, LiveActor* host, const char* name);
extern "C" void fn_8023EDC0(ShadowController* controller);
extern "C" void fn_8023EE10(ShadowController* controller);
extern "C" void fn_8023EE60(ShadowController* controller, f32 distance);
extern "C" void fn_8023EEC0(ShadowController* c);
extern "C" void fn_8023EF90(ShadowController* c);
extern "C" void* fn_8023F0E0(const ShadowController* c);
extern "C" LiveActor* fn_8023F0F0(const ShadowController* c);
extern "C" void fn_8023F100(ShadowController* c, void* drawer);
extern "C" void fn_8023F120(const ShadowController* c, TMtx34f* out);
extern "C" void fn_8023F1E0(const ShadowController* c, TVec3f* out);
extern "C" void fn_8023F220(const ShadowController* c, TVec3f* out);
extern "C" f32 fn_8023F250(const ShadowController* c);
extern "C" void fn_8023F260(const ShadowController* c, TVec3f* out);
extern "C" void fn_8023F290(const ShadowController* c, TVec3f* out);
extern "C" f32 fn_8023F2C0(const ShadowController* c);
extern "C" bool fn_8023F380(const ShadowController* c);
extern "C" bool fn_8023F3B0(const ShadowController* c);
extern "C" bool fn_8023F400(const ShadowController* c);
extern "C" bool fn_8023F440(const ShadowController* c);
extern "C" bool fn_8023F490(const ShadowController* c);
extern "C" void fn_8023F4B0(ShadowController* c, const char* name);
extern "C" void fn_8023F4C0(ShadowController* c, const TVec3f* p);
extern "C" void fn_8023F4D0(ShadowController* c, MtxPtr matrix, const TVec3f& offset);
extern "C" void fn_8023F4F0(ShadowController* c, const TVec3f& p);
extern "C" void fn_8023F530(ShadowController* c, const TVec3f* p);
extern "C" void fn_8023F540(ShadowController* c, const TVec3f* p, const TVec3f* n);
extern "C" void fn_8023F560(ShadowController* c, const TVec3f& p);
extern "C" void fn_8023F5A0(ShadowController* c, const TVec3f& p);
extern "C" void fn_8023F5B0(ShadowController* c, f32 v);
extern "C" void fn_8023F5C0(ShadowController* c, f32 v);
extern "C" void fn_8023F5D0(ShadowController* c);
extern "C" void fn_8023F5E0(ShadowController* c);
extern "C" void fn_8023F5F0(ShadowController* c, const TVec3f& p, const TVec3f& n, bool flag);
extern "C" void fn_8023F650(ShadowController* c);
extern "C" void fn_8023F660(ShadowController* c);
extern "C" void fn_8023F670(ShadowController* c);
extern "C" void fn_8023F690(ShadowController* c);
extern "C" void fn_8023F6F0(ShadowController* c);
extern "C" void fn_8023F750(ShadowController* c);
extern "C" void fn_8023F760(ShadowController* c);
extern "C" void fn_8023F7C0(ShadowController* c);
extern "C" void fn_8023F820(ShadowController* c);
extern "C" void fn_8023F830(ShadowController* c, void* filter);
extern "C" void fn_8023F840(ShadowController* c);
extern "C" void fn_8023F850(ShadowController* c);
extern "C" bool isFollowHostScale__16ShadowControllerCFv(const ShadowController* c);
extern "C" void onVisibleSyncHost__16ShadowControllerFv(ShadowController* c);
extern "C" void offVisibleSyncHost__16ShadowControllerFv(ShadowController* c);
extern "C" void fn_8023F890(ShadowController* c);
extern "C" void invalidate__16ShadowControllerFv(ShadowController* c);

extern "C" ShadowController* fn_8023ECC0(ShadowController* c, LiveActor* host, const char* name) {
    c->_0 = host;
    c->_4 = name;
    c->_8 = lbl_807CFAEC;
    c->_C = nullptr;
    c->_10 = nullptr;
    c->_14 = nullptr;
    c->_18 = nullptr;
    c->_1C = nullptr;
    c->_20 = nullptr;
    c->_24 = nullptr;
    c->_28 = nullptr;
    c->_2C = nullptr;
    c->_30.x = lbl_807DC504;
    c->_30.y = lbl_807DC504;
    c->_30.z = lbl_807DC504;
    c->_3C.x = lbl_807DC504;
    c->_3C.y = lbl_807DC508;
    c->_3C.z = lbl_807DC504;
    c->_48.x = lbl_807DC504;
    c->_48.y = lbl_807DC504;
    c->_48.z = lbl_807DC504;
    c->_54.x = lbl_807DC504;
    c->_54.y = lbl_807DC500;
    c->_54.z = lbl_807DC504;
    c->_60.x = lbl_807DC504;
    c->_60.y = lbl_807DC504;
    c->_60.z = lbl_807DC504;
    c->_6C = 1;
    c->_6D = 0;
    c->_6E = 0;
    c->_6F = 0;
    c->_70 = 0;
    c->_71 = 0;
    c->_72 = 0;
    c->_73 = 0;
    c->_74 = lbl_807DC510;
    c->_78 = lbl_807DC504;
    c->_7C = 0;
    c->_7D = 1;
    c->_7E = 1;
    MR::createSceneObj(0x4C);
    MR::addShadowController(c);
    return c;
}

extern "C" void fn_8023EDC0(ShadowController* controller) {
    if (!controller->_70) {
        controller->_70 = 1;
        ShadowController* queued = controller;
        ShadowPendingHolder* holder = reinterpret_cast<ShadowPendingHolder*>(MR::getSceneObjHolder()->getObj(0x4C));
        holder->pending.push_back(queued);
    }
}

extern "C" void fn_8023EE10(ShadowController* controller) {
    if (fn_8023F3B0(controller)) {
        fn_8023EEC0(controller);
        fn_8023EF90(controller);
    }
    controller->_70 = 0;
}

extern "C" void fn_8023EE60(ShadowController* controller, f32 distance) {
    TVec3f position;
    fn_8023F1E0(controller, &position);
    controller->_73 = MR::calcCameraDistanceZ(position) >= distance;
}

extern "C" void fn_8023EEC0(ShadowController* c) {
    if (fn_8023F440(c)) {
        TVec3f position;
        fn_8023F1E0(c, &position);
        TVec3f old(c->_3C);
        if (!(fn_8023F490(c) && fn_8002B470(c->_0, &position, &c->_3C, nullptr, nullptr))) {
            if (!fn_8002B450(c->_0, &position, &c->_3C, nullptr, nullptr)) c->_3C.setPS(old);
        }
        if (c->_6D == 2 || c->_6D == 5) ++c->_72;
    }
}

extern "C" void fn_8023EF90(ShadowController* c) {
    if (fn_8023F400(c)) {
        ShadowProjectionResult result;
        fn_80256A30(&result);
        TVec3f position, direction;
        fn_8023F1E0(c, &position);
        fn_8023F220(c, &direction);
        position -= fn_80023780(direction, c->_74);
        switch (c->_6E) {
        case 0:
            c->_6F = fn_80038040(&c->_48, &result, position, fn_80023780(direction, c->_78 + c->_74), c->_14, nullptr);
            break;
        case 1:
            c->_6F = fn_800381D0(&c->_48, &result, position, fn_80023780(direction, c->_78 + c->_74), c->_14, nullptr);
            break;
        }
        if (c->_6F) {
            c->_10 = result._8;
            c->_54.set<f32>(*fn_80256CC0(&result, 0));
        } else c->_10 = nullptr;
        if (c->_6C == 2) ++c->_71;
    }
}

extern "C" void* fn_8023F0E0(const ShadowController* c) { return c->_C; }

extern "C" LiveActor* fn_8023F0F0(const ShadowController* c) { return c->_0; }

extern "C" void fn_8023F100(ShadowController* c, void* drawer) {
    c->_C = drawer;
    fn_8023FAD0(drawer, c);
}

extern "C" void fn_8023F120(const ShadowController* c, TMtx34f* out) {
    if (!fn_8003F1A0(&c->_60, lbl_807DC514)) {
        out->identity();
        MR::makeMtxRotate(reinterpret_cast<MtxPtr>(out), c->_60);
    } else {
        out->identity();
    }
    if (c->_18) {
        PSMTXConcat(c->_18, reinterpret_cast<MtxPtr>(out), reinterpret_cast<MtxPtr>(out));
    } else if (c->_0->getBaseMtx()) {
        PSMTXConcat(c->_0->getBaseMtx(), reinterpret_cast<MtxPtr>(out), reinterpret_cast<MtxPtr>(out));
    }
}

extern "C" void fn_8023F1E0(const ShadowController* c, TVec3f* out) {
    if (c->_20) out->set<f32>(*c->_20);
    else if (c->_1C) fn_805C86D0(c->_1C, &c->_30, out);
    else out->set<f32>(c->_30);
}

extern "C" void fn_8023F220(const ShadowController* c, TVec3f* out) {
    if (c->_24) out->set<f32>(*c->_24);
    else out->set<f32>(c->_3C);
}

extern "C" f32 fn_8023F250(const ShadowController* c) { return c->_78; }

extern "C" void fn_8023F260(const ShadowController* c, TVec3f* out) {
    if (c->_28) out->set<f32>(*c->_28);
    else out->set<f32>(c->_48);
}

extern "C" void fn_8023F290(const ShadowController* c, TVec3f* out) {
    if (c->_2C) out->set<f32>(*c->_2C);
    else out->set<f32>(c->_54);
}

// Reconstruction helper: inlines to the retail PSVECDistance call and preserves return allocation.
inline f32 shadowPointDistance(const Vec* a, const Vec* b) { return PSVECDistance(a, b); }
extern "C" f32 fn_8023F2C0(const ShadowController* c) {
    bool projected = false;
    if (c->_6F && c->_7D) projected = true;
    if (!projected) return lbl_807DC508;
    TVec3f position, direction;
    fn_8023F1E0(c, &position);
    fn_8023F220(c, &direction);
    TVec3f difference(c->_48);
    difference -= position;
    f32 dot = direction.dot(difference);
    if (dot < lbl_807DC504) return lbl_807DC504;
    return shadowPointDistance(&position, &c->_48);
}

extern "C" bool fn_8023F380(const ShadowController* c) {
    bool result = false;
    if (c->_6F && c->_7D) result = true;
    return result;
}

extern "C" bool fn_8023F3B0(const ShadowController* c) {
    if (c->_73) return false;
    if (!c->_7D) return false;
    if (c->_7E) return fn_80031520(c->_0);
    return true;
}

extern "C" bool fn_8023F400(const ShadowController* c) {
    if (!c->_6C) return false;
    if (c->_6C == 2) return c->_71 < 1;
    return true;
}

extern "C" bool fn_8023F440(const ShadowController* c) {
    if (!c->_6D || c->_6D == 3) return false;
    if (c->_6D == 2 || c->_6D == 5) return c->_72 < 1;
    return true;
}

extern "C" bool fn_8023F490(const ShadowController* c) {
    return static_cast<u8>(c->_6D + 252) <= 1;
}

extern "C" void fn_8023F4B0(ShadowController* c, const char* name) { c->_8 = name; }

extern "C" void fn_8023F4C0(ShadowController* c, const TVec3f* p) { c->_20 = p; c->_1C = nullptr; }

extern "C" void fn_8023F4D0(ShadowController* c, MtxPtr matrix, const TVec3f& offset) {
    c->_18 = matrix;
    c->_20 = nullptr;
    c->_1C = matrix;
    c->_30.set<f32>(offset);
}

extern "C" void fn_8023F4F0(ShadowController* c, const TVec3f& p) {
    c->_30.set<f32>(p);
    c->_20 = nullptr;
    c->_1C = nullptr;
}

extern "C" void fn_8023F530(ShadowController* c, const TVec3f* p) { c->_24 = p; c->_6D = 0; }

extern "C" void fn_8023F540(ShadowController* c, const TVec3f* p, const TVec3f* n) {
    c->_28 = p; c->_2C = n; c->_6C = 0; c->_6F = 1; c->_10 = nullptr;
}

extern "C" void fn_8023F560(ShadowController* c, const TVec3f& p) {
    c->_3C.set<f32>(p); c->_24 = nullptr; c->_6D = 0;
}

extern "C" void fn_8023F5A0(ShadowController* c, const TVec3f& p) { c->_60.set<f32>(p); }

extern "C" void fn_8023F5B0(ShadowController* c, f32 v) { c->_78 = v; }

extern "C" void fn_8023F5C0(ShadowController* c, f32 v) { c->_74 = v; }

extern "C" void fn_8023F5D0(ShadowController* c) { c->_6E = 0; }

extern "C" void fn_8023F5E0(ShadowController* c) { c->_6E = 1; }

extern "C" void fn_8023F5F0(ShadowController* c, const TVec3f& p, const TVec3f& n, bool flag) {
    c->_48.set<f32>(p); c->_54.set<f32>(n); c->_6F = flag; c->_10 = nullptr;
}

extern "C" void fn_8023F650(ShadowController* c) { c->_6C = 1; }

extern "C" void fn_8023F660(ShadowController* c) { c->_6C = 0; }

extern "C" void fn_8023F670(ShadowController* c) { c->_6C = 2; c->_71 = 0; }

extern "C" void fn_8023F690(ShadowController* c) {
    TVec3f direction(lbl_807DC504, lbl_807DC500, lbl_807DC504);
    c->_3C.set<f32>(direction);
    c->_24 = nullptr;
    c->_6D = 1;
}

extern "C" void fn_8023F6F0(ShadowController* c) {
    TVec3f direction(lbl_807DC504, lbl_807DC500, lbl_807DC504);
    c->_3C.set<f32>(direction);
    c->_24 = nullptr;
    c->_6D = 2;
    c->_72 = 0;
}

extern "C" void fn_8023F750(ShadowController* c) { c->_6D = 0; }

extern "C" void fn_8023F760(ShadowController* c) {
    TVec3f direction(lbl_807DC504, lbl_807DC500, lbl_807DC504);
    c->_3C.set<f32>(direction);
    c->_24 = nullptr;
    c->_6D = 4;
}

extern "C" void fn_8023F7C0(ShadowController* c) {
    TVec3f direction(lbl_807DC504, lbl_807DC500, lbl_807DC504);
    c->_3C.set<f32>(direction);
    c->_24 = nullptr;
    c->_6D = 5;
    c->_72 = 0;
}

extern "C" void fn_8023F820(ShadowController* c) { c->_6D = 3; }

extern "C" void fn_8023F830(ShadowController* c, void* filter) { c->_14 = filter; }

extern "C" void fn_8023F840(ShadowController* c) { c->_7C = 1; }

extern "C" void fn_8023F850(ShadowController* c) { c->_7C = 0; }

extern "C" bool isFollowHostScale__16ShadowControllerCFv(const ShadowController* c) { return c->_7C != 0; }

extern "C" void onVisibleSyncHost__16ShadowControllerFv(ShadowController* c) { c->_7E = 1; }

extern "C" void offVisibleSyncHost__16ShadowControllerFv(ShadowController* c) { c->_7E = 0; }

extern "C" void fn_8023F890(ShadowController* c) { c->_7D = 1; }

extern "C" void invalidate__16ShadowControllerFv(ShadowController* c) { c->_7D = 0; }

// Shared shadow literals reconstructed from retail values; surrounding routines also reference them.
extern "C" u8 lbl_80695958[];
extern "C" void* lbl_807CFAE8 = lbl_80695958;
#pragma section sdata_type ".sdata" ".sdata"
extern "C" __attribute__((section(".sdata"))) const char lbl_807CFAEC[4] = "";
#pragma section sdata_type ".sdata" ".sbss"
extern "C" const f32 lbl_807DC500 = 1.0f;
extern "C" const f32 lbl_807DC504 = 0.0f;
extern "C" const f32 lbl_807DC508 = -1.0f;
extern "C" const f32 lbl_807DC50C = 7000.0f;
extern "C" const f32 lbl_807DC510 = 50.0f;
extern "C" const f32 lbl_807DC514 = 0.001f;
