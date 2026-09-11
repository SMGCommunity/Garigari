#pragma once

#include <JGeometry.hpp>
class LiveActor;
class ActorSoundController; // Provisional type name; original identity unresolved.
class ActorSoundHolder {
public:
    ActorSoundHolder(LiveActor*, s32, const char*, const TVec3f*, const TVec3f&);
    void* _0;                         // 0x00: sound object, original type unresolved
    ActorSoundController* _4;          // 0x04
    TVec3f* _8;                        // 0x08: transformed position
    MtxPtr _C;                        // 0x0C: follow matrix
    TVec3f* _10;                       // 0x10: offset
};
