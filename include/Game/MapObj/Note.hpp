#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"

class NoteFairy;
class FlashingCtrl;

/// @brief Class that represents a single note in a `NoteFairy` actor.
class Note : public LiveActor {
public:
    Note(const char* pName, const TVec3f& rRailDirection, NoteFairy* pNoteFairy);

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual void control();
    virtual void calcAndSetBaseMtx();

    /// @brief Checks if the sensor is either a player or a rideable entity and if it is, it will "collect" the note.
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);

    void startCountDown();

    /// @brief Begins the countdown sequence that plays the "waiting" animation, and is switched to the countdown nerve when the parent `NoteFairy`
    /// starts the countdown.
    void exeWait();

    /// @brief Begins the flashing sequence and, if the current step reaches the end of the countdown, kills this `Note`.
    void exeCountDown();

    /// @brief Scales the note's velocity by -30.0 and then invalidates all hit sensors. After 10 steps, it kills this `Note`.
    void exeFlyUp();

    /// @brief The parent `NoteFairy` that this note was spawned from.
    /* 0x90 */ NoteFairy* mNoteFairy;

    /* 0x94 */ TVec3f _94;
    /* 0xA0 */ TVec3f mRailDirection;

    /// @brief The amount of steps it takes for the note to disappear.
    /* 0xAC */ s32 mCounter;

    /* 0xB0 */ f32 _B0;

    /// @brief Whether the countdown is currently active.
    /* 0xB4 */ bool mIsCountdown;

    /// @brief A pointer to the `FlashingCtrl` instance that handles the "fading away" effects.
    /* 0xB8 */ FlashingCtrl* mFlashCtrl;
};

class NoteGroup : public LiveActorGroup {
public:
    NoteGroup();

    virtual void init(const JMapInfoIter&);
    virtual void movement();

    /* 0x20 */ f32 mRotation;
};
