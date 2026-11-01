#pragma once

#include "Game/Screen/SimpleLayout.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class LiveActor;

/// @brief Layout which appears and is positioned based on a host LiveActor.
class ActorLayout : public SimpleLayout {
public:
    ActorLayout(LiveActor*, const char*, const char*, const TVec3f&, u32, int);

    virtual void control();

    bool isHostHidden() const;

    /* 0x2C */ LiveActor* mHostActor;
    /* 0x30 */ TVec3f mOffset; ///< The added offset between the layout and the host actor.
};
