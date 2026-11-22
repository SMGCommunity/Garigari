#pragma once

#include "Game/LiveActor/LiveActor.hpp"

/// @brief A goal that Chomps can roll into. It will cause different effects depending on the type of Chomp that rolls into it. This object is
/// required for `WanwanRolling` and `WanwanRollingGold`'s SW_DEAD functionality.
class WanwanGoal : public LiveActor {
public:
    /// @brief Creates a new `WanwanGoal`.
    /// @param pName A pointer to the null-terminated name of the object.
    WanwanGoal(const char* pName);

    /// @brief Sets up the `WanwanGoal` and its fields based on the given BCSV information.
    /// @param rIter Reference to the `JMapInfoIter` that supplies BCSV information.
    virtual void init(const JMapInfoIter& rIter);

    /// @brief If this `WanwanGoal` has not yet been activated, and the receiving object is a `WanwanRolling` or `WanwanRollingGold` which is close
    /// enough to the goal, the goal will become activated and kill the receiver.
    /// @param pSender A pointer to a `HitSensor` belonging to the `WanwanGoal`.
    /// @param pReceiver A pointer to a `HitSensor` belonging to some other object.
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReciever);

    /// @brief This function is called every frame. It does nothing.
    void exeWait();

    /// @brief `true` if a Chomp has rolled into the goal and activated it; `false` otherwise.
    /* 0x90 */ bool mIsActive;
};
