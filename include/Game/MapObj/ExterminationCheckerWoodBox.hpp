#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class WoodBox;

/// @brief A controller that creates and registers several linked wood boxes. Individual boxes have to be linked to this object. It activates a switch
/// if all boxes have been destroyed.
class ExterminationCheckerWoodBox : public LiveActor {
public:
    /// @brief Creates a new `ExterminationCheckerWoodBox`.
    /// @param pName A pointer to the null-terminated name of the object.
    ExterminationCheckerWoodBox(const char* pName);

    /// @brief Initializes the object from the object's `JMapInfo`. Also creates and registers all of the linked wood boxes for this object.
    /// @param rIter A reference to an iterator through the data related to this object. This will tell the function how many wood boxes to create.
    virtual void init(const JMapInfoIter& rIter);

    /// @brief This function is called every frame. If Switch B is activated, all boxes will reappear and all switches will be deactivated. If Switch
    /// A isn't activated and all boxes have been destroyed within the time limit, Switch A is activated.
    void exeWatching();

    /// @brief Checks whether all boxes have been destroyed.
    /// @return `true` if all boxes have been destroyed; `false` otherwise.
    bool checkAllDestroyed();

    /// @brief An array of all of the wood boxes linked to this object.
    /* 0x90 */ WoodBox** mWoodBoxes;

    /// @brief The number of wood boxes linked to this object.
    /* 0x94 */ s32 mWoodBoxNum;
};
