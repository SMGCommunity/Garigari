#include "LiveActor/ModelManager.hpp"

extern "C" {
void fn_8006DBC0(void*);
void fn_8006DC50(void*);
void fn_800692F0(void*);
void fn_802317F0(void*);
}

// Only the accessed controller pointer offset is recovered here.
struct ModelManagerAnimationState {
    u8 _0[0x20];
    void* _20;
};

extern "C" __attribute__((noinline)) void fn_8023C350(ModelManager*);
extern "C" __attribute__((noinline)) void fn_80069340(void*);

// Explicit opaque dispatch table: target establishes only these slot offsets.
struct ModelManagerModelDispatch {
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
};

extern "C" {
extern u8 lbl_807286C8[];
void fn_805BAD50(void*);
void fn_805BAE30(void*);
bool fn_80231880(void*);
void fn_80231690(void*);
void fn_80231720(void*);
void fn_80069510(void*);
void fn_80069570(void*);
}

#include "System/ResourceInfo.hpp"
#include <cstdio>
void* operator new(unsigned long);
class ResourceHolder { public: ResTable* _0; ResTable* _4; };
namespace MR { ResourceHolder* createAndAddResourceHolder(const char*); }
extern "C" {
extern const char lbl_80695658[8];
bool fn_804C9B10(ResourceHolder*);
bool fn_80232210(void*);
void fn_8023C110(ModelManager*, ResourceHolder*, const char*, ResourceHolder*, u32);
void fn_8023C2D0(ModelManager*);
void fn_8023C1B0(ModelManager*);
void* fn_8023C070(const ModelManager*);
void* fn_802315E0(void*, void*, const f32 (*)[4], void*);
}

// Direct target reconstruction: only controller offset 4 is exposed.
struct ModelManagerController { void* _0; void* _4; };
extern "C" {
void fn_8006D500(void*, const char*);
void fn_8006DA40(void*, const void*);
void fn_8023C3F0(ModelManager*, const char*, const char*, void*);
void fn_80069350(void*, const char*);
void fn_80069400(void*);
__attribute__((noinline)) bool fn_8023BC60(const void*);
}

extern "C" __attribute__((noinline)) void fn_8023BA90(ModelManager*);
extern "C" __attribute__((noinline)) void fn_80231C20(void*, void*, const char*);
extern "C" __attribute__((noinline)) void fn_80231C40(void*, void*);

extern "C" __attribute__((noinline)) void fn_8023BAE0(ModelManager*);
extern "C" __attribute__((noinline)) void fn_80231C60(void*, void*, const char*);
extern "C" __attribute__((noinline)) void fn_80231C80(void*, void*);

extern "C" __attribute__((noinline)) void fn_8023BB30(ModelManager*);
extern "C" __attribute__((noinline)) void fn_80231BE0(void*, void*, const char*);
extern "C" __attribute__((noinline)) void fn_80231C00(void*, void*);

extern "C" __attribute__((noinline)) void fn_8023BB80(ModelManager*);
extern "C" __attribute__((noinline)) void fn_80231BA0(void*, void*, const char*);
extern "C" __attribute__((noinline)) void fn_80231BC0(void*, void*);

extern "C" __attribute__((noinline)) void fn_8023BBD0(ModelManager*);

extern "C" {
void fn_80069460(void*);
void fn_80069450(void*);
void* fn_8006E220(void*);
void fn_8006AED0(void*,void*);
void fn_8006DAC0(void*, int);
void fn_8006DB90(void*, int);
void fn_80069F40(void*);
void fn_80069A00(void*, const char*, void*);

}

struct ModelManagerPlayerTail { u8 _0[0x6C]; void* _6C; };

struct ModelManagerResourceTail { u8 _0[0x3C]; void* _3C; };

extern "C" {
void* fn_800426C0(ResourceHolder*, const char*, u32);
void* fn_80042550(ResourceHolder*);
void* fn_80042330(ResourceHolder*, const char*, ResourceHolder*, u32, void*);
void fn_804C9B60(void*,void*);
void* fn_80069E30(void*,void*,void*);
void* fn_80069DD0(void*,void*,void*);
void* fn_80069E90(void*,void*,void*);
void* fn_80069D70(void*,void*,void*);
void* fn_80069EF0(void*,void*,void*);
}

struct ModelManagerResourceTables {
    void* _0; void* _4; ResTable* _8; ResTable* _C;
    ResTable* _10; void* _14; ResTable* _18;
    u8 _1C[8]; ResTable* _24; u8 _28[0x10]; void* _38;
};

