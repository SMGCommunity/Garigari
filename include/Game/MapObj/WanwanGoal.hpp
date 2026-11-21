#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class WanwanGoal : public LiveActor {
public:
    /// @brief Creates a new `WanwanGoal`.
    /// @param pName A pointer to the null-terminated name of the object.
    WanwanGoal(const char* pName);

    /// @brief Sets up the `WanwanGoal` and its fields based on the given BCSV information.
    /// @param rIter Reference to the `JMapInfoIter` that supplies BCSV information.
    virtual void init(const JMapInfoIter& rIter);
    
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReciever);

    /// @brief This function is called every frame. It does nothing.
    void exeWait();

    /* 0x90 */ bool _90;
};
