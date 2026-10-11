#pragma once

#include <JSystem/JKernel/JKRMemArchive.hpp>

namespace MR {
    JKRMemArchive* receiveArchive(const char*);

    void makeScenarioArchiveFileName(char*, u32, const char*);

    bool isFileExist(const char*, bool);
};  // namespace MR
