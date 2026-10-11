#pragma once

#include <JSystem/JKernel/JKRMemArchive.hpp>

namespace MR {
    /// @brief Returns the archive after it has been asynchronously mounted.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the archive file.
    /// @return A pointer to the mounted archive.
    JKRMemArchive* receiveArchive(const char* pFilePath);

    /// @brief Creates an archive from existing memory data.
    /// @param[in] pArcData A pointer to the archive file data.
    /// @param[in,out] pHeap A pointer to the target heap.
    /// @param[in] pFilePath A pointer to the null-terminated absolute path of the file.
    void createAndAddArchive(void* pArcData, JKRHeap* pHeap, const char* pFilePath);

    void makeScenarioArchiveFileName(char*, u32, const char*);

    bool isFileExist(const char*, bool);
};  // namespace MR
