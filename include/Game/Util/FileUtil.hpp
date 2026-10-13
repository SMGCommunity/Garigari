#pragma once

#include <JSystem/JKernel/JKRMemArchive.hpp>

namespace MR {
    /// @brief Determines if a file exists within the disc file system.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the file.
    /// @param[in] considerLanguage Determines if the file is localized.
    /// @return `true` if the file exists within the disc file system, `false` otherwise.
    bool isFileExist(const char* pFilePath, bool considerLanguage) NO_INLINE;

    /// @brief Returns the size of a file, in bytes.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the file.
    /// @param[in] considerLanguage Determines if the file is localized.
    /// @return The size of the file, in bytes.
    u32 getFileSize(const char* pFilePath, bool considerLanguage);

    /// @brief Returns the archive after it has been asynchronously mounted.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the archive file.
    /// @return A pointer to the mounted archive.
    JKRMemArchive* receiveArchive(const char* pFilePath);

    /// @brief Creates an archive from existing memory data.
    /// @param[in] pArcData A pointer to the archive file data.
    /// @param[in,out] pHeap A pointer to the target heap.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the file.
    void createAndAddArchive(void* pArcData, JKRHeap* pHeap, const char* pFilePath);

    /// @brief Creates an absolute path to the given galaxy's mission archive file.
    /// @param[out] pDst A pointer to the path buffer to initialize.
    /// @param[in] size The size of the path buffer, in bytes.
    /// @param[in] pStageName A pointer to the null-terminated name of the galaxy.
    void makeScenarioArchiveFileName(char* pDst, u32 size, const char* pStageName);
};  // namespace MR
