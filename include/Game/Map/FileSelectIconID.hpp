#pragma once

#include <revolution/types.h>

/// @brief The identifier of a File Selection Screen icon.
class FileSelectIconID {
public:
    /// @brief The identifier of a Mario character icon.
    enum EFellowID {
        /// @brief The Mario icon.
        Mario,

        /// @brief The Luigi icon.
        Luigi,

        /// @brief The Yoshi icon.
        Yoshi,

        /// @brief The Toad icon.
        Kinopio,

        /// @brief The Peach icon.
        Peach,

        /// @brief The Luma icon.
        Tico,
    };

    /// @brief Creates a new `FileSelectIconID`.
    FileSelectIconID();

    /// @brief Creates a new `FileSelectIconID`.
    /// @param rOther The reference to the `FileSelectIconID` to copy from.
    FileSelectIconID(const FileSelectIconID& rOther);

    /// @brief Updates the value of each member variable.
    /// @param rOther The reference to the `FileSelectIconID` to copy from.
    void set(const FileSelectIconID& rOther);

    /// @brief Updates the position of the Mii data in the Mii database.
    /// @param miiIndex The new position of the Mii data.
    void setMiiIndex(u16);

    /// @brief Determines if the icon represents a Mii character.
    /// @return `true` if the icon represents a Mii character, `false` otherwise.
    bool isMii() const;

    /// @brief Returns the position of the Mii data in the Mii database.
    /// @return The position of the Mii data.
    u16 getMiiIndex() const;

    /// @brief Updates the identifier of the Mario character.
    /// @param fellowID The new identifier of the Mario character.
    void setFellowID(EFellowID);

    /// @brief Determines if the icon represents a Mario character.
    /// @return `true` if the icon represents a Mario character, `false` otherwise.
    bool isFellow() const;

    /// @brief Returns the identifier of the Mario character.
    /// @return The identifier of the Mario character.
    EFellowID getFellowID() const;

private:
    /// @brief Determines if the icon represents a Mii character.
    /* 0x0 */ bool mIsMii;

    /// @brief The position of the Mii data in the Mii database or the identifier of a Mario character.
    /* 0x2 */ u16 mData;
};
