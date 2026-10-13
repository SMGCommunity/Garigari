#pragma once

#include <revolution.h>

namespace MR {
    /// @brief Removes the file extension from the given path.
    /// @param pDst The output pointer for the path.
    /// @param size The size of the path buffer, in bytes.
    /// @param pPath The pointer to the null-terminated path.
    /// @return The pointer to the final directory separator character.
    char* removeExtensionString(char* pDst, u32 size, const char* pPath);

    /// @brief Copies `num` characters from `pSrc` to `pDst`.
    /// @param pDst The pointer to the null-terminated character string to copy to.
    /// @param pSrc The pointer to the null-terminated character string to copy from.
    /// @param num The number of characters to copy.
    void copyString(char* pDst, const char* pSrc, u32 num);

    /// @brief Returns the final component of the given path.
    /// @param pPath The pointer to the null-terminated path.
    /// @return The pointer to the null-terminated final component of the path.
    const char* getBasename(const char* pPath);

    /// @brief Copies `num` characters from `pSrc` to `pDst` and terminates the string.
    /// @param pDst The pointer to the null-terminated character string to copy to.
    /// @param pSrc The pointer to the null-terminated character string to copy from.
    /// @param num The number of characters to copy.
    void extractString(char* pDst, const char* pSrc, u32 num, u32);

    /// @brief Compares two character strings for equivalence without regard to case sensitivity.
    /// @param pStr1 The pointer to the left-hand null-terminated character string.
    /// @param pStr2 The pointer to the right-hand null-terminated character string.
    /// @retval -1 The first string contains a character less than the corresponding character in the second string.
    /// @retval 0 The strings are equivalent.
    /// @retval 1 The second string contains a character greater than the corresponding character in the first string.
    int strcasecmp(const char* pStr1, const char* pStr2);

    /// @brief Determines if two character strings are equivalent.
    /// @param pStr1 The pointer to the left-hand null-terminated character string.
    /// @param pStr2 The pointer to the right-hand null-terminated character string.
    /// @return `true` if the strings are equivalent, `false` otherwise.
    bool isEqualString(const char* pStr1, const char* pStr2);

    /// @brief Determines if two character strings are equivalent without regard to case sensitivity.
    /// @param pStr1 The pointer to the left-hand null-terminated character string.
    /// @param pStr2 The pointer to the right-hand null-terminated character string.
    /// @return `true` if the strings are equivalent, `false` otherwise.
    bool isEqualStringCase(const char* pStr1, const char* pStr2);

    /// @brief Determines if the given character string contains the given substring.
    /// @param pStr The pointer to the null-terminated character string.
    /// @param pSubStr The pointer to the null-terminated character substring.
    /// @return `true` if the string contains the substring, `false` otherwise.
    bool isEqualSubString(const char* pStr, const char* pSubStr);

    /// @brief Determines if the given character string contains a space character.
    /// @param pStr The pointer to the null-terminated character string.
    /// @return `true` if the string contains a space character, `false` otherwise.
    bool hasStringSpace(const char* pStr);

    /// @brief Determines if the pointer to the given character string is `nullptr` or contains no characters.
    /// @param pStr The pointer to the null-terminated character string.
    /// @return `true` if the pointer to the string is `nullptr` or contains no characters, `false` otherwise.
    bool isNullOrEmptyString(const char* pStr);
};  // namespace MR
