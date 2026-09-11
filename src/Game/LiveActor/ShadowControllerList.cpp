// List operations adapt CC0 Petari fa77cd4d; offsets and calls are verified against Galaxy 2.
#include "LiveActor/ShadowControllerList.hpp"

namespace MR { bool isEqualString(const char*, const char*); }
extern "C" void fn_8023EDC0(ShadowController*);

// Accessed offsets only; unrecovered ShadowController storage remains opaque.
struct ShadowControllerAccess {
    LiveActor* host;
    const char* name;
    u8 _8[0x69];
    u8 _71;
    u8 _72;
};

ShadowControllerList::ShadowControllerList(LiveActor* host, u32 capacity)
    : mList(), mHost(host) {
    mList.array = new ShadowController*[capacity];
    mList.capacity = capacity;
}

void ShadowControllerList::addController(ShadowController* controller) {
    mList.push_back(controller);
}

u32 ShadowControllerList::getControllerCount() const {
    return mList.count;
}

ShadowController* ShadowControllerList::getController(u32 index) const {
    return mList.array[index];
}

ShadowController* ShadowControllerList::getController(const char* name) const {
    if (mList.count == 1) return mList.array[0];
    for (u32 i = 0; i < mList.count; ++i) {
        if (MR::isEqualString(name, reinterpret_cast<ShadowControllerAccess*>(mList.array[i])->name)) {
            return mList.array[i];
        }
    }
    return nullptr;
}

void ShadowControllerList::resetCalcCount() {
    for (u32 i = 0; i < mList.count; ++i) {
        ShadowControllerAccess* controller = reinterpret_cast<ShadowControllerAccess*>(mList.array[i]);
        controller->_71 = 0;
        controller->_72 = 0;
    }
}

void ShadowControllerList::requestCalc() {
    for (u32 i = 0; i < mList.count; ++i) {
        fn_8023EDC0(mList.array[i]);
    }
}