struct ModelManagerControllerState {
    void* _0; void* _4; u8 _8[9]; u8 _11; u8 _12[6]; f32 _18;
};
extern "C" const f32 lbl_807DC4D0;

struct ModelManagerResourceLink { u8 _0[0x64]; void* _64; };

struct ModelManagerModelDataTail { u8 _0[0x54]; void* _54; };
struct ModelManagerPlayerSub { u8 _0[0x14]; u8* _14; };
extern "C" int fn_8050F080(void*, const char*);

extern "C" __attribute__((noinline)) void* fn_8023BE50(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023BE60(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023BE70(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023BE80(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023BE90(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023BEA0(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023C090(const ModelManager* manager);
extern "C" __attribute__((noinline)) void* fn_8023C0A0(const ModelManager* manager);
extern "C" __attribute__((noinline)) void fn_8023B860(ModelManager* m, const char* name, const void* other);
extern "C" __attribute__((noinline)) void fn_8023B8C0(ModelManager* m, const char* name);
extern "C" __attribute__((noinline)) void fn_8023BA90(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BED0(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023B920(ModelManager* m, const char* name);
extern "C" __attribute__((noinline)) void fn_8023BAE0(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BEF0(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023B980(ModelManager* m, const char* name);
extern "C" __attribute__((noinline)) void fn_8023BB30(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BF10(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023B9E0(ModelManager* m, const char* name);
extern "C" __attribute__((noinline)) void fn_8023BB80(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BF30(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BA40(ModelManager* m, const char* name);
extern "C" __attribute__((noinline)) void fn_8023BBD0(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BF50(const ModelManager* m);
extern "C" __attribute__((noinline)) u32 fn_8023BEB0(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BF70(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BF80(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BF90(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BFA0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BFB0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BBF0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BCB0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BD20(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BD90(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BE00(ModelManager* m);
extern "C" __attribute__((noinline)) void* fn_8023C0C0(const ModelManager* m);
extern "C" __attribute__((noinline)) void* fn_8023C0F0(const ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023BFC0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023C350(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023C3F0(ModelManager* m, const char* name, const char* other, void* player);
extern "C" __attribute__((noinline)) void fn_8023C110(ModelManager* m, ResourceHolder* model, const char* name, ResourceHolder* anim, u32 flags);
extern "C" __attribute__((noinline)) void fn_8023C1B0(ModelManager* m);
extern "C" __attribute__((noinline)) void fn_8023C2D0(ModelManager* m);
extern "C" __attribute__((noinline)) bool fn_8023BC60(const void* object);
extern "C" __attribute__((noinline)) void* fn_8023C070(const ModelManager* m);
extern "C" __attribute__((noinline)) void* fn_8023C000(ModelManager* m, const char* name);

ModelManager::ModelManager(const f32 (*projection)[4])
    : _0(0), _4(0), _8(0), _C(0), _10(0), _14(0), _18(0), _1C(0),
      _20(projection), _24(0), _28(0) {}

void ModelManager::init(const char* modelName, const char* animName, bool differed) {
    void* extra;
    void* object;
    char modelArchive[64];
    snprintf(modelArchive, sizeof(modelArchive), lbl_80695658, modelName);
    ResourceHolder* modelResource = MR::createAndAddResourceHolder(modelArchive);
    ResourceHolder* animResource;
    if (!animName) animResource = modelResource;
    else {
        char animArchive[64];
        snprintf(animArchive, sizeof(animArchive), lbl_80695658, animName);
        animResource = MR::createAndAddResourceHolder(animArchive);
    }
    bool hasAnimation = fn_804C9B10(animResource);
    bool modelFlag = fn_80232210(modelResource->_0->getRes(modelName));
    u32 flags = 0x20000;
    if (differed || hasAnimation || modelFlag) flags |= 0x80000;
    fn_8023C110(this, modelResource, modelName, animResource, flags);
    fn_8023C2D0(this);
    if (hasAnimation) fn_8023C1B0(this);
    if (flags & 0x80000) {
        object = ::operator new(0x24);
        if (object) {
            extra = fn_8023C070(this);
            object = fn_802315E0(object, fn_8023C0A0(this), _20, extra);
        }
        _28 = object;
        if (!differed) fn_802317F0(object);
    }
}

void ModelManager::update() {
    void* player = _18;
    if (player) {
        fn_8006DBC0(player);
        fn_8006DC50(player);
    }
    if (_0) fn_800692F0(_0);
    if (_4) fn_800692F0(_4);
    if (_8) fn_800692F0(_8);
    if (_C) fn_800692F0(_C);
    if (_10) fn_800692F0(_10);
}

void ModelManager::calcAnim() {
    fn_8023C350(this);
    updateDL(true);
    u8* player = static_cast<u8*>(_18);
    if (player) {
        player[0x88] = 0;
        player[0x89] = 0;
    }
    if (_0) fn_80069340(_0);
    if (_4) fn_80069340(_4);
    if (_8) fn_80069340(_8);
    if (_C) fn_80069340(_C);
    if (_10) fn_80069340(_10);
}

void ModelManager::calcView() {
    void* model = fn_8023C0A0(this);
    static_cast<ModelManagerModelDispatch*>(model)->slot1C();
}

void ModelManager::entry() {
    void* model = fn_8023C0A0(this);
    static_cast<ModelManagerModelDispatch*>(model)->slot0C();
}

void ModelManager::newDifferedDLBuffer() {
    fn_802317F0(_28);
}

void ModelManager::updateDL(bool doUpdate) {
    fn_805BAD50(lbl_807286C8);
    bool active = false;
    if (_28 && fn_80231880(_28)) active = true;
    if (active) {
        fn_80231690(_28);
        if (_0) fn_80069510(_0);
        if (_4) fn_80069510(_4);
        if (_8) fn_80069510(_8);
        if (_C) fn_80069510(_C);
    }
    static_cast<ModelManagerModelDispatch*>(fn_8023C0A0(this))->slot14();
    if (active) {
        if (doUpdate) fn_80231720(_28);
        if (_0) fn_80069570(_0);
        if (_4) fn_80069570(_4);
        if (_8) fn_80069570(_8);
        if (_C) fn_80069570(_C);
    }
    fn_805BAE30(lbl_807286C8);
}

void ModelManager::startBck(const char* name, const char* other) {
    fn_8006D500(_18, name);
    fn_8006DA40(_18, 0);
    fn_8023C3F0(this, name, other, 0);
}

extern "C" void fn_8023B860(ModelManager* m, const char* name, const void* other) {
    fn_8006D500(m->_18, name);
    fn_8006DA40(m->_18, 0);
    fn_8006DA40(m->_18, other);
}

extern "C" void fn_8023B8C0(ModelManager* m, const char* name) {
    fn_8023BA90(m);
    fn_80069350(m->_0, name);
    fn_80231C20(m->_28, static_cast<ModelManagerController*>(m->_0)->_4, name);
}

extern "C" void fn_8023B920(ModelManager* m, const char* name) {
    fn_8023BAE0(m);
    fn_80069350(m->_4, name);
    fn_80231C60(m->_28, static_cast<ModelManagerController*>(m->_4)->_4, name);
}

extern "C" void fn_8023B980(ModelManager* m, const char* name) {
    fn_8023BB30(m);
    fn_80069350(m->_8, name);
    fn_80231BE0(m->_28, static_cast<ModelManagerController*>(m->_8)->_4, name);
}

extern "C" void fn_8023B9E0(ModelManager* m, const char* name) {
    fn_8023BB80(m);
    fn_80069350(m->_C, name);
    fn_80231BA0(m->_28, static_cast<ModelManagerController*>(m->_C)->_4, name);
}

extern "C" void fn_8023BA40(ModelManager* m, const char* name) {
    fn_8023BBD0(m);
    fn_80069350(m->_10, name);
}

extern "C" void fn_8023BA90(ModelManager* m) {
    void* resource = static_cast<ModelManagerController*>(m->_0)->_4;
    if (resource) {
        fn_80231C40(m->_28, resource);
        fn_80069400(m->_0);
    }
}

extern "C" void fn_8023BAE0(ModelManager* m) {
    void* resource = static_cast<ModelManagerController*>(m->_4)->_4;
    if (resource) {
        fn_80231C80(m->_28, resource);
        fn_80069400(m->_4);
    }
}

extern "C" void fn_8023BB30(ModelManager* m) {
    void* resource = static_cast<ModelManagerController*>(m->_8)->_4;
    if (resource) {
        fn_80231C00(m->_28, resource);
        fn_80069400(m->_8);
    }
}

extern "C" void fn_8023BB80(ModelManager* m) {
    void* resource = static_cast<ModelManagerController*>(m->_C)->_4;
    if (resource) {
        fn_80231BC0(m->_28, resource);
        fn_80069400(m->_C);
    }
}

extern "C" void fn_8023BBD0(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_10);
    if (controller->_4) fn_80069400(controller);
}

extern "C" void fn_8023BBF0(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_0);
    if (controller->_4 && fn_8023BC60(controller)) {
        fn_80231C20(m->_28, static_cast<ModelManagerController*>(m->_0)->_4, "");
        fn_80069450(m->_0);
    }
}

extern "C" bool fn_8023BC60(const void* object) {
    const ModelManagerControllerState* c = static_cast<const ModelManagerControllerState*>(object);
    bool result = true;
    bool stopped = true;
    if (c->_4 && (c->_11 & 1) != 1) stopped = false;
    if (!stopped) {
        f32 frame = c->_18;
        if (lbl_807DC4D0 != frame) result = false;
    }
    return result;
}

extern "C" void fn_8023BCB0(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_4);
    if (controller->_4 && fn_8023BC60(controller)) {
        fn_80231C60(m->_28, static_cast<ModelManagerController*>(m->_4)->_4, "");
        fn_80069450(m->_4);
    }
}

extern "C" void fn_8023BD20(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_8);
    if (controller->_4 && fn_8023BC60(controller)) {
        fn_80231BE0(m->_28, static_cast<ModelManagerController*>(m->_8)->_4, "");
        fn_80069450(m->_8);
    }
}

extern "C" void fn_8023BD90(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_C);
    if (controller->_4 && fn_8023BC60(controller)) {
        fn_80231BA0(m->_28, static_cast<ModelManagerController*>(m->_C)->_4, "");
        fn_80069450(m->_C);
    }
}

extern "C" void fn_8023BE00(ModelManager* m) {
    ModelManagerController* controller = static_cast<ModelManagerController*>(m->_10);
    if (controller->_4 && fn_8023BC60(controller)) {
        fn_80069450(m->_10);
    }
}

extern "C" void* fn_8023BE50(const ModelManager* manager) {
    return static_cast<ModelManagerAnimationState*>(manager->_18)->_20;
}

extern "C" void* fn_8023BE60(const ModelManager* manager) {
    return static_cast<u8*>(manager->_0) + 0xC;
}

extern "C" void* fn_8023BE70(const ModelManager* manager) {
    return static_cast<u8*>(manager->_4) + 0xC;
}

extern "C" void* fn_8023BE80(const ModelManager* manager) {
    return static_cast<u8*>(manager->_8) + 0xC;
}

extern "C" void* fn_8023BE90(const ModelManager* manager) {
    return static_cast<u8*>(manager->_C) + 0xC;
}

extern "C" void* fn_8023BEA0(const ModelManager* manager) {
    return static_cast<u8*>(manager->_10) + 0xC;
}

extern "C" u32 fn_8023BEB0(const ModelManager* m) {
    const u8* player = static_cast<const u8*>(m->_18);
    player += player[0x54] * 0x18;
    return player[0x29] & 1;
}

extern "C" bool fn_8023BED0(const ModelManager* m) {
    if (m->_0) return fn_8023BC60(m->_0);
    return false;
}

extern "C" bool fn_8023BEF0(const ModelManager* m) {
    if (m->_4) return fn_8023BC60(m->_4);
    return false;
}

extern "C" bool fn_8023BF10(const ModelManager* m) {
    if (m->_8) return fn_8023BC60(m->_8);
    return false;
}

extern "C" bool fn_8023BF30(const ModelManager* m) {
    if (m->_C) return fn_8023BC60(m->_C);
    return false;
}

extern "C" bool fn_8023BF50(const ModelManager* m) {
    if (m->_10) return fn_8023BC60(m->_10);
    return false;
}

extern "C" void fn_8023BF70(ModelManager* m) { fn_80069460(m->_0); }

extern "C" void fn_8023BF80(ModelManager* m) { fn_80069460(m->_4); }

extern "C" void fn_8023BF90(ModelManager* m) { fn_80069460(m->_C); }

extern "C" void fn_8023BFA0(ModelManager* m) { fn_80069460(m->_8); }

extern "C" void fn_8023BFB0(ModelManager* m) { fn_80069460(m->_10); }

extern "C" void fn_8023BFC0(ModelManager* m) {
    void* model = fn_8023C0A0(m);
    fn_8006AED0(static_cast<ModelManagerPlayerTail*>(m->_18)->_6C,
               static_cast<ModelManagerController*>(model)->_4);
}

extern "C" void* fn_8023C000(ModelManager* m, const char* name) {
    void* model = fn_8023C0A0(m);
    ModelManagerModelDataTail* data = static_cast<ModelManagerModelDataTail*>(static_cast<ModelManagerController*>(model)->_4);
    int index = fn_8050F080(data->_54, name);
    u8* entries = static_cast<ModelManagerPlayerSub*>(static_cast<ModelManagerPlayerTail*>(m->_18)->_6C)->_14;
    switch (reinterpret_cast<u32>(entries)) {
    case 0: return 0;
    default: return entries + index * 0x70;
    }
}

extern "C" void* fn_8023C070(const ModelManager* m) {
    switch (reinterpret_cast<u32>(m->_14)) {
    case 0: return m->_24;
    default: return static_cast<ModelManagerResourceLink*>(m->_14)->_64;
    }
}

extern "C" void* fn_8023C090(const ModelManager* manager) {
    return manager->_24;
}

extern "C" void* fn_8023C0A0(const ModelManager* manager) {
    switch (reinterpret_cast<u32>(manager->_18)) {
    case 0: return manager->_1C;
    default: return *static_cast<void**>(manager->_18);
    }
}

extern "C" void* fn_8023C0C0(const ModelManager* m) {
    return static_cast<ModelManagerController*>(fn_8023C0A0(m))->_4;
}

extern "C" void* fn_8023C0F0(const ModelManager* m) {
    if (m->_18) return fn_8006E220(m->_18);
    return 0;
}

extern "C" void fn_8023C110(ModelManager* m, ResourceHolder* model, const char* name, ResourceHolder* anim, u32 flags) {
    m->_24 = model;
    if (!anim->_4->mResourceNum) m->_1C = fn_800426C0(model,name,flags);
    else {
        m->_14 = fn_80042550(anim);
        m->_18 = fn_80042330(model,name,anim,flags,m->_14);
    }
}

extern "C" void fn_8023C1B0(ModelManager* m) {
    void* model;
    ModelManagerResourceTables* r = static_cast<ModelManagerResourceTables*>(fn_8023C070(m));
    model = static_cast<ModelManagerController*>(fn_8023C0A0(m))->_4;
    if (!r->_38) fn_804C9B60(r, model);
    if (r->_8->mResourceNum) {
        void* object = ::operator new(0x28);
        if (object) object = fn_80069E30(object, r, model);
        m->_0 = object;
    }
    if (r->_18->mResourceNum) {
        void* object = ::operator new(0x28);
        if (object) object = fn_80069DD0(object, r, model);
        m->_4 = object;
    }
    if (r->_10->mResourceNum) {
        void* object = ::operator new(0x28);
        if (object) object = fn_80069E90(object, r, model);
        m->_8 = object;
    }
    if (r->_C->mResourceNum) {
        void* object = ::operator new(0x28);
        if (object) object = fn_80069D70(object, r, model);
        m->_C = object;
    }
}

extern "C" void fn_8023C2D0(ModelManager* m) {
    ModelManagerResourceTables* r = static_cast<ModelManagerResourceTables*>(fn_8023C070(m));
    if (r->_24->mResourceNum) {
        void* object = ::operator new(0x28);
        if (object) {
            ResTable* table = r->_24;
            object = fn_80069EF0(object, table, fn_8023C0A0(m));
        }
        m->_10 = object;
    }
}

extern "C" void fn_8023C350(ModelManager* m) {
    if (m->_18) fn_8006DAC0(m->_18, 0);
    if (m->_10) fn_80069F40(m->_10);
    fn_805BAD50(lbl_807286C8);
    static_cast<ModelManagerModelDispatch*>(fn_8023C0A0(m))->slot10();
    fn_805BAE30(lbl_807286C8);
    if (m->_18) fn_8006DB90(m->_18, 0);
}

extern "C" void fn_8023C3F0(ModelManager* m, const char* name, const char* other, void* player) {
    if (!player) player = m->_18;
    void* resource = static_cast<ModelManagerResourceTail*>(fn_8023C070(m))->_3C;
    if (resource) {
        if (!other) other = name;
        fn_80069A00(resource, other, player);
    }
}

extern "C" __attribute__((section(".data"))) const char lbl_80695658[8] = "%s.arc";
extern "C" const f32 lbl_807DC4D0 = 0.0f;

