#include "LiveActor/SensorHitChecker.hpp"
#include "LiveActor/SensorGroup.hpp"
#include "LiveActor/HitSensor.hpp"
#include "NameObj/NameObj.hpp"
#include "Scene/SceneObjHolder.hpp"

// Verified constructor accesses: NameObj prefix, then six group pointers.
struct SensorHitCheckerView {
    const void* _0;
    u8 _4[0x10];
    SensorGroup* _14;
    SensorGroup* _18;
    SensorGroup* _1C;
    SensorGroup* _20;
    SensorGroup* _24;
    SensorGroup* _28;
};
extern "C" {
    void* __ct__7NameObjFPCc(void*, const char*);
    void* __dt__7NameObjFv(void*, int);
    typedef void (*SensorVTableSlot)();
    extern const SensorVTableSlot lbl_8069592C[11];
    extern const char lbl_807CFAE0[4];
    void fn_8023E170(SensorHitCheckerView*, HitSensor*);
    void fn_8023E3F0(const SensorHitCheckerView*, SensorGroup*, SensorGroup*);
    void fn_8023E500(const SensorHitCheckerView*, SensorGroup*);
}
namespace MR { void connectToScene(NameObj*, int, int, int, int); }

inline f32 sensorRadiusSum(f32 a, f32 b) { return a + b; }

namespace MR {
    bool isSensorPlayer(const HitSensor*);
    bool isSensorRide(const HitSensor*);
    bool isSensorRush(const HitSensor*);
    bool isSensorAutoRush(const HitSensor*);
    bool isSensorMapObj(const HitSensor*);
}

namespace MR { bool isClipped(const LiveActor*); }

extern "C" SensorHitCheckerView* fn_8023E020(SensorHitCheckerView* c, const char* name);
extern "C" void fn_8023E150(NameObj* c, const void*);
extern "C" void fn_8023E170(SensorHitCheckerView* c, HitSensor* sensor);
extern "C" void fn_8023E2B0(SensorHitCheckerView* c);
extern "C" void fn_8023E3F0(const SensorHitCheckerView* c, SensorGroup* group1, SensorGroup* group2);
extern "C" void fn_8023E500(const SensorHitCheckerView* c, SensorGroup* group);
extern "C" void fn_8023E600(const SensorHitCheckerView*, HitSensor* a, HitSensor* b);
extern "C" SensorHitCheckerView* __dt__16SensorHitCheckerFv(SensorHitCheckerView* c, int deleting);

extern "C" SensorHitCheckerView* fn_8023E020(SensorHitCheckerView* c, const char* name) {
    __ct__7NameObjFPCc(c, name);
    c->_0 = lbl_8069592C;
    c->_14 = nullptr; c->_18 = nullptr; c->_1C = nullptr;
    c->_20 = nullptr; c->_24 = nullptr; c->_28 = nullptr;
    c->_14 = new SensorGroup(0x10, "Player");
    c->_18 = new SensorGroup(0x80, "Ride");
    c->_1C = new SensorGroup(0x200, lbl_807CFAE0);
    c->_20 = new SensorGroup(0x800, "Simple");
    c->_24 = new SensorGroup(0x400, "MapObj");
    c->_28 = new SensorGroup(0x400, "Character");
    return c;
}

extern "C" void fn_8023E150(NameObj* c, const void*) {
    MR::connectToScene(c, 5, -1, -1, -1);
}

extern "C" void fn_8023E170(SensorHitCheckerView* c, HitSensor* sensor) {
    if (MR::isSensorPlayer(sensor)) sensor->mSensorGroup = c->_14;
    else if (MR::isSensorRide(sensor)) sensor->mSensorGroup = c->_18;
    else if (sensor->isType(0x7A)) sensor->mSensorGroup = c->_1C;
    else if (sensor->isType(0x44) || sensor->isType(0x46) || sensor->isType(0x19)
        || sensor->isType(0x41) || sensor->isType(0x23) || MR::isSensorRush(sensor)
        || MR::isSensorAutoRush(sensor)) sensor->mSensorGroup = c->_20;
    else if (MR::isSensorMapObj(sensor)) sensor->mSensorGroup = c->_24;
    else sensor->mSensorGroup = c->_28;
}

