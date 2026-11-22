#pragma once

#include "Game/NameObj/NameObj.hpp"

class ExterminationWoodBoxFlagHolder : public NameObj {
public:
    /// @brief Creates a new `ExterminationWoodBoxFlagHolder` instance.
    /// @param pName A pointer to the null-terminated name of the object.
    ExterminationWoodBoxFlagHolder(const char* pName);

    /// @brief Initializes the object from the object's `JMapInfo`. Also creates and registers all of the linked wood boxes for this object.
    /// @param rIter A reference to an iterator through the data related to this object.
    virtual void init(const JMapInfoIter&);

    /* 0x12 */ bool mFlag;
};

namespace MR {
    void setExterminationWoodBoxFlag();
    void clearExterminationWoodBoxFlag();
    bool getExterminationWoodBoxFlagHolder();
};  // namespace MR
