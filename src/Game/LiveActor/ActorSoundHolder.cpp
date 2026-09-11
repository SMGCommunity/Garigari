#include "LiveActor/ActorSoundHolder.hpp"
#include "LiveActor/LiveActor.hpp"
void* operator new(unsigned long);
extern "C" const f32 lbl_807DC3A0;
extern "C" const f32 lbl_807DC3A4;

// Partial layouts; original controller and entry type names remain unresolved.
struct ActorSoundEntry {
    u8 _0[0x14];
    void* _14;
};
class ActorSoundController {
public:
    u8 _0[0x18];
    u32 _18;
    ActorSoundEntry* _1C;
};

// Partial resource layouts inferred from target accesses.
class ResTable {
public:
    void* getRes(u32) const;
    u8 _0[4];
    u32 mCount;
};
class ResourceHolder {
public:
    u8 _0[0x1C];
    ResTable* _1C;
};
struct SoundResource {
    u16 mCount;
};
namespace MR { ResourceHolder* getResourceHolder(const LiveActor*); }
extern "C" {
    void* fn_80040D70();
    void* fn_8007FE20(void*, const TVec3f*, u8, void*);
    bool fn_8003F1A0(const TVec3f*, f32);
    void fn_805C86D0(MtxPtr, const TVec3f*, TVec3f*);
    void* fn_80220A80(LiveActor*, const char*);
    ActorSoundController* fn_8021F0B0(ActorSoundController*, LiveActor*, void*, void*);
    void* fn_8007C890();
    void fn_800879A0(void*, const u32*, u32);
}

ActorSoundHolder::ActorSoundHolder(LiveActor* actor, s32 count, const char* name, const TVec3f* position, const TVec3f& offset) {
    _0 = nullptr;
    _4 = nullptr;
    _8 = nullptr;
    _C = nullptr;
    _10 = nullptr;
    if (position != nullptr) {
        void* object = ::operator new(0x74);
        if (object != nullptr) {
            object = fn_8007FE20(object, position, static_cast<u8>(count), fn_80040D70());
        }
        _0 = object;
    } else if (!fn_8003F1A0(&offset, lbl_807DC3A4)) {
        _10 = new TVec3f(static_cast<const Vec&>(offset));
        _8 = new TVec3f(lbl_807DC3A0);
        _C = actor->getBaseMtx();
        fn_805C86D0(_C, _10, _8);
        void* object = ::operator new(0x74);
        if (object != nullptr) {
            object = fn_8007FE20(object, _8, static_cast<u8>(count), fn_80040D70());
        }
        _0 = object;
    } else {
        void* object = ::operator new(0x74);
        if (object != nullptr) {
            object = fn_8007FE20(object, &actor->mPosition, static_cast<u8>(count), fn_80040D70());
        }
        _0 = object;
    }
    void* data = fn_80220A80(actor, name);
    if (data != nullptr) {
        ActorSoundController* controller = static_cast<ActorSoundController*>(::operator new(0x20));
        if (controller != nullptr) {
            controller = fn_8021F0B0(controller, actor, _0, data);
        }
        _4 = controller;
    }
    ResourceHolder* resource = MR::getResourceHolder(actor);
    if (resource != nullptr) {
        ResTable* table = resource->_1C;
        if (table != nullptr && table->mCount != 0) {
            void* manager = fn_8007C890();
            for (u32 i = 0; i < table->mCount; ++i) {
                SoundResource* sound = static_cast<SoundResource*>(table->getRes(i));
                for (s32 j = 0; j < sound->mCount; ++j) {
                    u32 id = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(sound) + j * 0x20 + 8);
                    fn_800879A0(manager, &id, 0);
                }
            }
        }
    }
}

extern "C" {
    void fn_8021F6B0(ActorSoundController*);
    void fn_8021F6D0(ActorSoundController*);
    void fn_8007CC80(void*);
    void fn_805C86D0(MtxPtr, const TVec3f*, TVec3f*);
    void fn_8021F2D0(ActorSoundController*);
    void fn_8021F4B0(ActorSoundController*);

    void* fn_8022CD70(const ActorSoundHolder* holder) {
        return holder->_0;
    }
    void fn_8022CD80(ActorSoundHolder* holder) {
        if (holder->_4 != nullptr) {
            fn_8021F6B0(holder->_4);
        }
    }
    void fn_8022CDA0(ActorSoundHolder* holder) {
        if (holder->_4 != nullptr) {
            fn_8021F6D0(holder->_4);
        }
    }
    bool fn_8022CDC0(ActorSoundHolder* holder) {
        if (holder->_10 != nullptr) {
            return false;
        }
        fn_8007CC80(holder->_0);
        return true;
    }
    void fn_8022CE00(ActorSoundHolder* holder) {
        if (holder->_10 != nullptr) {
            fn_805C86D0(holder->_C, holder->_10, holder->_8);
        }
        if (holder->_4 != nullptr) {
            fn_8021F2D0(holder->_4);
        }
    }
    void fn_8022CE50(ActorSoundHolder* holder) {
        if (holder->_4 != nullptr) {
            fn_8021F4B0(holder->_4);
        }
    }
    void* fn_8022CE70(const LiveActor* actor) {
        if (actor->mSoundHolder == nullptr) {
            return nullptr;
        }
        return actor->mSoundHolder->_0;
    }
    u32 fn_8022CE90(const LiveActor* actor) {
        if (actor->mSoundHolder == nullptr || actor->mSoundHolder->_4 == nullptr) {
            return 0;
        }
        return actor->mSoundHolder->_4->_18;
    }
    void* fn_8022CEC0(const LiveActor* actor, s32 index) {
        return actor->mSoundHolder->_4->_1C[index]._14;
    }
}

extern "C" const f32 lbl_807DC3A0 = 0.0f;
extern "C" const f32 lbl_807DC3A4 = 0.001f;