extern "C" void fn_8023E2B0(SensorHitCheckerView* c) {
    c->_14->clear();
    c->_18->clear();
    c->_1C->clear();
    c->_20->clear();
    c->_24->clear();
    c->_28->clear();
    fn_8023E3F0(c, c->_14, c->_28);
    fn_8023E3F0(c, c->_14, c->_24);
    fn_8023E3F0(c, c->_14, c->_18);
    fn_8023E3F0(c, c->_14, c->_20);
    fn_8023E3F0(c, c->_14, c->_1C);
    fn_8023E3F0(c, c->_18, c->_28);
    fn_8023E3F0(c, c->_18, c->_24);
    fn_8023E3F0(c, c->_18, c->_20);
    fn_8023E3F0(c, c->_18, c->_1C);
    fn_8023E3F0(c, c->_1C, c->_28);
    fn_8023E3F0(c, c->_1C, c->_24);
    fn_8023E3F0(c, c->_1C, c->_20);
    fn_8023E3F0(c, c->_28, c->_24);
    fn_8023E500(c, c->_28);
}

extern "C" void fn_8023E3F0(const SensorHitCheckerView* c, SensorGroup* group1, SensorGroup* group2) {
    HitSensor* first;
    HitSensor* second;
    const s32 count1 = group1->mSensorCount;
    for (s32 i = 0; i < count1; ++i) {
        first = group1->mSensors[i];
        const bool firstValid = first->mValidByHost && first->mValidBySystem;
        if (firstValid && !MR::isClipped(first->mHostActor)) {
            const s32 count2 = group2->mSensorCount;
            for (s32 j = 0; j < count2; ++j) {
                second = group2->mSensors[j];
                const bool secondValid = second->mValidByHost && second->mValidBySystem;
                if (secondValid && !MR::isClipped(second->mHostActor)) fn_8023E600(c, first, second);
            }
        }
    }
}

extern "C" void fn_8023E500(const SensorHitCheckerView* c, SensorGroup* group) {
    HitSensor* first;
    HitSensor* second;
    const s32 count = group->mSensorCount;
    for (s32 i = 0; i < count; ++i) {
        first = group->mSensors[i];
        const bool firstValid = first->mValidByHost && first->mValidBySystem;
        if (firstValid && !MR::isClipped(first->mHostActor)) {
            for (s32 j = i; j < count; ++j) {
                second = group->mSensors[j];
                const bool secondValid = second->mValidByHost && second->mValidBySystem;
                if (secondValid && !MR::isClipped(second->mHostActor)) fn_8023E600(c, first, second);
            }
        }
    }
}

extern "C" void fn_8023E600(const SensorHitCheckerView*, HitSensor* a, HitSensor* b) {
    if (a->mHostActor != b->mHostActor) {
        const f32 x = a->mOffset.x - b->mOffset.x;
        const f32 y = a->mOffset.y - b->mOffset.y;
        const f32 z = a->mOffset.z - b->mOffset.z;
        const f32 radius = sensorRadiusSum(a->mRadius, b->mRadius);
        if (!(z * z + (x * x + y * y) >= radius * radius)) {
            if (!b->isType(0x7A)) a->addHitSensor(b);
            if (!a->isType(0x7A)) b->addHitSensor(a);
        }
    }
}

namespace MR {
    void initHitSensorGroup(HitSensor* sensor) {
        SensorHitCheckerView* checker = reinterpret_cast<SensorHitCheckerView*>(getSceneObjHolder()->getObj(0));
        fn_8023E170(checker, sensor);
    }
}

extern "C" SensorHitCheckerView* __dt__16SensorHitCheckerFv(SensorHitCheckerView* c, int deleting) {
    if (c) {
        __dt__7NameObjFv(c, 0);
        if (deleting > 0) ::operator delete(c);
    }
    return c;
}

extern "C" {
    void initAfterPlacement__7NameObjFv();
    void draw__7NameObjCFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
// Verified retail virtual slots; unresolved routine identities retain address labels.
extern "C" __attribute__((section(".data"))) const SensorVTableSlot lbl_8069592C[11] = {
    nullptr, nullptr,
    reinterpret_cast<SensorVTableSlot>(__dt__16SensorHitCheckerFv),
    reinterpret_cast<SensorVTableSlot>(fn_8023E150),
    initAfterPlacement__7NameObjFv,
    reinterpret_cast<SensorVTableSlot>(fn_8023E2B0),
    draw__7NameObjCFv, calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv
};
extern "C" __attribute__((section(".sdata"))) const char lbl_807CFAE0[4] = "Eye";
